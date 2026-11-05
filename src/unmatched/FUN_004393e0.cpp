#include "dw4/reflected.h"
extern "C" {
int FUN_00236f80(...);
int FUN_00447d00(...);
int FUN_00447ed0(...);
int sprintf(...);
int FUN_002eb010(...);
int StringPool_Construct(...);
char *StringPool_Intern(...);
int StringChunk_ReleaseHeader(...);
int FUN_0030b3c0(...);
int strlen(...);
int FUN_0030b460(...);
int igObject_Destroy(...);
int FUN_00439f30(...);
char *beNDMWItemBase_GetRecordString(...);
int beMessenger_SelectGroup(...);
int beMessenger_AppendString(...);
int beMessenger_AppendVec3(...);
int beMessenger_DispatchSelected(...);
extern char *DAT_004cf8a0[12];
extern char *DAT_004c22f0[4];
extern int DAT_00586f20[4];
extern int DAT_00587d08[4];
extern int DAT_0058b028[4];
extern char DAT_0051b3c0[], DAT_0051b3c8[], DAT_0051b468[], DAT_0051b470[], DAT_0051b550[], DAT_0051b558[];
extern char DAT_0051b678[], DAT_0051b680[], DAT_0051b690[], DAT_0051b6a8[], DAT_0051b6b0[], DAT_0051b6b8[];
extern char DAT_0051b9f8[], DAT_0051bd60[];
struct Pad5 { char c[5]; } __attribute__((aligned(16)));
extern Pad5 DAT_0051bdc0;
}
struct Vec3 { float x, y, z; } __attribute__((aligned(16)));
struct Ref { igStringObj *const p; Ref(igStringObj *x) : p(x) {} ~Ref() { igStringObj *q = p; if (q) { q->_refCount = q->_refCount - 1; if ((q->_refCount & 0x7fffff) == 0) igObject_Destroy(q); } } };
struct Str {
    char *p;
    Str() { p = 0; }
    ~Str() { Rel(); }
    void Rel() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
    void Set(char *n) { Rel(); p = n; }
};
struct Pool { static char *Intern(char *s) { if (DAT_00586f20[0] == 0) { int v = FUN_002eb010(16); if (v != 0) v = StringPool_Construct(v); DAT_00586f20[0] = v; } return StringPool_Intern(DAT_00586f20[0], s); } };
#define LIST(p) ((igObjectList *)(p))
extern "C" void FUN_004393e0(beNDMWShopCtrlSales *arg0, int arg1, unsigned char arg2);
void FUN_004393e0(beNDMWShopCtrlSales *arg0, int arg1, unsigned char arg2) {
    int rec;
    int i;
    beNDMWItemRevisionPocketBase *it;
    char *name;
    rec = FUN_00236f80(arg0->_insight, DAT_0058b028[0]);
    if (arg1 != 0) {
        i = 0;
        do {
            Str str;
            it = 0;
            int idx = i + arg0->_nowPage * 12;
            if (idx < LIST(arg0->_salesItemList)->_count) it = (beNDMWItemRevisionPocketBase *)((int *)LIST(arg0->_salesItemList)->_data)[idx];
            if (it != 0) {
                Vec3 pos;
                Vec3 pos2;
                Pad5 buf;
                name = beNDMWItemBase_GetRecordString(it, rec, DAT_0051b678);
                beMessenger_SelectGroup(arg0->_messenger, DAT_0051b3c0);
                beMessenger_AppendString(arg0->_messenger, DAT_0051b3c8);
                beMessenger_AppendString(arg0->_messenger, DAT_004cf8a0[i]);
                beMessenger_AppendString(arg0->_messenger, name);
                beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b6b0);
                FUN_00447d00(&pos, it);
                beMessenger_SelectGroup(arg0->_messenger, DAT_0051b3c0);
                beMessenger_AppendString(arg0->_messenger, DAT_0051b3c8);
                beMessenger_AppendString(arg0->_messenger, DAT_004cf8a0[i]);
                pos2.x = pos.x; pos2.y = pos.y; pos2.z = pos.z;
                beMessenger_AppendVec3(arg0->_messenger, &pos2);
                beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b9f8);
                if (it->_kindNo == 3 && it->_recNo == 185) {
                    buf = DAT_0051bdc0;
                } else {
                    sprintf(&buf, DAT_0051b468, FUN_00447ed0(it, rec, DAT_0051b690));
                }
                beMessenger_SelectGroup(arg0->_messenger, DAT_0051b3c0);
                beMessenger_AppendString(arg0->_messenger, DAT_0051b680);
                beMessenger_AppendString(arg0->_messenger, DAT_004cf8a0[i]);
                beMessenger_AppendString(arg0->_messenger, (char *)&buf);
                beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b6b0);
                str.Set(Pool::Intern(DAT_0051b6b8));
            } else {
                str.Set(Pool::Intern(DAT_0051b550));
            }
            beMessenger_SelectGroup(arg0->_messenger, DAT_0051b3c0);
            beMessenger_AppendString(arg0->_messenger, DAT_0051b3c8);
            beMessenger_AppendString(arg0->_messenger, DAT_004cf8a0[i]);
            beMessenger_AppendString(arg0->_messenger, str.p);
            beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b558);
            beMessenger_SelectGroup(arg0->_messenger, DAT_0051b3c0);
            beMessenger_AppendString(arg0->_messenger, DAT_0051b680);
            beMessenger_AppendString(arg0->_messenger, DAT_004cf8a0[i]);
            beMessenger_AppendString(arg0->_messenger, str.p);
            beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b558);
        } while (++i < 12);
        char dig[2];
        dig[1] = 0;
        dig[0] = arg0->_nowPage + 49;
        beMessenger_SelectGroup(arg0->_messenger, DAT_0051b3c0);
        beMessenger_AppendString(arg0->_messenger, DAT_0051bd60);
        beMessenger_AppendString(arg0->_messenger, DAT_004cf8a0[0]);
        beMessenger_AppendString(arg0->_messenger, dig);
        beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b6b0);
        dig[0] = arg0->_maxPage + 48;
        beMessenger_SelectGroup(arg0->_messenger, DAT_0051b3c0);
        beMessenger_AppendString(arg0->_messenger, DAT_0051bd60);
        beMessenger_AppendString(arg0->_messenger, DAT_004cf8a0[1]);
        beMessenger_AppendString(arg0->_messenger, dig);
        beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b6b0);
    }
    if (arg2) {
        int base = arg0->_nowPage * 12; it = (beNDMWItemRevisionPocketBase *)((int *)LIST(arg0->_salesItemList)->_data)[base + arg0->_retCode];
        char *label;
        if (it != 0) {
            name = beNDMWItemBase_GetRecordString(it, rec, DAT_0051b6a8);
            if (it->_kindNo == 0 || it->_kindNo == 1) {
                char dig[2];
                dig[1] = 0;
                dig[0] = it->_pocket + 48;
                Ref rc((igStringObj *)((beSystem *)FUN_00236f80(arg0->_insight, DAT_00587d08[0]))->_globalStrObj);
                if (rc.p != 0) rc.p->_refCount = rc.p->_refCount + 1;
                FUN_0030b3c0(rc.p, name);
                igStringObj *t = rc.p;
                i = t->_length;
                FUN_0030b460(t, dig, i, strlen(dig));
                name = (rc.p->_buffer == 0) ? DAT_004c22f0[0] : (char *)rc.p->_buffer;
            }
            beMessenger_SelectGroup(arg0->_messenger, DAT_0051b3c0);
            beMessenger_AppendString(arg0->_messenger, DAT_0051b470);
            beMessenger_AppendString(arg0->_messenger, DAT_004cf8a0[0]);
            beMessenger_AppendString(arg0->_messenger, name);
            beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b6b0);
            label = DAT_0051b6b8;
            FUN_00439f30(arg0, 1);
        } else {
            label = DAT_0051b550;
            FUN_00439f30(arg0, 0);
        }
        beMessenger_SelectGroup(arg0->_messenger, DAT_0051b3c0);
        beMessenger_AppendString(arg0->_messenger, DAT_0051b470);
        beMessenger_AppendString(arg0->_messenger, DAT_004cf8a0[0]);
        beMessenger_AppendString(arg0->_messenger, label);
        beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b558);
    }
}
