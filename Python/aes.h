#ifndef __AES__H__
#define __AES__H__

int aes_encrypt(unsigned char *plaintext, int plaintext_len, unsigned char **ciphertext);

int aes_decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char **plaintext);

#endif