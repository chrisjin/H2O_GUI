#ifndef H2O_FILE_H
#define H2O_FILE_H
#include"H2O_Delegate.h"
namespace ColdWater
{
    class File:public Object
    {
    public:
        File();
        virtual void read(const char*);
    };
}
#endif // H2O_FILE_H
