#include "dw4/reflected.h"
#define OBJ(m) if (&m) { o = (igObject *)m; if (o != 0) { rc = (int)o->_refCount - 1; o->_refCount = rc; if (((unsigned long long) ((long long) (int)o->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(o); } } }
#define STR(m) if (&m) { p = (void *)m; if (p != 0) { h = (int *)((char *)(p) - 8); rc = *(int *)((char *)(p) - 4) - 1; *(int *)((char *)(p) - 4) = rc; if (rc == 0) { StringChunk_ReleaseHeader(*h, h); } } }
extern "C" {
int StringChunk_ReleaseHeader(int, int *);
int igObject_Destroy(igObject *);
int thunk_FUN_002ed460__002ff810(beNDMWMdlPlayer2InfoWork *);
extern int DAT_00537ee0[4];
void *FUN_00350410(beNDMWMdlPlayer2InfoWork *arg0, long long arg1);
}

void *FUN_00350410(beNDMWMdlPlayer2InfoWork *arg0, long long arg1) {
    void *p;
    igObject *o;
    int *h;
    int rc;

    if (arg0 != 0) {
        arg0->_vtable = (int)&DAT_00537ee0[0];
        OBJ(arg0->_baseAABox)
        OBJ(arg0->_subCommand)
        STR(arg0->_hitParentName)
        OBJ(arg0->_hitBody)
        OBJ(arg0->_debugHitBoxNode)
        OBJ(arg0->_rideOnData)
        OBJ(arg0->_moveObjectList)
        STR(arg0->_posLockBoneName)
        STR(arg0->_posLockModelName)
        OBJ(arg0->_posLockTrc)
        OBJ(arg0->_posLockNode)
        STR(arg0->_keyEventName)
        STR(arg0->_targetSpc1)
        STR(arg0->_targetKind)
        STR(arg0->_targetMode)
        OBJ(arg0->_aI)
        STR(arg0->_wCheckName)
        OBJ(arg0->_pdMoveDataList)
        STR(arg0->_luaFHit)
        STR(arg0->_luaWHit)
        STR(arg0->_luaBHit)
        OBJ(arg0->_labelOffsetList)
        OBJ(arg0->_labelNameList)
        OBJ(arg0->_labelSeqList)
        OBJ(arg0->_comData)
        STR(arg0->_seqCodeName)
        OBJ(arg0->_hp)
        OBJ(arg0->_mHp)
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}
