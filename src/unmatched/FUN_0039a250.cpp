/* Appends an effect sub-command: builds a beModelCtrlSCEffect (pooled allocator unless the global
 * selector flag is clear), interns the model and sequence names into it (releasing whatever the
 * fresh record held), copies the offset and rotation vectors, the two flags and the start frame,
 * then appends the record to the sub-command list, which retains it. The creating reference is
 * released on scope exit. */
#include "dw4/reflected.h"
struct V { float x, y, z; };
extern "C" {
beModelCtrlSCEffect *FUN_0034f8e0(int);
int FUN_002eb010(int);
int Memory_GetAllocatorBySelector(int);
int ObjectList_AppendRetained(int, beModelCtrlSCEffect *);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
void *StringPool_Intern(int, int);
int igObject_Destroy(beModelCtrlSCEffect *);
int igObject_GetAllocator();
extern int DAT_00586f20[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
void FUN_0039a250(beModelCtrlSubCom *self, int str1, int str2, struct V *va, struct V *vb, char c1, char c2, float f);
}
/* Owning stack reference to the new effect record, released on scope exit (reference count in the
 * low 23 bits of _refCount). */
class ObjectRef {
public:
    beModelCtrlSCEffect *p;
    ObjectRef(beModelCtrlSCEffect *o) : p(o) {}
    ~ObjectRef() { beModelCtrlSCEffect *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
void FUN_0039a250(beModelCtrlSubCom *self, int str1, int str2, struct V *va, struct V *vb, char c1, char c2, float f) {
    int a;
    int v;
    int *s;
    int *old;
    int *hd;
    int r;
    beModelCtrlSCEffect *e;
    a = igObject_GetAllocator();
    ObjectRef effect(FUN_0034f8e0(GPR_00554c14 != 0 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0])));
    e = effect.p;
    if (DAT_00586f20[0] == 0) {
        v = FUN_002eb010(0x10);
        if (v != 0) {
            v = StringPool_Construct(v);
        }
        DAT_00586f20[0] = v;
    }
    s = (int *)StringPool_Intern(DAT_00586f20[0], str1);
    old = (int *)e->_modelName;
    if (old != 0) {
        hd = old - 2;
        r = old[-1] - 1;
        old[-1] = r;
        if (r == 0) {
            StringChunk_ReleaseHeader(*hd, hd);
        }
    }
    e->_modelName = (int)s;
    effect.p->_geneRamNo = -1;
    e = effect.p;
    if (DAT_00586f20[0] == 0) {
        v = FUN_002eb010(0x10);
        if (v != 0) {
            v = StringPool_Construct(v);
        }
        DAT_00586f20[0] = v;
    }
    s = (int *)StringPool_Intern(DAT_00586f20[0], str2);
    old = (int *)e->_seqName;
    if (old != 0) {
        hd = old - 2;
        r = old[-1] - 1;
        old[-1] = r;
        if (r == 0) {
            StringChunk_ReleaseHeader(*hd, hd);
        }
    }
    e->_seqName = (int)s;
    effect.p->_startFrame = f;
    e = effect.p;
    ((float *)e->_offset)[0] = va->x;
    ((float *)e->_offset)[1] = va->y;
    ((float *)e->_offset)[2] = va->z;
    e = effect.p;
    ((float *)e->_rotation)[0] = vb->x;
    ((float *)e->_rotation)[1] = vb->y;
    ((float *)e->_rotation)[2] = vb->z;
    effect.p->_isSeqDead = c1;
    effect.p->_isPositionLock = c2;
    ObjectList_AppendRetained(self->_comList, effect.p);
}
