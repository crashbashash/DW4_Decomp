#include "dw4/reflected.h"
extern "C" {
int beMessenger_SelectGroup(int, int *);
int beMessenger_AppendInt(int, int);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_GetObject(int, int);
void *igProperty_GetRecord(void *, int *);
void *igProperty_GetRecordFolder(void *, int *);
int igObject_GetAllocator(void *);
int Memory_GetAllocatorBySelector(int);
void *FUN_002caa70(int);
int List_Resize(void *, int, int);
int igObject_Destroy(void *);
extern int DAT_0051b398[4];
extern int DAT_0051b3e8[4];
extern int DAT_0051bac0[4];
extern int DAT_0051bc48[4];
extern int DAT_004cfa30[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;

}
typedef struct { char pad[12]; int f12; } Rec2;
#define CNT(x) ((x)->_count)
#define REL(t) if ((t) != 0) { (t)->_refCount = (t)->_refCount - 1; if (((unsigned long long)((long long)(int)(t)->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(t); }

/* Working list reference held across the List_Resize call. */
struct ListRef {
    igIntList *p;
    ListRef(igIntList *x) { p = x; }
    ~ListRef() {
        igIntList *o;
        /* matching construct: (o = p) != 0 shares the load of the held pointer with the loop reads, as retail */
        if ((o = p) != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o);
        }
    }
};
extern "C" int FUN_00432d30(beNDMWShopCtrlDigilabo *arg0) {
    int cn;
    int v1;
    igObjectList *folder;
    int j;
    igIntList *list;
    Rec2 *e;
    int v0;
    int k2;
    int al;
    int *rec;
    int o4;
    int o5;
    int off;
    void *obj;
    int c;
    int *src;
    igIntList *t;
    int al2;
    int w;
    igIntList *l;
    int k;
    int o2;
    int o3;
    int *arr;
    int s0;
    igIntList *l2;
    igIntList *t2;
    int r;
    if (arg0->_isDigimonChange != 0 || arg0->_isWeaponChange != 0) {
        cn = 0;
        off = 0;
        if (0 < ((igIntList *)arg0->_playerNoList)->_count) {
            do {
                s0 = *(int *)(((igIntList *)arg0->_playerNoList)->_data + off);
                beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b398[0]);
                beMessenger_AppendInt(arg0->_messenger, s0);
                beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3e8[0]);
                obj = (void *)beMessenger_GetObject(arg0->_messenger, 0);
                rec = (int *)igProperty_GetRecord(obj, &DAT_0051bac0[0]);
                if (rec[3] != *(int *)(((igIntList *)arg0->_digimonNoList)->_data + off)) return 1;
                folder = (igObjectList *)(((int *)igProperty_GetRecordFolder(obj, &DAT_0051bc48[0]))[3]);
                list = (igIntList *)*(int *)(((igIntList *)arg0->_wpuNoListList)->_data + off);
                al = igObject_GetAllocator(arg0);
                if (GPR_00554c14 != 0) {
                    al2 = al;
                } else {
                    al2 = Memory_GetAllocatorBySelector(DAT_00587110[0]);
                }
                {
                ListRef sp((igIntList *)FUN_002caa70(al2));
                v0 = 0;
                if (0 < list->_count) {
                    o2 = 0;
                    do {
                        src = (int *)((char *)list->_data + o2);
                        l = sp.p;
                        c = l->_count;
                        if (c < l->_capacity) {
                            l->_count = *(const int *)&l->_count + 1;
                        } else {
                            List_Resize(l, c + 1, 4);
                        }
                        ((int *)l->_data)[c] = *src;
                        v0++;
                        o2 += 4;
                    } while (v0 < list->_count);
                }
                v1 = 0;
                j = 0;
                if (0 < folder->_count) {
                    o3 = 0;
                    do {
                        e = *(Rec2 **)(folder->_data + o3);
                        if (e != 0) {
                            w = e->f12;
                            v1++;
                            l = sp.p;
                            o4 = 0;
                            if (0 < CNT(l)) {
                                k = 0;
                                l2 = l;
                                do {
                                    int x = *(int *)(l2->_data + k);
                                    if (x != -1 && w == x) {
                                        if (CNT(l) != 0 && o4 >= 0 && o4 < CNT(l)) {
                                            ((int *)l->_data)[o4] = DAT_004cfa30[0];
                                        }
                                        break;
                                    }
                                    o4++;
                                    k += 4;
                                    l2 = l;
                                } while (o4 < CNT(l));
                            }
                        }
                        j++;
                        o3 += 4;
                    } while (j < folder->_count);
                }
                if (v1 != list->_count) {
                    return 1;
                }
                t = sp.p;
                k2 = 0;
                if (0 < CNT(t)) {
                    o5 = 0;
                    t2 = t;
                    do {
                        if (*(int *)(t2->_data + o5) != -1) {
                            return 1;
                        }
                        k2++;
                        o5 += 4;
                        t2 = t;
                    } while (k2 < CNT(t));
                }
                }
                cn = cn + 1;
                off += 4;
                r = ((igIntList *)arg0->_playerNoList)->_count > cn;
            } while (r);
        }
    }
    return 0;
}
