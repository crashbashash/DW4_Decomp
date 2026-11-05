/* Exact full-width SELECTCTRL ISFO2TOP negation; finding #913. */
#include "dw4/reflected.h"
extern "C" void beMessenger_SendNamed(void *,const char *,long long,long long,const char *);
extern "C" long long beMessenger_GetBool(void *,int);
extern char D_0051a918[],D_0051a968[];
extern "C" bool beNDMWWindowSelect_CanRequestFO2TOP(beNDMWWindowSelect *);
bool beNDMWWindowSelect_CanRequestFO2TOP(beNDMWWindowSelect *self){
    beMessenger_SendNamed((void *)self->_messenger,D_0051a918,self->_infoName,self->_playerNo,D_0051a968);
    return !beMessenger_GetBool((void *)self->_messenger,0);
}
