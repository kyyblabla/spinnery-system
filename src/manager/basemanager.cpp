#include "basemanager.h"



BaseManager::BaseManager()
{


}

int BaseManager::startWork()
{
    int rc=this->init();
    if(rc<0){
        return rc;
    }

    work();

    return 1;

}


