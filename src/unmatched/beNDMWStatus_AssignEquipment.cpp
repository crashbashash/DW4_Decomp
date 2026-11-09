#include "dw4/reflected.h"
extern "C" {
int FUN_002eb010(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
char *StringPool_Intern(...);
void *Memory_GetAllocatorBySelector(...);
void *igObject_GetAllocator(...);
int igObject_Destroy(...);
int FUN_00236f80(...);
int FUN_002b90e0(...);
int FUN_002caa70(...);
int beNDMWItemBase_GetRecordInt(...);
extern int DAT_00586f20[4];
extern int DAT_00587110[4];
extern int DAT_0058b028[4];
extern unsigned char GPR_00554c14;
extern char DAT_00519de0[], DAT_00519de8[], DAT_00519df8[], DAT_00519e00[];
extern char DAT_00519e10[], DAT_00519e20[], DAT_00519e28[], DAT_00519e38[];
extern char DAT_00519e48[], DAT_00519e58[], DAT_00519e60[], DAT_00519e68[];
}

/* An inventory item: kind at +8, equipped flag at +16. */
struct EquipItem {
    int _vtable;
    unsigned int _refCount;
    int _kind;
    int _pad;
    unsigned char _equipped;
};
/* igObjectList of EquipItem pointers. */
struct ItemList {
    int _vtable;
    unsigned int _refCount;
    int _count;
    int _capacity;
    EquipItem **_data;
};
struct StatusPanel {
    int _vtable;
    unsigned int _refCount;
    int _insight;
    char _pad[0x6c];
    ItemList *_equipList;   /* +0x78 */
};
struct StrList;
/* Owning stack reference to a pooled string token (count at p[-1], chunk header at p[-2]).
 * Interning for a text list yields one: the list takes its own share and the token is a temporary
 * released at the end of the statement; copying a list entry out yields one in the caller's frame. */
class StringRef {
public:
    char *p;
    StringRef() {}
    StringRef(char *s) : p(s) {}
    StringRef(const StringRef &o) : p(o.p) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
extern "C" int StringList_AppendRetained(void *, const StringRef &);
/* The copy comes back through the hidden result pointer, so it is owned from the call on. */
extern "C" StringRef StringList_CopyRetained(void *list, int index);
/* Owning stack references to the equipment-category name list and the scratch int list of the
 * unequip pass; each releases its object on scope exit (reference count in the low 23 bits of
 * _refCount). */
template <class T> class igSmartPointer {
public:
    T *p;
    igSmartPointer(T *o) : p(o) {}
    ~igSmartPointer() { T *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class IntListRef {
public:
    igObject *p;
    IntListRef(igObject *o) : p(o) {}
    /* matching construct: __option(exceptions) -- the inline instance in this exception-handling unit re-reads p
     * after the decrement store (retail `lw a0,216(sp)`), but retail's out-of-line copy 0x00150eb0 comes from an
     * exceptions-off unit and reads p once.  One spelling cannot give both, so the body follows the compile mode
     * (the verifier compiles the deferred duplicate under that unit's profile). */
    ~IntListRef() {
#if __option(exceptions)
        if (p != 0) { p->_refCount = p->_refCount - 1; if ((p->_refCount & 0x7fffff) == 0) igObject_Destroy(p); }
#else
        igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); }
#endif
    }
};
struct StrList {
    int _vtable;
    unsigned int _refCount;
    int _count;
};

struct U { static inline char *InternStr(char *text) {
    if (text == 0) return 0;
    if (DAT_00586f20[0] == 0) {
        int pool = FUN_002eb010(0x10);
        if (pool != 0) pool = StringPool_Construct(pool);
        DAT_00586f20[0] = pool;
    }
    return StringPool_Intern(DAT_00586f20[0], text);
} };
#define INTERN_APPEND(lst, text) { char *tok = U::InternStr((char *)(text)); StringList_AppendRetained(lst, StringRef(tok)); }
#define REL(o) { igObject *rr = (igObject *)(o); if (rr != 0) { rr->_refCount = rr->_refCount - 1; if (((unsigned long long)((long long)(int)rr->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(rr); } } }
#define LIST_CLEAR_AT(L, i) { REL((L)->_data[i]); \
    if ((L)->_count != 0 && (i) >= 0 && (i) < (L)->_count) (L)->_data[i] = 0; }

extern "C" void beNDMWStatus_AssignEquipment(StatusPanel *self, ItemList *slotList, int slot, int equipIdx);
void beNDMWStatus_AssignEquipment(StatusPanel *self, ItemList *slotList, int slot, int equipIdx) {
    EquipItem *oldItem = 0;
    EquipItem *newItem = 0;
    ItemList *held;
    void *alloc;
    int i;
    int rec;
    int hit;
    int cat;

    held = slotList;
    if (slot < slotList->_count) oldItem = slotList->_data[slot];
    if (equipIdx >= 0) {
        held = self->_equipList;
        if (equipIdx < held->_count) newItem = held->_data[equipIdx];
    }
    if (oldItem == newItem) {
        LIST_CLEAR_AT(slotList, slot)
        if (oldItem != 0) oldItem->_equipped = 0;
    } else {
        if (oldItem != 0) {
            oldItem->_equipped = 0;
            LIST_CLEAR_AT(slotList, slot)
        }
        if (newItem != 0) {
            i = 0;
            if (0 < slotList->_count) {
                int off = 0;
                do {
                    EquipItem *it = *(EquipItem **)((char *)slotList->_data + off);
                    if (it != 0 && it == newItem) {
                        it->_equipped = 0;
                        REL(*(EquipItem **)((char *)slotList->_data + off))
                        if (slotList->_count != 0 && i >= 0 && i < slotList->_count)
                            *(EquipItem **)((char *)slotList->_data + off) = 0;
                    }
                    i += 1;
                    off += 4;
                } while (i < slotList->_count);
            }
            if ((newItem->_kind == 3) == 1) {
                alloc = igObject_GetAllocator(self);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                {
                igSmartPointer<igObject> names((igObject *)FUN_002b90e0(alloc));
                INTERN_APPEND(names.p, DAT_00519de0)
                INTERN_APPEND(names.p, DAT_00519de8)
                INTERN_APPEND(names.p, DAT_00519df8)
                INTERN_APPEND(names.p, DAT_00519e00)
                INTERN_APPEND(names.p, DAT_00519e10)
                INTERN_APPEND(names.p, DAT_00519e20)
                INTERN_APPEND(names.p, DAT_00519e28)
                INTERN_APPEND(names.p, DAT_00519e38)
                INTERN_APPEND(names.p, DAT_00519e48)
                INTERN_APPEND(names.p, DAT_00519e58)
                INTERN_APPEND(names.p, DAT_00519e60)
                INTERN_APPEND(names.p, DAT_00519e68)
                rec = FUN_00236f80(self->_insight, DAT_0058b028[0]);
                alloc = igObject_GetAllocator(self);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                IntListRef tmp((igObject *)FUN_002caa70(alloc));
                cat = -1;
                i = 0;
                if (0 < ((StrList *)names.p)->_count) {
                    do {
                        hit = beNDMWItemBase_GetRecordInt(newItem, rec, (int)StringList_CopyRetained(names.p, i).p) > 0;
                        if (hit != 0) { cat = i; break; }
                        i += 1;
                    } while (i < ((StrList *)names.p)->_count);
                }
                int k = 0;
                if (0 < slotList->_count) {
                    EquipItem *it;
                    int off = 0;
                    do {
                        it = *(EquipItem **)((char *)slotList->_data + off);
                        if (it != 0) {
                            hit = beNDMWItemBase_GetRecordInt(it, rec, (int)StringList_CopyRetained(names.p, cat).p) > 0;
                            if (hit != 0) {
                                it->_equipped = 0;
                                REL(*(EquipItem **)((char *)slotList->_data + off))
                                if (slotList->_count != 0 && k >= 0 && k < slotList->_count)
                                    *(EquipItem **)((char *)slotList->_data + off) = 0;
                            }
                        }
                        k += 1;
                        off += 4;
                    } while (k < slotList->_count);
                }
                }
            }
            newItem->_equipped = 1;
        }
        if (newItem != 0) newItem->_refCount = newItem->_refCount + 1;
        REL(slotList->_data[slot])
        if (slotList->_count != 0 && slot >= 0 && slot < slotList->_count)
            slotList->_data[slot] = newItem;
    }
}
