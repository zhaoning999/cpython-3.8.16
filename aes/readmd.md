#####
编译命令

c++ -O3 -Wall -shared -std=c++11 -fPIC  ../aes.cpp -o aes$(/opt/python38/bin/python3-config --extension-suffix) -lssl -lcrypto

运行

import aes
