#include "dw4/reflected.h"
extern "C" {
int FUN_002eb010(int);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
void *StringPool_Intern(int, int);
int igObject_Destroy(void *);
int ObjectList_AppendRetained(void *, void *);
void *FUN_003637c0(int);
void *FUN_00363c20(int);
int Memory_GetAllocatorBySelector(int);
int igObject_GetAllocator(void *);
extern int DAT_00586f20[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
/* Owning reference to the new message; the destructor drops one reference and destroys at zero. */
struct RP { beDemoKeepMes *p; ~RP() { beDemoKeepMes *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } } };
#define POOL(v) if (DAT_00586f20[0] == 0) { v = FUN_002eb010(16); if (v != 0) v = StringPool_Construct(v); DAT_00586f20[0] = v; }
#define SETSTR(fld, arg) { int *nw; beDemoKeepMes *c = e.p; POOL(v) nw = (int *)StringPool_Intern(DAT_00586f20[0], arg); old = (int *)c->fld; if (old != 0) { hd = old - 2; r = old[-1] - 1; old[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*hd, hd); } c->fld = (int)nw; }
extern "C" void FUN_0037e3a0(beDemoManager *self, int a1, int a2, int a3, int t0, int t1, int t2, long long t3);
void FUN_0037e3a0(beDemoManager *self, int a1, int a2, int a3, int t0, int t1, int t2, long long t3) {
    int v;
    beDemoManagerWork *q;
    beDemoManagerWork *q2;
    int *old;
    int *hd;
    int r;
    if (self->_buildData == 0) {
        v = igObject_GetAllocator(self);
        v = (GPR_00554c14 != 0) ? v : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        q = (beDemoManagerWork *)self->_buildData;
        if (q != 0) {
            q->_refCount = q->_refCount - 1;
            if ((q->_refCount & 0x7fffff) == 0) igObject_Destroy(q);
        }
        self->_buildData = (int)FUN_003637c0(v);
        self->_turningOK = 0;
    }
    q2 = (beDemoManagerWork *)self->_buildData;
    v = igObject_GetAllocator(self);
    v = (GPR_00554c14 != 0) ? v : Memory_GetAllocatorBySelector(DAT_00587110[0]);
    /* matching construct: the holder is declared after the allocation call returns, so retail's protected range starts after the allocator and not at it */
    beDemoKeepMes *k = (beDemoKeepMes *)FUN_00363c20(v);
    RP e;
    e.p = k;
    e.p->_kind = a1;
    e.p->_sendTime = t3;
    SETSTR(_groupName, a2)
    SETSTR(_infoName, a3)
    e.p->_ramNo = t0;
    SETSTR(_message, t1)
    SETSTR(_mesParam, t2)
    ObjectList_AppendRetained((void *)q2->_keepMesList, e.p);
}
