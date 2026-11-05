#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int FUN_003f9570(beNDMWGameRam *);
extern char DAT_00518828[];
int FUN_003a9340(int, char *);
int ObjectList_AppendRetained(igObjectList *, int);
int igObject_Destroy(igObject *);
/* igProperty_GetRecordFolder result: a record whose +12 is an igObjectList; no reflected class */
struct W { char pad[12]; igObjectList *f12; };
void FUN_003f99f0(beNDMWGameRam *arg0, int arg1, void *arg2, int *arg3) {
    igObjectList *l;
    struct W *w;
    int n;
    int n2;
    int i;
    int j;
    igObject *p;

    FUN_003f9570(arg0);
    w = (struct W *)FUN_003a9340(((int *)(((igObjectList *)arg0->_playerDataListList)->_data))[arg1], DAT_00518828);
    l = w->f12;
    if (*(volatile int *)&l->_count != 0) {
        n = l->_count;
        for (i = 0; i < n; i++) {
            p = ((igObject **)l->_data)[i];
            if (p != 0) {
                p->_refCount = p->_refCount - 1;
                if ((p->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        n2 = l->_count;
        for (j = 0; j < n2; j++) {
            ((igObject **)l->_data)[j] = 0;
        }
        l->_count = 0;
    }
    ObjectList_AppendRetained(l, *arg3);
}
} /* extern "C" */
