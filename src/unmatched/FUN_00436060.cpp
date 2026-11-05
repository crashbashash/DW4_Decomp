#include "dw4/reflected.h"
extern "C" {
int sprintf(...);
int strlen(...);
void *FUN_00236f80(...);
int FUN_0030b3c0(...);
int FUN_0030b460(...);
int FUN_00447d00(...);
int FUN_00447ed0(...);
int beMessenger_AppendInt(...);
int beMessenger_AppendString(...);
int beMessenger_AppendVec3(...);
int beMessenger_DispatchSelected(...);
int beMessenger_GetObject(...);
int beMessenger_SelectGroup(...);
char *beNDMWItemBase_GetRecordString(...);
void igObject_Destroy(void *);
char *igProperty_GetRecordFolder(...);
extern char *DAT_004c22f0[4];
extern char *DAT_004cf8a0[12];
extern char *DAT_004cf8a4[4];
extern int DAT_0051b398[];
extern int DAT_0051b3c0[];
extern char DAT_0051b3c8[];
extern int DAT_0051b3d8[];
extern int DAT_0051b3e8[];
extern int DAT_0051b468[];
extern char DAT_0051b470[];
extern int DAT_0051b528[];
extern char DAT_0051b550[];
extern int DAT_0051b558[];
extern int DAT_0051b678[];
extern char DAT_0051b680[];
extern int DAT_0051b6a8[];
extern int DAT_0051b6b0[];
extern char DAT_0051b6b8[];
extern int DAT_0051b800[];
extern int DAT_0051b9f8[];
extern char DAT_0051bd60[];
extern int DAT_0051bd70[];
extern char DAT_0051bd78[];
extern char DAT_0051bd80[];
extern int DAT_00587d08[];
extern int DAT_0058b028[];
void FUN_00436060(beNDMWShopCtrlDeviceSell *self, int full, unsigned char sel);
}
/* matching construct: raw view of the property-record folder (list at +12). */
struct RecordFolder { int w0; int w4; int w8; igDataList *list; };
struct V3 { float x, y, z; };
/* Owning stack reference to the system's shared string object: retained while the shop labels are built and
 * released on scope exit (reference count in the low 23 bits of _refCount).  The out-of-line copy the
 * exception table names is the retail body 0x001489a0 (config/SLUS-20836/unit-objects.json, duplicate __dt__9ObjectRefFv). */
