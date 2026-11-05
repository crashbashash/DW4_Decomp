/* 0x0038d820 — registers the receiver of an info record (falling back to the default receiver) with the messenger. C++ keeps the
 * call a real jal (the C front end turns a trailing call into a tail jump); the ternary gives the empty-then / branch-over shape. */
#include "dw4/reflected.h"
extern "C" {
int beMessenger_RegisterReceiver(int, beBaseInfoRam *, int, int *, int);
extern int DAT_004e0858[4];
void beMessenger_RegisterReceiverFromInfo(int arg0, beBaseInfoRam *arg1, int arg2);
}
void beMessenger_RegisterReceiverFromInfo(int arg0, beBaseInfoRam *arg1, int arg2) {
    beBaseInfo *info = (beBaseInfo *)arg1->_parentInfo;
    int *recv = (int *)info->_name;
    int t = arg1->_ramNo;
    recv = recv != 0 ? recv : &DAT_004e0858[0];
    beMessenger_RegisterReceiver(arg0, arg1, arg2, recv, t);
}
