#pragma once
#include <string>
#include <mutex>

class SyncIStream{
    public:
    static SyncIStream& getInstance();
    friend SyncIStream &operator>>( SyncIStream  &input, std::string &str );
    private:
    SyncIStream()=default;
    std::mutex mutex_;
}; 

class SyncOStream{
    public:
    static SyncOStream& getInstance();
    friend SyncOStream& operator<<( SyncOStream &output, const std::string &str );
    private:
    SyncOStream()=default;
    std::mutex mutex_;
};

extern SyncIStream& g_cin_s;
extern SyncOStream& g_cout_s;


