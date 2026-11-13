#include "dw4/reflected.h"

extern "C" void igInsightCore_AddToScheduler(int, char *);
extern "C" void igInsightCore_RemoveFromScheduler(int, char *);
extern "C" void *igInsightCore_FindManager(...);
extern "C" void *FUN_0034ce50(...);
extern "C" int FUN_00454290(...);
extern "C" int FUN_004542d0(...);
extern "C" int FUN_004574f0(...);
extern "C" int FUN_00462e90(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" int igObject_Destroy(...);
extern "C" int igObject_GetAllocator(...);
extern "C" int FUN_004542a0(int, int);
extern "C" int FUN_004542e0(int, int, int);
extern "C" int Gap__Bec__bePadManager__vfunc_25(void);
extern "C" void Gap__Bec__bePadManager__vfunc_26(void);
extern "C" int Gap__Bec__bePadManager__vfunc_20(void);
extern "C" int bePadData_UpdateButtons(...);
extern "C" void Gap__Bec__bePadManager__vfunc_21(bePadManager *self, int unusedArg);
extern "C" void Gap__Bec__bePadManager__vfunc_22(bePadManager *self, int unusedArg);
struct Rc { int vt; int rc; };
extern "C" int g_ndmwAllocatorSelector[4];
extern "C" int g_beSystem_metaObject[4];
extern "C" int g_igViewerSceneInfoManager_metaObject[4];
extern "C" unsigned char g_useOwnerAllocator;
struct Ref {
    Rc *p;
    Ref(Rc *x) : p(x) {}
    ~Ref() {
        Rc *object = p;
        if (object) {
            --object->rc;
            if (((unsigned long long)(long long)object->rc & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
struct M { char p[32]; int f32; int f36; };
struct O { char p[12]; M *f12; Rc *f16; int f20; int f24; };
extern "C" void Gap__Bec__bePadManager__vfunc_23(O *o);
extern "C" void Gap__Bec__bePadManager__vfunc_24(bePadManager *arg0);
extern "C" int g_bePadManager_metaObject[4];
/* matching construct: dummy-virtual pad device class; real slots are v28 (+120), v29 (+124), v30 (+128), v32 (+136) */
class Pad { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual int v28(); virtual int v29(int, float *, float *); virtual int v30(); virtual void d31(); virtual int v32(); };
struct Vec2 { float x, y; };
extern "C" int bePadData_UpdateLeftStick(bePadData *, Vec2 *);
extern "C" int bePadData_UpdateRightStick(bePadData *, Vec2 *);
extern "C" void Gap__Bec__bePadManager__vfunc_27(bePadManager *arg0);
extern "C" int bePadManager_GetPadForPlayer(bePadManager *arg0, int arg1);

/* Hands the object to the insight core's helper igInsightCore_AddToScheduler, which asks the scheduler at +12 of
 * the insight object (_insight) whether it already has the object (scheduler slot 26) and, if not,
 * calls scheduler slot 24 with it. Same body as beMessenger slot 21. The second argument is
 * unused. */
void Gap__Bec__bePadManager__vfunc_21(bePadManager *self, int unusedArg)
{
    igInsightCore_AddToScheduler(self->_insight, (char *)self);
}

/* Counterpart of slot 21 through igInsightCore_RemoveFromScheduler, which calls scheduler slot 25 with the object only
 * when scheduler slot 26 reports it present. Same body as beMessenger slot 22. The second argument
 * is unused. */
void Gap__Bec__bePadManager__vfunc_22(bePadManager *self, int unusedArg)
{
    igInsightCore_RemoveFromScheduler(self->_insight, (char *)self);
}

void Gap__Bec__bePadManager__vfunc_23(O *o) {
    Rc *t0 = (Rc *)igInsightCore_FindManager(o->f12, g_beSystem_metaObject[0]);
    if (t0 != 0) t0->rc = t0->rc + 1;
    {
        Rc *a0 = o->f16;
        if (a0 != 0) {
            a0->rc = a0->rc - 1;
            if (((unsigned long long)((long long)a0->rc << 0x29) >> 0x29) == 0) igObject_Destroy(a0);
        }
    }
    o->f16 = t0;
    for (int i = 0; i < 5; i++) {
        int v0 = igObject_GetAllocator(o);
        Ref sp3C((Rc *)FUN_0034ce50(g_useOwnerAllocator != 0 ? v0 : Memory_GetAllocatorBySelector(g_ndmwAllocatorSelector[0])));
        ObjectList_AppendRetained(o->f20, sp3C.p);
    }
    M *m = o->f12;
    int s0 = m->f32;
    FUN_004542d0(s0, o->f24, m->f36);
    FUN_00454290(s0, o->f24);
    char *v = (char *)igInsightCore_FindManager(o->f12, g_igViewerSceneInfoManager_metaObject[0]);
    int s = *(int *)(v + 132);
    FUN_004574f0(s, 15);
    FUN_004574f0(s, 3);
    FUN_004574f0(s, 0);
    FUN_004574f0(s, 10);
    FUN_004574f0(s, 11);
    FUN_004574f0(s, 1);
    FUN_004574f0(s, 2);
    FUN_004574f0(s, 12);
    FUN_00462e90(v);
}

void Gap__Bec__bePadManager__vfunc_24(bePadManager *arg0) {
    int temp_s0;
    void *temp_v0;

    temp_v0 = (void *)arg0->_insight;
    temp_s0 = *(int *)((char *)(temp_v0) + 32);
    FUN_004542e0(temp_s0, arg0->_kbReceiver, *(int *)((char *)(temp_v0) + 36));
    FUN_004542a0(temp_s0, arg0->_kbReceiver);
}

int Gap__Bec__bePadManager__vfunc_25(void) {
    return 0;
}

void Gap__Bec__bePadManager__vfunc_26(void)
{
}

void Gap__Bec__bePadManager__vfunc_27(bePadManager *arg0) {
    int b;
    bool flag;
    int i;
    unsigned short st;
    igControllerList *list;
    Pad *pad;
    bePadData *slot;
    Vec2 out;
    Vec2 t1;
    Vec2 t2;
    Vec2 t3;
    Vec2 t4;
    if (((beSystem *)arg0->_system)->_isFrameSkip == 0) {
        flag = false;
        list = (igControllerList *)((igControllerManager *)((igEventDispatcher *)((igInsightCore *)arg0->_insight)->_dispatcher)->_controllerManager)->_controllers;
        for (i = 0; i < list->_count; i++) {
            pad = ((Pad **)list->_data)[i];
            st = pad->v30();
            b = (unsigned char)pad->v32();
            if (st == 2) {
                if (b == 0) continue;
                flag = true;
            }
            if (st == 1) {
                if (flag) continue;
                flag = true;
                st = 2;
            }
            if ((unsigned short)((unsigned)st >> 1) < 4) {
                bePadDataList *pads = (bePadDataList *)arg0->_padList;
                slot = ((bePadData **)pads->_data)[(unsigned short)((unsigned)st >> 1)];
                slot->_isConnect = b;
                if (b != 0) {
                    pad->v29(0, &out.x, &out.y);
                    t1.x = out.x; t1.y = out.y;
                    bePadData_UpdateLeftStick(slot, &t1);
                    pad->v29(1, &out.x, &out.y);
                    t2.x = out.x; t2.y = out.y;
                    bePadData_UpdateRightStick(slot, &t2);
                    bePadData_UpdateButtons(slot, pad->v28());
                } else {
                    t3.x = 0; t3.y = 0;
                    bePadData_UpdateLeftStick(slot, &t3);
                    t4.x = 0; t4.y = 0;
                    bePadData_UpdateRightStick(slot, &t4);
                    bePadData_UpdateButtons(slot, 0);
                }
            }
        }
    }
}

/* _padList is a bePadDataList whose backing array (_data) holds the pad record pointers */
int bePadManager_GetPadForPlayer(bePadManager *arg0, int arg1) {
    if (arg0->_isPadDisable != 0) {
        return *(int *)(((bePadDataList *)arg0->_padList)->_data + 16);
    }
    if (arg1 < 4) {
        return *(int *)(((bePadDataList *)arg0->_padList)->_data + (arg1 * 4));
    }
    return *(int *)(((bePadDataList *)arg0->_padList)->_data + 16);
}

int Gap__Bec__bePadManager__vfunc_20(void)
{
    return g_bePadManager_metaObject[0];
}
