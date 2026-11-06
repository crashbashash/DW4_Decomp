#include "dw4/reflected.h"
extern "C" {
void *igProperty_FindByName(void *, int);
void *igObject_GetAllocator(void *);
void *Memory_GetAllocatorBySelector(int);
void *beMessengerGroup_Create(void *);
void igNamedObject_SetName(void *, const char *);
void ObjectList_AppendRetained(void *, void *);
void List_Resize(void *, int, int);
void igObject_Destroy(void *);
void *FUN_002eb010(int);
void *StringPool_Construct(void *);
const char *StringPool_Intern(void *, const char *);
void StringChunk_ReleaseHeader(int, int *);
extern void *DAT_00586f20[4];
extern int DAT_00587110[4];
extern int DAT_00585be0[4];
extern unsigned char GPR_00554c14;
}
/* matching construct: the list/group fields are 4-byte arena handles in the reflected structs; the (void *) / (T *) casts give the typed views (no layout effect) */
#define RETAIN_REF(q) { igObject *rr = (q); if (rr) ++rr->_refCount; }
#define RELEASE_REF(q) { igObject *rr = (q); \
    if (rr) { --rr->_refCount; if (!(rr->_refCount & 0x7fffff)) igObject_Destroy(rr); } }
/* Owning stack reference to the receiver group: holds the found (retained) or freshly created
 * group for the duration of the registration and releases it on scope exit (reference count in the
 * low 23 bits of _refCount). */
class GroupRef {
public:
    beMessengerGroup *p;
    GroupRef(beMessengerGroup *g) : p(g) {}
    ~GroupRef() { beMessengerGroup *g = p; if (g != 0) { --g->_refCount; if ((g->_refCount & 0x7fffff) == 0) igObject_Destroy(g); } }
};
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    const char *p;
    StringRef(const char *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
extern "C" void StringList_AppendRetained(void *, const StringRef &);
struct Str { static inline const char *intern(const char *text) {
    const char *token;
    if (text == 0) {
        token = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            void *pool = FUN_002eb010(0x10);
            if (pool != 0) pool = StringPool_Construct(pool);
            DAT_00586f20[0] = pool;
        }
        token = StringPool_Intern(DAT_00586f20[0], text);
    }
    return token;
} };
extern "C" void beMessenger_RegisterReceiver(beMessenger *self, void *recv, const char *name, const char *text, int value)
{
    void *allocator;
    igIntList *l;
    int n;

    GroupRef grp((beMessengerGroup *)igProperty_FindByName((void *)self->_groupList, DAT_00585be0[0]));
    RETAIN_REF((igObject *)grp.p)
    if (grp.p == 0) {
        allocator = igObject_GetAllocator(self);
        allocator = GPR_00554c14 ? allocator : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        RELEASE_REF((igObject *)grp.p)
        grp.p = (beMessengerGroup *)beMessengerGroup_Create(allocator);
        igNamedObject_SetName(grp.p, name);
        ObjectList_AppendRetained((void *)self->_groupList, grp.p);
    }
    ObjectList_AppendRetained((void *)grp.p->_ramList, recv);
    {
        const char *token = Str::intern(text);
        StringList_AppendRetained((void *)grp.p->_infoNameList, StringRef(token));
    }
    l = (igIntList *)grp.p->_ramNoList;
    n = l->_count;
    if (n < l->_capacity) l->_count = *(volatile int *)&l->_count + 1;
    else List_Resize(l, n + 1, 4);
    ((int *)l->_data)[n] = value;
}
