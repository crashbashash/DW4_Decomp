#include "dw4/reflected.h"
void FUN_00175470(igPsx2VisualContext *arg0, void *arg1) {
    *(unsigned char *)((char *)(arg1) + 0) = (unsigned char) *(unsigned char *)&arg0->_videoMode[0];
    *(unsigned char *)((char *)(arg1) + 1) = (unsigned char) ((unsigned char *)&arg0->_videoMode[0])[1];
    *(int *)((char *)(arg1) + 4) = (int)((int) arg0->_videoMode[1]);
    *(int *)((char *)(arg1) + 8) = (int)((int) arg0->_videoMode[2]);
    *(float *)((char *)(arg1) + 12) = (float) *(float *)&arg0->_videoMode[3];
    *(int *)((char *)(arg1) + 16) = (int)((int) arg0->_videoMode[4]);
    *(int *)((char *)(arg1) + 20) = (int)((int) arg0->_videoMode[5]);
}
