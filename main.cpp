#include "RSA.hpp"
#include <iostream>
#include <exception>


int main()
{
    RSA rsa;
    
    for (int i = 0; i < 100; ++i) {
        pairOfIntPairs keys = rsa.generateKeys();

        auto publicKey = keys.first;
        auto privateKey = keys.second;
        std::cout << "e: " << publicKey.first << " n: " << publicKey.second << std::endl;
        std::cout << "d: " << privateKey.first << " n: " << privateKey.second << std::endl;

        ULL msg = 1356;
        std::cout << "msg: " << msg << std::endl;

        ULL enMsg = rsa.encrypt(msg, publicKey);
        std::cout << "encrypted msg: " << enMsg << std::endl;

        ULL decMsg = rsa.decrypt(enMsg, privateKey);
        std::cout << "dectypted msg: " << decMsg << std::endl << std::endl;
    }

}