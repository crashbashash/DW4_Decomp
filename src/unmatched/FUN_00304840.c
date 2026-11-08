#include "dw4/reflected.h"
int strlen(int);
int strncmp(int, int, unsigned);
igPluginRepository *FUN_002bc930(int);
int FUN_002eb010(int);
int ObjectList_AppendRetained(int, igPluginRepository *);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
int StringPool_Intern(int, char *);
int igNamedObject_SetName(igPluginRepository *, int);
int igObject_Destroy(igPluginRepository *);
int igObject_GetAllocator(igPluginHelper *);
extern int DAT_004c22c8[4];
extern int DAT_004c22d0[4];
extern int DAT_004fafb8[4];
extern int DAT_004fafc0[4];
extern int DAT_00586f20[4];
extern char GPR_00554c18;
extern char GPR_00554c1c;

void FUN_00304840(igPluginHelper *arg0, int arg1, int arg2) {
    igPluginRepository * volatile sp4C;
    igPluginRepository *o;
    int s2, v, old;
    int *hd;
    if (GPR_00554c18 == 0) {
        DAT_004fafb8[0] = strlen(DAT_004c22c8[0]);
        GPR_00554c18 = 1;
    }
    if (GPR_00554c1c == 0) {
        DAT_004fafc0[0] = strlen(DAT_004c22d0[0]);
        GPR_00554c1c = 1;
    }
    sp4C = FUN_002bc930(igObject_GetAllocator(arg0));
    igNamedObject_SetName(sp4C, arg1);
    if (strncmp(arg2, DAT_004c22c8[0], DAT_004fafb8[0]) == 0) {
            o = sp4C;
    if (DAT_00586f20[0] == 0) {
        v = FUN_002eb010(16);
        if (v != 0) v = StringPool_Construct(v);
        DAT_00586f20[0] = v;
    }
    s2 = StringPool_Intern(DAT_00586f20[0], (char *)(arg2 + DAT_004fafb8[0]));
    old = o->_location;
    if (old != 0) {
        hd = (int *)(old - 8);
        v = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = v;
        if (v == 0) StringChunk_ReleaseHeader(*hd, hd);
    }
    o->_location = s2;
    sp4C->_locationType = 1;

    } else if (strncmp(arg2, DAT_004c22d0[0], DAT_004fafc0[0]) == 0) {
            o = sp4C;
    if (DAT_00586f20[0] == 0) {
        v = FUN_002eb010(16);
        if (v != 0) v = StringPool_Construct(v);
        DAT_00586f20[0] = v;
    }
    s2 = StringPool_Intern(DAT_00586f20[0], (char *)(arg2 + DAT_004fafc0[0]));
    old = o->_location;
    if (old != 0) {
        hd = (int *)(old - 8);
        v = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = v;
        if (v == 0) StringChunk_ReleaseHeader(*hd, hd);
    }
    o->_location = s2;
    sp4C->_locationType = 2;

    } else {
            o = sp4C;
    if (DAT_00586f20[0] == 0) {
        v = FUN_002eb010(16);
        if (v != 0) v = StringPool_Construct(v);
        DAT_00586f20[0] = v;
    }
    s2 = StringPool_Intern(DAT_00586f20[0], (char *)(arg2));
    old = o->_location;
    if (old != 0) {
        hd = (int *)(old - 8);
        v = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = v;
        if (v == 0) StringChunk_ReleaseHeader(*hd, hd);
    }
    o->_location = s2;
    sp4C->_locationType = 0;

    }
    ObjectList_AppendRetained(arg0->_repositoryList, sp4C);
    o = sp4C;
    if (o != 0) {
        o->_refCount = (int)o->_refCount - 1;
        if ((((unsigned long long)(long long)(int)o->_refCount) & 0x7fffffULL) == 0) igObject_Destroy(o);
    }
}
