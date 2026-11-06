/* Object storage dispatch: every helper re-selects the allocator from the object header
 * (igObject_GetAllocator) and calls one slot of that allocator's vtable, forwarding its arguments
 * unchanged. Allocator is an observed ABI view of the vtable byte offsets the helpers call
 * through, not an original type; it is never instantiated. Only slots 216 (AllocateStorage) and
 * 264 (FreeStorage) are named by the original symbols; the other slots keep their byte offset. */
/* RESERVED(n) declares unused virtual slot n so the named slots land on the
 * right byte offsets. */
#define RESERVED(n) virtual void reserved_##n()
class Allocator {
public:
    /* The first two vtable words are the class header, so slot n sits at byte
     * offset 8 + 4 * n (slot 52 = +216). */
    RESERVED(0); RESERVED(1); RESERVED(2); RESERVED(3); RESERVED(4);
    RESERVED(5); RESERVED(6); RESERVED(7); RESERVED(8); RESERVED(9);
    RESERVED(10); RESERVED(11); RESERVED(12); RESERVED(13); RESERVED(14);
    RESERVED(15); RESERVED(16); RESERVED(17); RESERVED(18); RESERVED(19);
    RESERVED(20); RESERVED(21); RESERVED(22); RESERVED(23); RESERVED(24);
    RESERVED(25); RESERVED(26); RESERVED(27); RESERVED(28); RESERVED(29);
    RESERVED(30); RESERVED(31); RESERVED(32); RESERVED(33); RESERVED(34);
    RESERVED(35); RESERVED(36); RESERVED(37); RESERVED(38); RESERVED(39);
    RESERVED(40); RESERVED(41); RESERVED(42); RESERVED(43); RESERVED(44);
    RESERVED(45); RESERVED(46); RESERVED(47); RESERVED(48); RESERVED(49);
    RESERVED(50); RESERVED(51);
    virtual int allocate_storage(int size);                                   /* +216 */
    virtual int slot_220(int size, int alignment);                            /* +220: callers pass 0x10/0x80 */
    virtual int slot_224(int size, int option);                               /* +224: metadata default storage passes 1 */
    RESERVED(55);                                                             /* +228 */
    virtual int slot_232(int storage, int size);                              /* +232: callers pass (old storage, size) */
    virtual int slot_236(int storage, int size, int alignment);               /* +236: callers pass 0x80 */
    RESERVED(58); RESERVED(59); RESERVED(60); RESERVED(61); RESERVED(62);     /* +240..+260 */
    RESERVED(63);
    virtual void free_storage(int storage);                                   /* +264 */
};

extern "C" {
Allocator *igObject_GetAllocator(int object);
int igObject_AllocateStorage(int object, int size);
int FUN_00300db0(int object, int size, int alignment);
int FUN_00300e00(int object, int size, int option);
int FUN_00300e50(int object, int storage, int size);
int FUN_00300ea0(int object, int storage, int size, int alignment);
void igObject_FreeStorage(int object, int storage);
void FUN_00300f50(int object, int storage);
}

int igObject_AllocateStorage(int object, int size) {
    Allocator *allocator = igObject_GetAllocator(object);
    return allocator->allocate_storage(size);
}

int FUN_00300db0(int object, int size, int alignment) {
    Allocator *allocator = igObject_GetAllocator(object);
    return allocator->slot_220(size, alignment);
}

int FUN_00300e00(int object, int size, int option) {
    Allocator *allocator = igObject_GetAllocator(object);
    return allocator->slot_224(size, option);
}

int FUN_00300e50(int object, int storage, int size) {
    Allocator *allocator = igObject_GetAllocator(object);
    return allocator->slot_232(storage, size);
}

int FUN_00300ea0(int object, int storage, int size, int alignment) {
    Allocator *allocator = igObject_GetAllocator(object);
    return allocator->slot_236(storage, size, alignment);
}

/* A null storage pointer returns without touching the allocator */
void igObject_FreeStorage(int object, int storage) {
    if (storage != 0) {
        Allocator *allocator = igObject_GetAllocator(object);
        allocator->free_storage(storage);
    }
}

/* Same instruction body as igObject_FreeStorage. */
void FUN_00300f50(int object, int storage) {
    if (storage != 0) {
        Allocator *allocator = igObject_GetAllocator(object);
        allocator->free_storage(storage);
    }
}
