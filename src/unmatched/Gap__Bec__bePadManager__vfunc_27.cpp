#include "dw4/reflected.h"
/* matching construct: dummy-virtual pad device class; real slots are v28 (+120), v29 (+124), v30 (+128), v32 (+136) */
class Pad { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual int v28(); virtual int v29(int, float *, float *); virtual int v30(); virtual void d31(); virtual int v32(); };
struct Vec2 { float x, y; };
extern "C" {
int FUN_0039af10(...);
int FUN_0039af90(bePadData *, Vec2 *);
int FUN_0039b050(bePadData *, Vec2 *);
void Gap__Bec__bePadManager__vfunc_27(bePadManager *arg0);
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
                    FUN_0039af90(slot, &t1);
                    pad->v29(1, &out.x, &out.y);
                    t2.x = out.x; t2.y = out.y;
                    FUN_0039b050(slot, &t2);
                    FUN_0039af10(slot, pad->v28());
                } else {
                    t3.x = 0; t3.y = 0;
                    FUN_0039af90(slot, &t3);
                    t4.x = 0; t4.y = 0;
                    FUN_0039b050(slot, &t4);
                    FUN_0039af10(slot, 0);
                }
            }
        }
    }
}
