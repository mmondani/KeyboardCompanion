#ifndef SDPROVIDER_H
#define SDPROVIDER_H


#include <FS.h>

class FSProvider {
    public:
        static FSProvider* getInstance();
        void begin(fs::FS* fs);
        fs::FS* take ();
        void give ();
        
        

    protected:
        FSProvider();
        FSProvider (FSProvider const&);
        FSProvider& operator= (FSProvider const&);


    private:
        static FSProvider* instance;
        fs::FS* fs;
        bool mutex;

};


#endif