class ObjectRef {
public:
    igStringObj *p;
    ObjectRef(igStringObj *o) : p(o) {}
    ~ObjectRef() { igStringObj *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};

void FUN_00436060(beNDMWShopCtrlDeviceSell *self, int full, unsigned char sel)
{
    beMessenger_SelectGroup(self->_messenger, &DAT_0051b398[0]);
    beMessenger_AppendInt(self->_messenger, self->_playerNo);
    beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3e8[0]);
    igDataList *folder = ((RecordFolder *)igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), &DAT_0051b528[0]))->list;
    ObjectRef str((igStringObj *)((int *)FUN_00236f80(self->_insight, DAT_00587d08[0]))[18]);
    if (str.p != 0) str.p->_refCount = str.p->_refCount + 1;
    char numbuf[2];
    char nb2[2];
    char nb3[2];
    char name[16];
    V3 vA;
    V3 vB;
    if (full != 0) {
        int i = 0;
        do {
            int idx = i + self->_nowPage * 12;
            const char *s;
            if (idx < folder->_count) {
                void *c = FUN_00236f80(self->_insight, DAT_0058b028[0]);
                beNDMWItemBase *o = *(beNDMWItemBase **)(folder->_data + idx * 4);
                FUN_0030b3c0(str.p, beNDMWItemBase_GetRecordString(o, c, &DAT_0051b678[0]));
                if (o->_isEquip != 0) { igStringObj *t = str.p; FUN_0030b460(t, &DAT_0051bd78[0], 0, strlen(&DAT_0051bd78[0])); }
                else { igStringObj *t = str.p; FUN_0030b460(t, &DAT_0051bd80[0], 0, strlen(&DAT_0051bd80[0])); }
                beMessenger_SelectGroup(self->_messenger, &DAT_0051b3c0[0]);
                beMessenger_AppendString(self->_messenger, &DAT_0051b3c8[0]);
                beMessenger_AppendString(self->_messenger, DAT_004cf8a0[i]);
                {
                    int m = self->_messenger;
                    char *t0 = (char *)str.p->_buffer;
                    char *t;
                    if (t0 == 0) t = DAT_004c22f0[0]; else t = t0;
                    beMessenger_AppendString(m, t);
                }
                beMessenger_DispatchSelected(self->_messenger, &DAT_0051b6b0[0]);
                sprintf(name, &DAT_0051b468[0], FUN_00447ed0(o, c, &DAT_0051bd70[0]));
                beMessenger_SelectGroup(self->_messenger, &DAT_0051b3c0[0]);
                beMessenger_AppendString(self->_messenger, &DAT_0051b680[0]);
                beMessenger_AppendString(self->_messenger, DAT_004cf8a0[i]);
                beMessenger_AppendString(self->_messenger, name);
                beMessenger_DispatchSelected(self->_messenger, &DAT_0051b6b0[0]);
                FUN_00447d00(&vA, o);
                beMessenger_SelectGroup(self->_messenger, &DAT_0051b3c0[0]);
                beMessenger_AppendString(self->_messenger, &DAT_0051b3c8[0]);
                beMessenger_AppendString(self->_messenger, DAT_004cf8a0[i]);
                vB = vA;
                beMessenger_AppendVec3(self->_messenger, &vB);
                beMessenger_DispatchSelected(self->_messenger, &DAT_0051b9f8[0]);
                if (*(unsigned char *)(((igUnsignedCharList *)self->_decideList)->_data + i) != 0) {
                    beMessenger_SelectGroup(self->_messenger, &DAT_0051b3c0[0]);
                    beMessenger_AppendString(self->_messenger, &DAT_0051b680[0]);
                    beMessenger_AppendString(self->_messenger, DAT_004cf8a0[i]);
                    beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3d8[0]);
                } else {
                    beMessenger_SelectGroup(self->_messenger, &DAT_0051b3c0[0]);
                    beMessenger_AppendString(self->_messenger, &DAT_0051b680[0]);
                    beMessenger_AppendString(self->_messenger, DAT_004cf8a0[i]);
                    beMessenger_DispatchSelected(self->_messenger, &DAT_0051b800[0]);
                }
                s = &DAT_0051b6b8[0];
            } else {
                s = &DAT_0051b550[0];
            }
            beMessenger_SelectGroup(self->_messenger, &DAT_0051b3c0[0]);
            beMessenger_AppendString(self->_messenger, &DAT_0051b3c8[0]);
            beMessenger_AppendString(self->_messenger, DAT_004cf8a0[i]);
            beMessenger_AppendString(self->_messenger, s);
            beMessenger_DispatchSelected(self->_messenger, &DAT_0051b558[0]);
            beMessenger_SelectGroup(self->_messenger, &DAT_0051b3c0[0]);
            beMessenger_AppendString(self->_messenger, &DAT_0051b680[0]);
            beMessenger_AppendString(self->_messenger, DAT_004cf8a0[i]);
            beMessenger_AppendString(self->_messenger, s);
            beMessenger_DispatchSelected(self->_messenger, &DAT_0051b558[0]);
            i++;
        } while (i < 12);
        numbuf[1] = 0;
        numbuf[0] = self->_nowPage + 0x31;
        beMessenger_SelectGroup(self->_messenger, &DAT_0051b3c0[0]);
        beMessenger_AppendString(self->_messenger, &DAT_0051bd60[0]);
        beMessenger_AppendString(self->_messenger, DAT_004cf8a0[0]);
        beMessenger_AppendString(self->_messenger, numbuf);
        beMessenger_DispatchSelected(self->_messenger, &DAT_0051b6b0[0]);
        numbuf[0] = self->_maxPage + 0x30;
        beMessenger_SelectGroup(self->_messenger, &DAT_0051b3c0[0]);
        beMessenger_AppendString(self->_messenger, &DAT_0051bd60[0]);
        beMessenger_AppendString(self->_messenger, DAT_004cf8a4[0]);
        beMessenger_AppendString(self->_messenger, numbuf);
        beMessenger_DispatchSelected(self->_messenger, &DAT_0051b6b0[0]);
    }
    if (sel) {
        int rc = self->_retCode; int pg = self->_nowPage * 12; int idx = pg + rc;
        const char *s;
        if (idx < folder->_count) {
            char *txt;
            void *c2 = FUN_00236f80(self->_insight, DAT_0058b028[0]);
            beNDMWItemBase *o = *(beNDMWItemBase **)(folder->_data + idx * 4);
            int kind;
            txt = beNDMWItemBase_GetRecordString(o, c2, &DAT_0051b6a8[0]);
            kind = o->_kindNo;
            if (kind == 0) {
                if (o->_recNo != 0x114) {
                    nb2[1] = 0;
                    nb2[0] = ((beNDMWItemBlueArmor *)o)->_pocket + 0x30;
                    FUN_0030b3c0(str.p, txt);
                    {
                        int t = (int)str.p;
                        int n = ((igStringObj *)t)->_length;
                        FUN_0030b460((igStringObj *)t, nb2, n, strlen(nb2));
                    }
                    { char *x = (char *)str.p->_buffer; txt = (x == 0) ? DAT_004c22f0[0] : x; }
                }
            } else if (kind == 1 && o->_recNo != 0x1f) {
                nb3[1] = 0;
                nb3[0] = ((beNDMWItemBlueArmor *)o)->_pocket + 0x30;
                FUN_0030b3c0(str.p, txt);
                {
                    int t = (int)str.p;
                    int n = ((igStringObj *)t)->_length;
                    FUN_0030b460((igStringObj *)t, nb3, n, strlen(nb3));
                }
                { char *x = (char *)str.p->_buffer; txt = (x == 0) ? DAT_004c22f0[0] : x; }
            }
            beMessenger_SelectGroup(self->_messenger, &DAT_0051b3c0[0]);
            beMessenger_AppendString(self->_messenger, &DAT_0051b470[0]);
            beMessenger_AppendString(self->_messenger, DAT_004cf8a0[0]);
            beMessenger_AppendString(self->_messenger, txt);
            beMessenger_DispatchSelected(self->_messenger, &DAT_0051b6b0[0]);
            s = &DAT_0051b6b8[0];
        } else {
            s = &DAT_0051b550[0];
        }
        beMessenger_SelectGroup(self->_messenger, &DAT_0051b3c0[0]);
        beMessenger_AppendString(self->_messenger, &DAT_0051b470[0]);
        beMessenger_AppendString(self->_messenger, DAT_004cf8a0[0]);
        beMessenger_AppendString(self->_messenger, s);
        beMessenger_DispatchSelected(self->_messenger, &DAT_0051b558[0]);
    }
}
