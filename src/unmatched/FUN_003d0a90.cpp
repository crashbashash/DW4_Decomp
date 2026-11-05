#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(igObject *);
}
struct Rel { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
extern "C" void FUN_003d0a90(int arg0, beNDMWPanelWazaInfoRam *arg1, int arg2, igObject *arg3);
void FUN_003d0a90(int arg0, beNDMWPanelWazaInfoRam *arg1, int arg2, igObject *arg3) {
    beNDMWPanelWazaInfoWork *s0 = (beNDMWPanelWazaInfoWork *)arg1->_work;
    beNDMWPanelObjectStat *c;
    if (arg1->_isRun != 0) {
        if (arg1->_st0 == 3) {
            arg1->_isRun = 1;
            s0->_isWindowGenerate = 1;
            s0->_isCursorGenerate = 0;
        }
        arg1->_st0 = 0;
        arg1->_st3 = 0;
        arg1->_st2 = 0;
        arg1->_st1 = 0;
    } else {
        arg1->_isRun = 1;
        s0->_isWindowGenerate = 1;
        s0->_isCursorGenerate = 0;
        arg1->_st0 = 0;
        arg1->_st3 = 0;
        arg1->_st2 = 0;
        arg1->_st1 = 0;
    }
    s0->_page = arg2;
    s0->_retIsFire = 0;
    if (arg3 != 0) {
        arg3->_refCount = arg3->_refCount + 1;
    }
    Rel::go((igObject *)s0->_playerWork);
    s0->_playerWork = (int)arg3;
    c = (beNDMWPanelObjectStat *)s0->_panelStat;
    if (arg3 != 0) {
        arg3->_refCount = arg3->_refCount + 1;
    }
    Rel::go((igObject *)c->_playerWork);
    c->_playerWork = (int)arg3;
}
