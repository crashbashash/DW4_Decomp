/* The external float objects are default-origin constants; full-width words preserve the EE ABI. */
#include "dw4/reflected.h"
extern float D_004e1058[],D_004e105c[],D_004e1060[];
extern char D_00518738[];
extern "C" void beMessenger_SendNamed(void *,const char *,long long,long long,long long);
extern "C" void beNDMWWindow_PresentModel(beNDMWWindow *,long long,long long,long long,long long,const float *);
extern "C" void beNDMWWindow_PresentModelAtOrigin(beNDMWWindow *,long long,long long,long long,long long);
extern "C" void beNDMWWindow_SendModelSequence(beNDMWWindow *,long long,long long,long long);
void beNDMWWindow_PresentModelAtOrigin(beNDMWWindow *self,long long model,long long id,long long sequence,long long close){
    float origin[3];origin[0]=D_004e1058[0];origin[1]=D_004e105c[0];origin[2]=D_004e1060[0];
    beNDMWWindow_PresentModel(self,model,id,sequence,close,origin);
}
void beNDMWWindow_SendModelSequence(beNDMWWindow *self,long long model,long long id,long long sequence){
    beMessenger_SendNamed((void *)self->_messenger,D_00518738,model,id,sequence);
}
