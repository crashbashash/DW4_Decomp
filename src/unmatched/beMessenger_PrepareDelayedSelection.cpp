/* beMessenger::PrepareDelayedSelection (0x0038e6b0, 576 bytes). Make the messenger's last delay
 * record ready for a delayed send: reset the current argument context, replace the record by a
 * fresh one when it is already in use, then intern the group and name strings and store the
 * number. Callers: beMessenger_SendDelayedNamed/SendDelayedGroup/ PrepareDelayedGroup. Matching
 * notes - The record handle is an owning stack reference (ObjectRef below) whose accesses are
 * reloaded around calls; its destructor releases the record on scope exit and is the destroy
 * action of the retail exception table. - Needs the content-pinned alternate compiler with -O3,p;
 * the padding NOPs and register choices come out of the compiler, no inline assembly is used. -
 * Fields are reached through the reflected beMessenger, beMessengerDelay, beMessengerDelayList and
 * igObject structs; the 4-byte handles are cast at the use sites. */
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

/* Owning stack reference to the delay record: constructed from the record and released on scope
 * exit (reference count in the low 23 bits of _refCount).  The out-of-line copy the exception
 * table names is the retail body 0x0038c390 (config/SLUS-20836/unit-objects.json, duplicate
 * __dt__9ObjectRefFv). */
class ObjectRef {
public:
    igObject *p;
    ObjectRef(igObject *o) : p(o) {}
    ~ObjectRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};

/* Intern `text` (creating the string pool on first use), release the string
 * previously stored in the field and publish the interned token. */
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
    ObjectRef row(((igObject **)stack->_data)[last]);
    RETAIN_REF(row.p)
    if (((beMessengerDelay *)row.p)->_isUse) {
        allocator = igObject_GetAllocator(self);
        allocator = GPR_00554c14 ? allocator : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        /* Swap the held record for a fresh one: drop the old reference, keep the new. */
        RELEASE_REF(row.p)
        row.p = (igObject *)beMessengerDelay_Create(allocator);
        ObjectList_AppendRetained((void *)self->_delayStack, row.p);
    }
    SET_STRING(_groupName, group)
    SET_STRING(_infoName, name)
    ((beMessengerDelay *)row.p)->_ramNo = number;
}
