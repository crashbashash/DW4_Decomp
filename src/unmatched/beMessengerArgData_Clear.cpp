#include "dw4/reflected.h"
extern "C" {
int FUN_002eb010(int);
int List_Reserve(igDataList *, int, int);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
void *StringPool_Intern(int, int);
int igObject_Destroy(igObject *);
extern int DAT_00586f20[16];
void beMessengerArgData_Clear(beMessengerArgData *arg0);
}
void beMessengerArgData_Clear(beMessengerArgData *arg0) {
    igDataList *lo;
    int v;
    int v0;
    int *old;
    int *hd;
    int *s1;
    igDataList *l;
    igDataList *sl;
    int n1;
    int i1;
    int n2;
    int i2;

    arg0->_isRunCheck = 0;
    if (DAT_00586f20[0] == 0) {
        v = FUN_002eb010(0x10);
        if (v != 0) {
            v = StringPool_Construct(v);
        }
        DAT_00586f20[0] = v;
    }
    s1 = (int *)StringPool_Intern(DAT_00586f20[0], 0);
    old = (int *)arg0->_debugString;
    if (old != 0) {
        hd = old - 2;
        v0 = old[-1] - 1;
        old[-1] = v0;
        if (v0 == 0) {
            StringChunk_ReleaseHeader(*hd, hd);
        }
    }
    arg0->_debugString = (int)s1;
    ((igBoolList *)arg0->_boolList)->_count = 0;
    l = (igDataList *)arg0->_boolList;
    /* matching construct: list shrink guard spelled as nested ifs ("&&" or "> 4" changes the compare) */
    if (l->_capacity > 4) { if (l->_count < 5) List_Reserve(l, 4, 1); }
    ((igIntList *)arg0->_intList)->_count = 0;
    l = (igDataList *)arg0->_intList;
    if (l->_capacity > 4) { if (l->_count < 5) List_Reserve(l, 4, 4); }
    ((igFloatList *)arg0->_floatList)->_count = 0;
    l = (igDataList *)arg0->_floatList;
    if (l->_capacity > 4) { if (l->_count < 5) List_Reserve(l, 4, 4); }
    ((igLongList *)arg0->_longList)->_count = 0;
    l = (igDataList *)arg0->_longList;
    if (l->_capacity > 4) { if (l->_count < 5) List_Reserve(l, 4, 8); }
    ((igVec3fList *)arg0->_vec3fList)->_count = 0;
    l = (igDataList *)arg0->_vec3fList;
    if (l->_capacity > 4) { if (l->_count < 5) List_Reserve(l, 4, 12); }
    ((igMatrix44fList *)arg0->_matrix44fList)->_count = 0;
    l = (igDataList *)arg0->_matrix44fList;
    if (l->_capacity > 4) { if (l->_count < 5) List_Reserve(l, 4, 64); }
    sl = (igDataList *)arg0->_stringList;
    
    /* matching construct: separate n/i counters per loop and block-local rr/m/j fix register allocation */
    n1 = sl->_count;
    for (i1 = 0; i1 < n1; i1++) {
        int **slot = &((int **)sl->_data)[i1];
        int *rr;
        if (DAT_00586f20[0] == 0) {
            v = FUN_002eb010(0x10);
            if (v != 0) {
                v = StringPool_Construct(v);
            }
            DAT_00586f20[0] = v;
        }
        rr = (int *)StringPool_Intern(DAT_00586f20[0], 0);
        old = *slot;
        if (old != 0) {
            hd = old - 2;
            v0 = old[-1] - 1;
            old[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*hd, hd);
            }
        }
        *slot = rr;
    }
    
    sl->_count = 0;
    sl = (igDataList *)arg0->_stringList;
    if (sl->_capacity > 4) { if (sl->_count < 5) List_Reserve(sl, 4, 4); }
    lo = (igDataList *)arg0->_objectList;
    
    n2 = lo->_count;
    for (i2 = 0; i2 < n2; i2++) {
        igObject *o = ((igObject **)lo->_data)[i2];
        if (o != 0) {
            o->_refCount = (int)o->_refCount - 1;
            if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    
    {
        int m = lo->_count;
        int j;
        for (j = 0; j < m; j++) {
            ((igObject **)lo->_data)[j] = 0;
        }
    }
    lo->_count = 0;
    l = (igDataList *)arg0->_objectList;
    if (l->_capacity > 4) { if (l->_count < 5) List_Reserve(l, 4, 4); }
}
