#include "dw4/reflected.h"
extern char D_0051a918[],D_0051a968[];
extern "C" bool beNDMWWindowSelect_CanRequestFO2TOP(beNDMWWindowSelect *);
extern "C" void beMessenger_SendNamed(int,const char *,int,int,const char *);
extern "C" int beMessenger_GetBool(int,int);
bool beNDMWWindowSelect_CanRequestFO2TOP(beNDMWWindowSelect *self){
    beMessenger_SendNamed(self->_messenger,D_0051a918,self->_infoName,self->_playerNo,D_0051a968);
    return !beMessenger_GetBool(self->_messenger,0);
}
