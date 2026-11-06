/* FUN_00418ac0 (0x00418ac0, 1828 B): MATCH under the alternate compiler
 * (local/mwcps2/combat/mwccps2.exe). Receiver beNDMWStatusCtrlD0: rebuilds the 12-slot page of the
 * item list through messenger scripts (arg1: page list, arg2: cursor detail). Built under the unit
 * profile (alternate compiler, -O3,p, exceptions on); the ObjectRef destructor is the destroy
 * action of the retail exception table and a duplicate of the retail body 0x001489a0. Matching
 * constructs (each measured): the function-level declaration order fixes vreg ids and so the
 * s-register colouring; `self = p0` and DAT_004cf670[i] (the compiler strength-reduces it into a
 * late-numbered pointer) put the receiver below the name pointer; the string length of the holder
 * is read into the dead loop counter `i` / `idx` (a second web gets a later id than the holder
 * reload); per-arm block locals for the record folder; `s = s2 == 0 ? default : s2` keeps the
 * unthreaded join of the null fallback. */
#include "dw4/reflected.h"
extern "C" {
int strlen(void *);
void *FUN_00236f80(int, int);
int FUN_0030b3c0(void *, char *);
int FUN_0030b460(void *, void *, int, int);
int FUN_00447d00(void *, void *);
int beMessenger_AppendInt(int, int);
int beMessenger_AppendString(int, void *);
int beMessenger_AppendVec3(int, void *);
int beMessenger_DispatchSelected(int, void *);
int beMessenger_GetObject(int, int);
int beMessenger_SelectGroup(int, void *);
char *beNDMWItemBase_GetRecordString(void *, void *, void *);
void igObject_Destroy(igStringObj *);
void *igProperty_GetRecordFolder(int, void *);
extern int DAT_00519ba0[4];
extern int DAT_00519ba8[4];
extern int DAT_0051a0c8[4];
extern int DAT_00519c00[4];
extern int DAT_0058b028[4];
extern int DAT_00587d08[4];
extern int DAT_00519f28[4];
extern int DAT_0051a0d8[4];
extern int DAT_0051a0e0[4];
extern int DAT_00519c28[4];
extern int DAT_0051a060[4];
extern int DAT_0051a070[4];
extern int DAT_0051a088[4];
extern int DAT_0051a098[4];
extern int DAT_00519f30[4];
extern int DAT_00519f38[4];
extern int DAT_00519f68[4];
extern int DAT_00519b60[4];
extern int DAT_00519b78[4];
extern int DAT_00519b00[4];
extern int DAT_00519b08[4];
extern int DAT_00519f40[4];
extern int DAT_00519b50[4];
extern char *DAT_004cf670[12];
extern char *DAT_004c22f0[4];
void FUN_00418ac0(beNDMWStatusCtrlD0 *p0, int arg1, int arg2);
}
/* matching construct: raw view for the property-record folder (list at +12; no reflected class). */
struct RecordFolder { int w0; int w4; int w8; igDataList *list; };
/* Owning stack reference to the shared name-string object: constructed from the insight's string slot,
 * retained, and released on scope exit (reference count in the low 23 bits of _refCount).  The
 * out-of-line copy the exception table names is the retail body 0x001489a0 (config/SLUS-20836/unit-objects.json,
 * duplicate __dt__9ObjectRefFv). */
