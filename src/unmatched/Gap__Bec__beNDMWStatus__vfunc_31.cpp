/* Status-screen update for one info record (info->_st0: 0 create the sub-window picked by
 * _subWndNo, 1 run it until it stops, default tear down). FUN_003d8740 takes (self, info, st0) so
 * the state stays in a2; the sub-window reference lives in memory and is released when its block
 * ends, before case 0 falls into case 1 into default. */
#include "dw4/reflected.h"

extern "C" {
int FUN_003d8740(void *, void *, int);
beNDMWWindow *FUN_003b7750(void *);
beNDMWWindow *FUN_003b7eb0(void *);
beNDMWWindow *FUN_003bb1d0(void *);
beNDMWWindow *beNDMWShopCtrl00_Create(void *);
void *igObject_GetAllocator(void *);
void *Memory_GetAllocatorBySelector(int);
void igObject_Destroy(beNDMWWindow *);
int FUN_00236f80(int, int);
int beLua__RunNamedChunk(int, int *, int);
void beMessenger_SelectGroup(int, int *);
void beMessenger_AppendString(int, int *);
void beMessenger_AppendInt(int, int);
void beMessenger_DispatchSelected(int, int *);
void beMessenger_SendGroup(int, int *, int *);
void beMessenger_SetFreezeTime(int, int);
int beMessenger_GetObject(int, int);
int beMessenger_GetBool(int, int);
beDataObjBool *igProperty_GetRecordByte(int, int *);
void beNDMWWindow_BindContext(beNDMWWindow *, int, int, int, int);
void beNDMWWindow_UpdateTree(int);
extern int DAT_00516790[4], DAT_005167a0[4], DAT_005167a8[4], DAT_005167b8[4], DAT_005167c8[4], DAT_005167d0[4],
    DAT_005167d8[4], DAT_005167e0[4], DAT_005167e8[4], DAT_005167f0[4], DAT_005167f8[4], DAT_00516800[4],
    DAT_00516810[4], DAT_00516818[4], DAT_00516828[4], DAT_00516838[4], DAT_00516848[4], DAT_00516850[4],
    DAT_00516860[4], DAT_00516868[4], DAT_00516870[4], DAT_00516878[4], DAT_00516888[4], DAT_00516898[4],
    DAT_005168a8[4], DAT_005168b8[4], DAT_005168c8[4], DAT_005168d0[4], DAT_00587110[4], DAT_00589208[4];
extern unsigned char GPR_00554c14;
}

/* Owning stack reference to the sub-window being created: starts empty, takes the window the
 * creator returns and releases it on scope exit (reference count in the low 23 bits of _refCount). */
