import aes
import py_compile
def pyc2pye(path):
    """Convert a pyc-file to a pye-file."""
    
    pe_path = path + 'e'
    print('Converting {} to {}...'.format(path, pe_path))
    # 先读出2字节的magic number
    
    with open(path, 'rb') as pyc_file:
        magic = pyc_file.read(16)
        pyc_data = pyc_file.read()
        # print('magic:', len(magic))
        print('pyc_data:', len(pyc_data))
    with open(pe_path, 'wb') as pye_file:
        pye_file.write(magic)
        pye_file.write(aes.encrypt(pyc_data))

path = 'test2.py'
pathc = path + 'c'
py_compile.compile(path, pathc)
pyc2pye(pathc)