class ObjectRef {
public:
    igStringObj *p;
    ObjectRef(igStringObj *o) : p(o) {}
    /* matching construct: accessor read — the string calls take the held pointer through `this`. */
    operator igStringObj *() { return p; }
    ~ObjectRef() { igStringObj *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
void FUN_00418ac0(beNDMWStatusCtrlD0 *p0, int arg1, int arg2) {
    beNDMWStatusCtrlD0 *self;
    igDataList *folder;
    int i;
    igStringObj *r;
    beNDMWItemBase *item;
    int m;
    void *tail;
    void *ctx;
    char *s;
    char *nm;
    char *nm2;
    char *s2;
    int mm;
    int o;
    int idx;
    int base;
    RecordFolder *t;
    RecordFolder *t2;
    self = p0;
    beMessenger_SelectGroup(self->_messenger, DAT_00519ba0);
    beMessenger_AppendInt(self->_messenger, self->_playerNo);
    beMessenger_DispatchSelected(self->_messenger, DAT_00519ba8);
    o = beMessenger_GetObject(self->_messenger, 0);
    if (self->_isBankFolder != 0) {
        t = (RecordFolder *)igProperty_GetRecordFolder(o, DAT_0051a0c8);
        folder = t->list;
    } else {
        t2 = (RecordFolder *)igProperty_GetRecordFolder(o, DAT_00519c00);
        folder = t2->list;
    }
    ctx = FUN_00236f80(self->_insight, DAT_0058b028[0]);
    ObjectRef sp((igStringObj *)((int *)FUN_00236f80(self->_insight, DAT_00587d08[0]))[18]);
    /* matching construct: the text buffers are declared after the holder so they lie below it in the frame as retail. */
    char buf1[2];
    char buf2[2];
    char buf3[2];
    int vec[4];
    if (sp.p != 0) {
        sp.p->_refCount = sp.p->_refCount + 1;
    }
    if (arg1 != 0) {
        i = 0;
        do {
            idx = self->_nowPage * 12 + i;
            if (idx < folder->_count) {
                item = *(beNDMWItemBase **)(folder->_data + idx * 4);
                s = beNDMWItemBase_GetRecordString(item, ctx, DAT_00519f28);
                FUN_0030b3c0(sp, s);
                if (item->_isEquip != 0) {
                    FUN_0030b460(sp, DAT_0051a0d8, 0, strlen(DAT_0051a0d8));
                } else {
                    FUN_0030b460(sp, DAT_0051a0e0, 0, strlen(DAT_0051a0e0));
                }
                beMessenger_SelectGroup(self->_messenger, DAT_00519c28);
                beMessenger_AppendString(self->_messenger, DAT_0051a060);
                beMessenger_AppendString(self->_messenger, DAT_004cf670[i]);
                mm = self->_messenger;
                nm2 = (char *)sp.p->_buffer;
                if (nm2 == 0) nm = DAT_004c22f0[0]; else nm = nm2;
                beMessenger_AppendString(mm, nm);
                beMessenger_DispatchSelected(self->_messenger, DAT_00519f30);
                beMessenger_SelectGroup(self->_messenger, DAT_00519c28);
                beMessenger_AppendString(self->_messenger, DAT_0051a060);
                beMessenger_AppendString(self->_messenger, DAT_004cf670[i]);
                if (*(unsigned char *)(((igBoolList *)self->_decideList)->_data + i) != 0) {
                    m = self->_messenger;
                    FUN_00447d00(vec, item);
                    beMessenger_AppendVec3(m, vec);
                    beMessenger_DispatchSelected(self->_messenger, DAT_00519f38);
                } else {
                    beMessenger_DispatchSelected(self->_messenger, DAT_00519f68);
                }
                beMessenger_SelectGroup(self->_messenger, DAT_00519c28);
                beMessenger_AppendString(self->_messenger, DAT_0051a070);
                beMessenger_AppendString(self->_messenger, DAT_004cf670[i]);
                beMessenger_AppendString(self->_messenger, DAT_00519b60);
                beMessenger_DispatchSelected(self->_messenger, DAT_00519f30);
                tail = DAT_00519b78;
            } else {
                tail = DAT_00519b00;
            }
            beMessenger_SelectGroup(self->_messenger, DAT_00519c28);
            beMessenger_AppendString(self->_messenger, DAT_0051a060);
            beMessenger_AppendString(self->_messenger, DAT_004cf670[i]);
            beMessenger_AppendString(self->_messenger, tail);
            beMessenger_DispatchSelected(self->_messenger, DAT_00519b08);
            beMessenger_SelectGroup(self->_messenger, DAT_00519c28);
            beMessenger_AppendString(self->_messenger, DAT_0051a070);
            beMessenger_AppendString(self->_messenger, DAT_004cf670[i]);
            beMessenger_AppendString(self->_messenger, tail);
            beMessenger_DispatchSelected(self->_messenger, DAT_00519b08);
            i++;
        } while (i < 12);
        buf1[0] = self->_nowPage + 49;
        buf1[1] = 0;
        beMessenger_SelectGroup(self->_messenger, DAT_00519c28);
        if (self->_isBankFolder != 0) {
            beMessenger_AppendString(self->_messenger, DAT_0051a088);
        } else {
            beMessenger_AppendString(self->_messenger, DAT_0051a098);
        }
        beMessenger_AppendString(self->_messenger, DAT_004cf670[0]);
        beMessenger_AppendString(self->_messenger, buf1);
        beMessenger_DispatchSelected(self->_messenger, DAT_00519f30);
        buf1[0] = self->_maxPage + 48;
        buf1[1] = 0;
        beMessenger_SelectGroup(self->_messenger, DAT_00519c28);
        if (self->_isBankFolder != 0) {
            beMessenger_AppendString(self->_messenger, DAT_0051a088);
        } else {
            beMessenger_AppendString(self->_messenger, DAT_0051a098);
        }
        beMessenger_AppendString(self->_messenger, DAT_004cf670[1]);
        beMessenger_AppendString(self->_messenger, buf1);
        beMessenger_DispatchSelected(self->_messenger, DAT_00519f30);
    }
    if (arg2 != 0) {
        base = self->_nowPage * 12;
        idx = base + self->_retCode;
        if (idx < folder->_count) {
            item = *(beNDMWItemBase **)(folder->_data + idx * 4);
            s = beNDMWItemBase_GetRecordString(item, ctx, DAT_00519f40);
            if (item->_kindNo == 0) {
                if (item->_recNo != 0x114) {
                    buf2[1] = 0;
                    buf2[0] = ((beNDMWItemBlueArmor *)item)->_pocket + 48;
                    FUN_0030b3c0(sp, s);
                    r = sp.p;
                    i = r->_length;
                    FUN_0030b460(r, buf2, i, strlen(buf2));
                    s2 = (char *)sp.p->_buffer;
                    s = s2 == 0 ? DAT_004c22f0[0] : s2;
                }
            } else if (item->_kindNo == 1 && item->_recNo != 0x1f) {
                buf3[1] = 0;
                buf3[0] = ((beNDMWItemBlueArmor *)item)->_pocket + 48;
                FUN_0030b3c0(sp, s);
                r = sp.p;
                idx = r->_length;
                FUN_0030b460(r, buf3, idx, strlen(buf3));
                s2 = (char *)sp.p->_buffer;
                s = s2 == 0 ? DAT_004c22f0[0] : s2;
            }
            beMessenger_SelectGroup(self->_messenger, DAT_00519c28);
            beMessenger_AppendString(self->_messenger, DAT_00519b50);
            beMessenger_AppendString(self->_messenger, DAT_004cf670[0]);
            if (s != 0) {
                beMessenger_AppendString(self->_messenger, s);
            } else {
                beMessenger_AppendString(self->_messenger, DAT_00519b60);
            }
            beMessenger_DispatchSelected(self->_messenger, DAT_00519f30);
            tail = DAT_00519b78;
        } else {
            tail = DAT_00519b00;
        }
        beMessenger_SelectGroup(self->_messenger, DAT_00519c28);
        beMessenger_AppendString(self->_messenger, DAT_00519b50);
        beMessenger_AppendString(self->_messenger, DAT_004cf670[0]);
        beMessenger_AppendString(self->_messenger, tail);
        beMessenger_DispatchSelected(self->_messenger, DAT_00519b08);
    }
}