template <class T> class igSmartPointer {
public:
    T *p;
    igSmartPointer(T *o) : p(o) {}
    ~igSmartPointer() { T *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};

#define RELEASE_WIN(p_) { beNDMWWindow *rw = (p_); if (rw) { --rw->_refCount; if (!(rw->_refCount & 0x7fffff)) igObject_Destroy(rw); } }
#define GET_ALLOC(v) { void *ga = igObject_GetAllocator(self); if (GPR_00554c14 != 0) { v = ga; } else { v = Memory_GetAllocatorBySelector(DAT_00587110[0]); } }
#define NEXT() { info->_st0 = info->_st0 + 1; info->_st3 = 0; info->_st2 = 0; info->_st1 = 0; }
#define MK(fn) { void *al; GET_ALLOC(al) RELEASE_WIN(w.p) w.p = fn(al); }

extern "C" void Gap__Bec__beNDMWStatus__vfunc_31(beNDMWStatus *self, beNDMWStatusInfoRam *info);
void Gap__Bec__beNDMWStatus__vfunc_31(beNDMWStatus *self, beNDMWStatusInfoRam *info)
{
    int st;
    if (info->_isRun == 0) return;
    st = info->_st0;
    switch (st) {
    case 0:
        FUN_003d8740(self, info, st);
        beMessenger_SelectGroup(self->_messenger, DAT_00516790);
        beMessenger_AppendString(self->_messenger, DAT_005167a0);
        beMessenger_DispatchSelected(self->_messenger, DAT_005167a8);
        {
        igSmartPointer<beNDMWWindow> w(0);
        switch (self->_subWndNo) {
        case 0:
            beMessenger_SelectGroup(self->_messenger, DAT_005167b8);
            beMessenger_AppendString(self->_messenger, DAT_005167c8);
            beMessenger_AppendString(self->_messenger, DAT_005167d0);
            beMessenger_DispatchSelected(self->_messenger, DAT_005167d8);
            beMessenger_SelectGroup(self->_messenger, DAT_005167b8);
            beMessenger_AppendString(self->_messenger, DAT_005167e0);
            beMessenger_AppendString(self->_messenger, DAT_005167d0);
            beMessenger_DispatchSelected(self->_messenger, DAT_005167d8);
            MK(FUN_003bb1d0)
            break;
        case 1: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
            MK(beNDMWShopCtrl00_Create)
            break;
        case 2:
            MK(FUN_003b7750)
            break;
        case 10:
            MK(FUN_003b7eb0)
            break;
        }
        beNDMWWindow_BindContext(w.p, 0, self->_insight, self->_whoGenerate, 0);
        w.p->_entCode = self->_subWndNo;
        {
            beNDMWWindow *s2 = w.p;
            if (s2) ++s2->_refCount;
            RELEASE_WIN((beNDMWWindow *)self->_windowPro)
            self->_windowPro = (int)s2;
        }
        if (self->_subWndNo != 0) {
            beMessenger_SendGroup(self->_messenger, DAT_005167e8, DAT_005167f0);
            beMessenger_SendGroup(self->_messenger, DAT_005167e8, DAT_005167f8);
            beMessenger_SelectGroup(self->_messenger, DAT_005167e8);
            beMessenger_AppendString(self->_messenger, DAT_00516800);
            beMessenger_DispatchSelected(self->_messenger, DAT_00516810);
        }
        }
        NEXT()
    case 1:
        if (self->_windowPro != 0) beNDMWWindow_UpdateTree(self->_windowPro);
        if (((beNDMWWindow *)self->_windowPro)->_isRun != 0) return;
        NEXT()
    default:
        {
            int i;
            RELEASE_WIN((beNDMWWindow *)self->_windowPro)
            self->_windowPro = 0;
            beMessenger_SendGroup(self->_messenger, DAT_005167e8, DAT_00516818);
            beMessenger_SendGroup(self->_messenger, DAT_00516828, DAT_00516818);
            beMessenger_SendGroup(self->_messenger, DAT_00516838, DAT_00516818);
            beMessenger_SetFreezeTime(self->_messenger, 0);
            info->_isRun = 0;
            i = 0;
            do {
                beMessenger_SelectGroup(self->_messenger, DAT_00516848);
                beMessenger_AppendInt(self->_messenger, i);
                beMessenger_DispatchSelected(self->_messenger, DAT_00516850);
                if (igProperty_GetRecordByte(beMessenger_GetObject(self->_messenger, 0), DAT_00516860)->_data != 0) {
                    beMessenger_SelectGroup(self->_messenger, DAT_00516848);
                    beMessenger_AppendInt(self->_messenger, i);
                    beMessenger_AppendInt(self->_messenger, 0);
                    beMessenger_DispatchSelected(self->_messenger, DAT_00516868);
                    beMessenger_SelectGroup(self->_messenger, DAT_00516848);
                    beMessenger_AppendInt(self->_messenger, i);
                    beMessenger_AppendInt(self->_messenger, 0);
                    beMessenger_DispatchSelected(self->_messenger, DAT_00516870);
                }
                i++;
            } while (i < 4);
            if (self->_subWndNo == 10) {
                beMessenger_SendGroup(self->_messenger, DAT_00516790, DAT_00516878);
                if ((beMessenger_GetBool(self->_messenger, 0) & 0xff) == 0) {
                    beMessenger_SelectGroup(self->_messenger, DAT_00516888);
                    beMessenger_AppendInt(self->_messenger, 4);
                    beMessenger_DispatchSelected(self->_messenger, DAT_00516898);
                    beMessenger_SelectGroup(self->_messenger, DAT_00516790);
                    beMessenger_AppendString(self->_messenger, DAT_005168a8);
                    beMessenger_DispatchSelected(self->_messenger, DAT_005168b8);
                }
            } else {
                beMessenger_SelectGroup(self->_messenger, DAT_005167b8);
                beMessenger_AppendString(self->_messenger, DAT_005167c8);
                beMessenger_AppendString(self->_messenger, DAT_005168c8);
                beMessenger_DispatchSelected(self->_messenger, DAT_005167d8);
                beMessenger_SelectGroup(self->_messenger, DAT_005167b8);
                beMessenger_AppendString(self->_messenger, DAT_005167e0);
                beMessenger_AppendString(self->_messenger, DAT_005168c8);
                beMessenger_DispatchSelected(self->_messenger, DAT_005167d8);
                if (self->_subWndNo != 0)
                    beLua__RunNamedChunk(FUN_00236f80(self->_insight, DAT_00589208[0]), DAT_005168d0, 0);
            }
        }
    }
}
