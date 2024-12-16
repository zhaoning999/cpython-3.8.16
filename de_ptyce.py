import aes

with open('test1.pyc', 'rb') as py_file:
    py_data = py_file.read()
    print('py_data:', len(py_data))

# with open('test1.pyce22', 'rb') as pyc_file:
#     magic = pyc_file.read(8)
#     pyc_data = pyc_file.read()
#     print('pyc_data:', len(pyc_data))
# with open('test1.pycd', 'wb') as pye_file:
#     pye_file.write(magic)
#     pye_file.write(aes.decrypt(pyc_data))