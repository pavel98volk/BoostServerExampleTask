#include "synchronized_io.h"
#include <iostream>


 SyncIStream& SyncIStream::getInstance(){
    static SyncIStream instance;
    return instance;
}
SyncIStream &operator>>( SyncIStream  &input, std::string &str ) { 
    std::lock_guard<std::mutex> lock(input.mutex_);
    std::cin >> str;
    return input;            
}


SyncOStream& SyncOStream::getInstance(){
    static SyncOStream instance;
    return instance;
}
SyncOStream& operator<<( SyncOStream &output, const std::string& str ) { 
    std::lock_guard<std::mutex> lock(output.mutex_);
    //std::cout << "some strange things";

    std::cout << str;
    return output;            
}

SyncIStream& g_cin_s  = SyncIStream::getInstance();
SyncOStream& g_cout_s = SyncOStream::getInstance();