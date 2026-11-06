#include "dw4/reflected.h"
int FUN_00100c20();
int igMatrix44f_SetIdentity();
extern int DAT_00562518[4];
extern void * DAT_00562528[4];
extern int DAT_00562530[4];
extern void * DAT_00562540[4];
extern int DAT_00562548[4];
extern void * DAT_00562558[4];
extern int DAT_00562588[4];
extern int DAT_0056258c[4];
extern int DAT_00562590[4];
extern int DAT_00562708[4];
extern void * DAT_00562718[4];
extern int DAT_00562748[4];
extern void * DAT_00562758[4];
extern int DAT_00562778[4];
extern void * DAT_00562788[4];
extern int DAT_00562890[4];
extern int DAT_00562a58[4];
extern void * DAT_00562a68[4];
extern int DAT_00562a70[4];
extern void * DAT_00562a80[4];
extern int DAT_00562a88[4];
extern void * DAT_00562a98[4];
extern int DAT_00562aa0[4];
extern void * DAT_00562ab0[4];
extern int DAT_00562ab8[4];
extern void * DAT_00562ac8[4];
extern int DAT_00562ad0[4];
extern void * DAT_00562ae0[4];
extern int DAT_00562ae8[4];
extern void * DAT_00562af8[4];
extern int DAT_00562b00[4];
extern void * DAT_00562b10[4];
extern int DAT_00562b18[4];
extern void * DAT_00562b28[4];
extern int DAT_00562b30[4];
extern void * DAT_00562b40[4];
extern int DAT_00562b48[4];
extern void * DAT_00562b58[4];
int FUN_001a0510();
int FUN_001a1fb0();
int FUN_001ab380();
int FUN_001ce350();
int FUN_001d21b0();
int FUN_001d3090();
int FUN_001d3110();
int FUN_001e3d70();
int FUN_001e3df0();
int FUN_001e3e70();
int FUN_001e3ef0();
int FUN_001e3f70();

void FUN_00520cf0(void) {
    DAT_00562528[0] = 0;
    FUN_00100c20(&DAT_00562528[0], &FUN_001e3f70, &DAT_00562518[0]);
    DAT_00562540[0] = 0;
    FUN_00100c20(&DAT_00562540[0], &FUN_001e3ef0, &DAT_00562530[0]);
    DAT_00562558[0] = 0;
    FUN_00100c20(&DAT_00562558[0], &FUN_001a1fb0, &DAT_00562548[0]);
    DAT_00562718[0] = 0;
    DAT_00562588[0] = 0x3F800000;
    DAT_0056258c[0] = 0x3F800000;
    DAT_00562590[0] = 0x3F800000;
    FUN_00100c20(&DAT_00562718[0], &FUN_001e3e70, &DAT_00562708[0]);
    DAT_00562758[0] = 0;
    if (DAT_00562758[0] != 0) {
        ((igObject *)DAT_00562758[0])->_refCount = ((igObject *)DAT_00562758[0])->_refCount + 1;
    }
    FUN_00100c20(&DAT_00562758[0], &FUN_001d3090, &DAT_00562748[0]);
    DAT_00562788[0] = 0;
    if (DAT_00562788[0] != 0) {
        ((igObject *)DAT_00562788[0])->_refCount = ((igObject *)DAT_00562788[0])->_refCount + 1;
    }
    FUN_00100c20(&DAT_00562788[0], &FUN_001ce350, &DAT_00562778[0]);
    igMatrix44f_SetIdentity(&DAT_00562890[0]);
    DAT_00562a68[0] = 0;
    if (DAT_00562a68[0] != 0) {
        ((igObject *)DAT_00562a68[0])->_refCount = ((igObject *)DAT_00562a68[0])->_refCount + 1;
    }
    FUN_00100c20(&DAT_00562a68[0], &FUN_001a0510, &DAT_00562a58[0]);
    DAT_00562a80[0] = 0;
    if (DAT_00562a80[0] != 0) {
        ((igObject *)DAT_00562a80[0])->_refCount = ((igObject *)DAT_00562a80[0])->_refCount + 1;
    }
    FUN_00100c20(&DAT_00562a80[0], &FUN_001e3df0, &DAT_00562a70[0]);
    DAT_00562a98[0] = 0;
    if (DAT_00562a98[0] != 0) {
        ((igObject *)DAT_00562a98[0])->_refCount = ((igObject *)DAT_00562a98[0])->_refCount + 1;
    }
    FUN_00100c20(&DAT_00562a98[0], &FUN_001d21b0, &DAT_00562a88[0]);
    DAT_00562ab0[0] = 0;
    if (DAT_00562ab0[0] != 0) {
        ((igObject *)DAT_00562ab0[0])->_refCount = ((igObject *)DAT_00562ab0[0])->_refCount + 1;
    }
    FUN_00100c20(&DAT_00562ab0[0], &FUN_001d21b0, &DAT_00562aa0[0]);
    DAT_00562ac8[0] = 0;
    if (DAT_00562ac8[0] != 0) {
        ((igObject *)DAT_00562ac8[0])->_refCount = ((igObject *)DAT_00562ac8[0])->_refCount + 1;
    }
    FUN_00100c20(&DAT_00562ac8[0], &FUN_001d21b0, &DAT_00562ab8[0]);
    DAT_00562ae0[0] = 0;
    if (DAT_00562ae0[0] != 0) {
        ((igObject *)DAT_00562ae0[0])->_refCount = ((igObject *)DAT_00562ae0[0])->_refCount + 1;
    }
    FUN_00100c20(&DAT_00562ae0[0], &FUN_001d21b0, &DAT_00562ad0[0]);
    DAT_00562af8[0] = 0;
    if (DAT_00562af8[0] != 0) {
        ((igObject *)DAT_00562af8[0])->_refCount = ((igObject *)DAT_00562af8[0])->_refCount + 1;
    }
    FUN_00100c20(&DAT_00562af8[0], &FUN_001ab380, &DAT_00562ae8[0]);
    DAT_00562b10[0] = 0;
    if (DAT_00562b10[0] != 0) {
        ((igObject *)DAT_00562b10[0])->_refCount = ((igObject *)DAT_00562b10[0])->_refCount + 1;
    }
    FUN_00100c20(&DAT_00562b10[0], &FUN_001ab380, &DAT_00562b00[0]);
    DAT_00562b28[0] = 0;
    if (DAT_00562b28[0] != 0) {
        ((igObject *)DAT_00562b28[0])->_refCount = ((igObject *)DAT_00562b28[0])->_refCount + 1;
    }
    FUN_00100c20(&DAT_00562b28[0], &FUN_001e3d70, &DAT_00562b18[0]);
    DAT_00562b40[0] = 0;
    if (DAT_00562b40[0] != 0) {
        ((igObject *)DAT_00562b40[0])->_refCount = ((igObject *)DAT_00562b40[0])->_refCount + 1;
    }
    FUN_00100c20(&DAT_00562b40[0], &FUN_001d3110, &DAT_00562b30[0]);
    DAT_00562b58[0] = 0;
    if (DAT_00562b58[0] != 0) {
        ((igObject *)DAT_00562b58[0])->_refCount = ((igObject *)DAT_00562b58[0])->_refCount + 1;
    }
    FUN_00100c20(&DAT_00562b58[0], &FUN_001ab380, &DAT_00562b48[0]);
}
