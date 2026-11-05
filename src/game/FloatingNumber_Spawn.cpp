#include "dw4/reflected.h"
extern "C" {
struct DmgVec { float x; float y; float z; };
struct DmgRow { int w[7]; };
extern struct DmgRow DAT_004c8770[];
extern struct DmgRow DAT_004c8774[];
extern struct DmgRow DAT_004c8778[];
extern int DAT_0050db10[4];
extern int DAT_0050dd00[4];
extern int DAT_0050dd10[4];
extern int DAT_0050dd20[4];
extern int DAT_0050dd30[4];
extern int DAT_0058a1c0[4];
extern int DAT_0058a1e8[4];
int Matrix44_GetTranslation(int, struct DmgVec *);
int beMessenger_AppendInt(int, int);
int beMessenger_AppendString(int, int);
int beMessenger_AppendVec3(int, struct DmgVec *);
int beMessenger_DispatchSelected(int, int *);
beBaseInfoRam *beMessenger_GetObject(int, int);
int beMessenger_GetObjectCount(int);
int beMessenger_SelectReceivers(int, int *, int, int);
int beMessenger_SendNamed(int, int *, int, int, int *);
void FloatingNumber_Spawn(int dmg, int row);
}

void FloatingNumber_Spawn(int dmg, int row) {
    int a = DAT_004c8770[row].w[0];
    int b = DAT_004c8774[row].w[0];
    beBaseInfoRam *obj;
    int idx;
    int s;
    struct DmgVec v;
    struct DmgVec w;
    beMessenger_SendNamed(DAT_0058a1c0[0], DAT_0050db10, a, -1, DAT_0050dd00);
    if (beMessenger_GetObjectCount(DAT_0058a1c0[0]) != 0) {
        obj = beMessenger_GetObject(DAT_0058a1c0[0], 0);
        if (dmg < 10) idx = 0;
        else if (dmg < 100) idx = 1;
        else if (dmg < 1000) idx = 2;
        else if (dmg < 10000) idx = 3;
        else if (dmg < 100000) idx = 4;
        else { idx = 4; dmg = 99999; }
        s = DAT_004c8778[row].w[idx];
        beMessenger_SelectReceivers(DAT_0058a1c0[0], DAT_0050db10, a, obj->_ramNo);
        beMessenger_AppendString(DAT_0058a1c0[0], s);
        Matrix44_GetTranslation(DAT_0058a1e8[0], &v);
        w.x = v.x; w.y = v.y; w.z = v.z;
        beMessenger_AppendVec3(DAT_0058a1c0[0], &w);
        beMessenger_DispatchSelected(DAT_0058a1c0[0], DAT_0050dd10);
        beMessenger_SelectReceivers(DAT_0058a1c0[0], DAT_0050dd20, b, obj->_ramNo);
        beMessenger_AppendInt(DAT_0058a1c0[0], dmg);
        beMessenger_DispatchSelected(DAT_0058a1c0[0], DAT_0050dd30);
    }
}
