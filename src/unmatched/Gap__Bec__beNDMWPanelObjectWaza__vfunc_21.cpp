#include "dw4/reflected.h"

/* 0x003ce960 - beNDMWPanelObjectWaza vfunc 21 (refresh the technique list panel). Alternate compiler -O3,p. */
extern "C" {
void igObject_Destroy(igObject *);
int sprintf(...);
int FUN_003cdef0(...);
int FUN_003ce4c0(...);
int List_Reserve(...);
int List_Resize(...);
int ObjectList_AppendRetained(int, int);
int beMessenger_AppendInt(...);
int beMessenger_DispatchSelected(...);
void *beMessenger_GetObject(...);
int beMessenger_SelectGroup(...);
int beNDMWItemBase_GetRecordInt(...);
int *beNDMWItemBase_GetRecordString(...);
struct Rec { char p[12]; int f12; };
Rec *igProperty_GetRecord(...);
Rec *igProperty_GetRecordFolder(...);
extern int DAT_005159f0[4];
extern int DAT_005159f8[4];
extern int DAT_00515a08[4];
extern int DAT_00515a18[4];
extern int DAT_00515a20[4];
extern int DAT_00515a28[4];
}
struct Rel { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
extern "C" void Gap__Bec__beNDMWPanelObjectWaza__vfunc_21(beNDMWPanelObjectWaza *arg0) {
    int spB0[3];
    int spA8[2];
    if (arg0->_playerDataList == 0) {
        beMessenger_SelectGroup(arg0->_messenger, DAT_005159f0);
        beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
        beMessenger_DispatchSelected(arg0->_messenger, DAT_005159f8);
        igObject *o = (igObject *)beMessenger_GetObject(arg0->_messenger, 0);
        if (o != 0) {
            o->_refCount = o->_refCount + 1;
        }
        Rel::go((igObject *)arg0->_playerDataList);
        arg0->_playerDataList = (int)o;
    }
    igObjectList *fl = (igObjectList *)igProperty_GetRecordFolder(arg0->_playerDataList, DAT_00515a08)->f12;
    igObjectList *l = (igObjectList *)arg0->_listFolder;
    int n1 = l->_count;
    int i1 = 0;
    if (0 < n1) {
        do {
            Rel::go(((igObject **)l->_data)[i1]);
            i1++;
        } while (i1 < n1);
    }
    int m = l->_count;
    for (int j = 0; j < m; j++) {
        ((igObject **)l->_data)[j] = 0;
    }
    l->_count = 0;
    int n2 = fl->_count;
    for (int k = 0; k < n2; k++) {
        ObjectList_AppendRetained(arg0->_listFolder, (int)((igObject **)fl->_data)[k]);
    }
    int cnt = ((igObjectList *)arg0->_listFolder)->_count;
    igIntList *d = (igIntList *)arg0->_listColor;
    if (d->_count < cnt) {
        if (!(cnt < *(volatile int *)&d->_count)) List_Reserve(d, cnt, 4);
    }
    d = (igIntList *)arg0->_listColor;
    if (cnt >= 0) {
        if (cnt <= d->_capacity) {
            d->_count = cnt;
        } else {
            List_Resize(d, cnt, 4);
        }
    }
    int c2 = ((igObjectList *)arg0->_listFolder)->_count;
    if (c2 != arg0->_listKazu) {
        arg0->_cursor = 0;
        arg0->_offset = 0;
        arg0->_listKazu = c2;
    }
    FUN_003ce4c0(arg0, spB0);
    int i = 0;
    do {
        int s3 = i + arg0->_playerNo * 4;
        int a = arg0->_lineMode;
        int s2 = (i + arg0->_offset) - a;
        if (a <= i) {
            igObjectList *v1 = (igObjectList *)arg0->_listFolder;
            if (s2 < v1->_count) {
                int s6 = s2 * 4;
                int s1 = 0;
                beNDMWItemBase *s0 = ((beNDMWItemBase **)v1->_data)[s2];
                int *s7 = beNDMWItemBase_GetRecordString(s0, arg0->_manager, DAT_00515a18);
                int s8 = igProperty_GetRecord(arg0->_playerDataList, DAT_00515a20)->f12;
                if (s8 < beNDMWItemBase_GetRecordInt(s0, arg0->_manager, DAT_00515a20)) {
                    s1 = 1;
                }
                if (arg0->_isNoHealing != 0) {
                    int t = s0->_recNo;
                    if (t >= 40 && t < 50) s1 = 2;
                }
                if (arg0->_isNoParaUp != 0) {
                    int t = s0->_recNo;
                    if (t >= 65 && t < 70) s1 = 2;
                    else if (t >= 75 && t < 85) s1 = 2;
                }
                if (arg0->_isNoCureling != 0) {
                    int t = s0->_recNo;
                    if (t >= 50 && t < 65) s1 = 2;
                }
                igIntList *w = (igIntList *)arg0->_listColor;
                int nn = w->_count;
                if (nn != 0 && s2 >= 0 && s2 < nn) {
                    ((int *)w->_data)[s2] = s1;
                }
                FUN_003cdef0(arg0, 0, s3, s7, s1);
            } else {
                FUN_003cdef0(arg0, 0, s3, 0, 0);
            }
        } else {
            FUN_003cdef0(arg0, 0, s3, 0, 0);
        }
        FUN_003cdef0(arg0, 2, s3, 0, 0);
        if (i == 0) {
            sprintf(spA8, DAT_00515a28, beNDMWItemBase_GetRecordInt(((beNDMWItemBase **)((igObjectList *)arg0->_listFolder)->_data)[arg0->_cursor + arg0->_offset], arg0->_manager, DAT_00515a20));
            FUN_003cdef0(arg0, 1, s3 / 4, spA8, 0);
        }
        i++;
    } while (i < 4);
}
