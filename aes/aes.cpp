#include "pybind11/pybind11.h"
#include <string>
#include <openssl/evp.h>

namespace py = pybind11;

static const char*key = "01234567890123456789012345678901";
static const char*iv = "0123456789012345";

void handleErrors(void)
{
    // ERR_print_errors_fp(stderr);
    abort();
}

py::bytes encrypt(std::string plaintext_)
{
    unsigned char *plaintext = reinterpret_cast<unsigned char *>(const_cast< char*>(plaintext_.data()));
    int plaintext_len = plaintext_.size();
    unsigned char *ciphertext = new unsigned char[plaintext_len + 1];
    EVP_CIPHER_CTX *ctx;

    int len;

    int ciphertext_len;

    /* Create and initialise the context */
    if (!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    /* Initialise the encryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits */
    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_ctr(), NULL, reinterpret_cast<const unsigned char*>(key), reinterpret_cast<const unsigned char*>(iv)))
        handleErrors();

    /* Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_EncryptUpdate can be called multiple times if necessary
     */
    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
        handleErrors();
    ciphertext_len = len;

    /* Finalise the encryption. Further ciphertext bytes may be written at
     * this stage.
     */
    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
        handleErrors();
    ciphertext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    auto res = py::bytes(reinterpret_cast<char*>(ciphertext), ciphertext_len);
    delete[] ciphertext;
    return res; 
}

py::bytes decrypt(std::string ciphertext_)
{
    EVP_CIPHER_CTX *ctx;

    unsigned char *ciphertext = reinterpret_cast<unsigned char *>(const_cast< char*>(ciphertext_.data()));
    int ciphertext_len = ciphertext_.size();
    unsigned char *plaintext = new unsigned char[ciphertext_len + 1];    

    int len;

    int plaintext_len;

    /* Create and initialise the context */
    if (!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    /* Initialise the decryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits */
    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_ctr(), NULL, reinterpret_cast<const unsigned char*>(key), reinterpret_cast<const unsigned char*>(iv)))
        handleErrors();

    /* Provide the message to be decrypted, and obtain the plaintext output.
     * EVP_DecryptUpdate can be called multiple times if necessary
     */
    if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
        handleErrors();
    plaintext_len = len;

    /* Finalise the decryption. Further plaintext bytes may be written at
     * this stage.
     */
    if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
        handleErrors();
    plaintext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);
    auto res = py::bytes(reinterpret_cast<char*>(plaintext), plaintext_len);
    delete[] plaintext;
    return res; 
}



PYBIND11_MODULE(aes, m) {

    m.def("encrypt", [](std::string plaintext_) {
                return encrypt(plaintext_);
            });
    m.def("decrypt", [](std::string ciphertext_) {
            return decrypt(ciphertext_);
        });
}