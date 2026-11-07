#include "dw4/reflected.h"
typedef struct S { char pad[8]; igObjectList *l8; igObjectList *l12; } S;
int FUN_00303e50(S *);
int List_RemoveWordAt(igObjectList *, int);
int igObject_Destroy(igObject *);
#define REL(o) if ((o) != 0) { (o)->_refCount = (int)(o)->_refCount - 1; if (((unsigned long long)((long long)(int)(o)->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(o); } }
void FUN_00304030(S *arg0, int arg1) {
    /*D*/
    igObject *o;
    igObjectList *l2;
    int c2;
    igObjectList *l6;
    int c1;
    igObjectList *l3;
    int idx;
    igObject *s6b;
    igObject *s6;
    igObjectList *l4;
    igObjectList *l1;
    int s4;
    igObjectList *l5;
    int a4;
    /*E*/
    idx = FUN_00303e50(arg0);
    l1 = arg0->l12;
    s4 = 4 * idx;
    s6 = ((igObject **)((char *)l1->_data + s4 - 4))[0];
    if (s6) { s6->_refCount = 1 + (int)s6->_refCount; }
    a4 = 4 * arg1;
    o = ((igObject **)((char *)l1->_data + a4))[0];
    REL(o)
    if (l1->_count && arg1 >= 0 && arg1 < l1->_count) { ((igObject **)((char *)l1->_data + a4))[0] = s6; }
    l2 = arg0->l12;
    o = ((igObject **)(s4 + (char *)l2->_data - 4))[0];
    REL(o)
    if (l2->_count && idx - 1 >= 0 && idx - 1 < l2->_count) { ((igObject **)((char *)(s4 + (int)(igObject **)l2->_data) - 4))[0] = 0; }
    l3 = arg0->l12;
    c1 = l3->_count - 1;
    o = ((igObject **)(l3->_data + c1 * 4))[0];
    REL(o)
    List_RemoveWordAt(l3, c1);
    ((igObject **)(l3->_data + 4 * l3->_count))[0] = 0;
    l4 = arg0->l8;
    s6b = ((igObject **)(s4 + (char *)l4->_data - 4))[0];
    if (s6b) { s6b->_refCount = 1 + (int)s6b->_refCount; }
    o = ((igObject **)((char *)l4->_data + a4))[0];
    REL(o)
    if (l4->_count && arg1 >= 0 && arg1 < l4->_count) { ((igObject **)(a4 + (char *)l4->_data))[0] = s6b; }
    l5 = arg0->l8;
    o = ((igObject **)((char *)l5->_data + s4 - 4))[0];
    REL(o)
    if (l5->_count && idx - 1 >= 0 && idx - 1 < l5->_count) { ((igObject **)((char *)(s4 + (int)(igObject **)l5->_data) - 4))[0] = 0; }
    l6 = arg0->l8;
    c2 = l6->_count - 1;
    o = ((igObject **)(l6->_data + 4 * c2))[0];
    REL(o)
    List_RemoveWordAt(l6, c2);
    ((igObject **)(l6->_data + l6->_count * 4))[0] = 0;
}
