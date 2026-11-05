/* 0x00457ab0 - FUN_00457ab0. Stack key lookup (destructor copy at 0x002e2300), two 16-byte message objects, member pointer kept in a local. */
#include "dw4/reflected.h"
extern "C" {
void FUN_002ed5c0(void *);
int FUN_004578c0(void *, void *);
int FUN_00457c40(void *, int, void *);
extern int DAT_0058c280[4];
}
struct K { void *p; K(void *x) { p = x; } ~K() { } static void operator delete(void *q) { FUN_002ed5c0(q); } };
struct Msg { int a; int b; int c; int d; };
struct Finder {
    static int Find(igObjectList *l, K &key) {
        int n = l->_count;
        int i = 0;
        for (; i < n; i++) {
            if (key.p == ((void **)l->_data)[i]) {
                return i;
            }
        }
        return -1;
    }
};
extern "C" {
void FUN_00457ab0(igRadioGroup *arg0, igRadioGroupSelectedObserver *arg1, int arg2) {
    int idx;
    int flag;
    igObjectList *l;
    igRadioGroupModel *s;
    int *pf;
    l = (igObjectList *)arg0->_observerList;
    flag = ((igOnOffModel *)arg1->_model)->_value;
    K key(arg1);
    idx = Finder::Find(l, key);
    if (flag != 0) {
        s = (igRadioGroupModel *)arg0->_model;
        pf = &s->_selected;
        if (idx != s->_selected) {
            *pf = idx;
            Msg m;
            m.a = 2;
            m.b = 0;
            m.c = DAT_0058c280[0];
            FUN_004578c0((void *)arg0->_model, &m);
        }
    } else {
        s = (igRadioGroupModel *)arg0->_model;
        pf = &s->_selected;
        if (idx == s->_selected) {
            if (arg0->_alwaysSelected != 0) {
                FUN_00457c40(arg1, 1, pf);
                return;
            }
            *pf = -1;
            Msg m2;
            m2.a = 2;
            m2.b = 0;
            m2.c = DAT_0058c280[0];
            FUN_004578c0((void *)arg0->_model, &m2);
        }
    }
}
}
