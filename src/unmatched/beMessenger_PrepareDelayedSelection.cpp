/* The record handle is an owning stack reference (igSmartPointer<igObject>) whose accesses are reloaded around
 * calls; its destructor releases the record on scope exit. The padding nops and register choices
 * come out of the compiler; no inline assembly is used. The 4-byte handles are cast at the use
 * sites. */
#include "dw4/reflected.h"

extern "C" {
void beMessenger_InitializeMemory();
void beMessengerArgData_Clear(int);
void *igObject_GetAllocator(void *);
void *Memory_GetAllocatorBySelector(int);
void *beMessengerDelay_Create(void *);
void ObjectList_AppendRetained(void *, void *);
void igObject_Destroy(void *);
void *FUN_002eb010(int);
void *StringPool_Construct(void *);
const char *StringPool_Intern(void *, const char *);
void StringChunk_ReleaseHeader(int, int *);
extern void *DAT_00586f20[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}

#define RETAIN_REF(q) { igObject *rr = (q); if (rr) ++rr->_refCount; }
#define RELEASE_REF(q) { igObject *rr = (q); \
    if (rr) { --rr->_refCount; if (!(rr->_refCount & 0x7fffff)) igObject_Destroy(rr); } }

/* Owning stack reference to the delay record; released on scope exit (reference count in the low
 * 23 bits of _refCount). */
template <class T> class igSmartPointer {
public:
    T *p;
    igSmartPointer(T *o) : p(o) {}
    ~igSmartPointer() { T *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};

#define SET_STRING(field, text) { \
    beMessengerDelay *r = (beMessengerDelay *)row.p; \
    if (DAT_00586f20[0] == 0) { \
        void *pool = FUN_002eb010(0x10); \
        if (pool != 0) pool = StringPool_Construct(pool); \
        DAT_00586f20[0] = pool; \
    } \
    token = StringPool_Intern(DAT_00586f20[0], (text)); \
    int *old = (int *)r->field; \
    if (old) { \
        int *header = old - 2; \
        if (--old[-1] == 0) StringChunk_ReleaseHeader(*header, header); \
    } \
    r->field = (int)token; }

extern "C" void beMessenger_PrepareDelayedSelection(beMessenger *self, const char *group, const char *name, int number)
{
    void *allocator;
    const char *token;
    beMessengerDelayList *stack;
    int last;

    if (self->_isMemoryAssign == 0)
        beMessenger_InitializeMemory();
    else
        beMessengerArgData_Clear(self->_argData);
    stack = (beMessengerDelayList *)self->_delayStack;
    last = stack->_count - 1;
    igSmartPointer<igObject> row(((igObject **)stack->_data)[last]);
    RETAIN_REF(row.p)
    if (((beMessengerDelay *)row.p)->_isUse) {
        allocator = igObject_GetAllocator(self);
        allocator = GPR_00554c14 ? allocator : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        RELEASE_REF(row.p)
        row.p = (igObject *)beMessengerDelay_Create(allocator);
        ObjectList_AppendRetained((void *)self->_delayStack, row.p);
    }
    SET_STRING(_groupName, group)
    SET_STRING(_infoName, name)
    ((beMessengerDelay *)row.p)->_ramNo = number;
}
