/* 0x002ed330 - Memory_ReallocateBuffer (a buffer reallocate; no retail name known).
 * Resize `buffer` to `size` bytes.  A null buffer is simply allocated from the
 * default allocator; otherwise Memory_FindOwningAllocator names the pool that
 * owns the block and its virtual method at vtable offset 232 does the resize.
 * A block no pool owns yields 0.  Used by igArray_Append to grow its data
 * buffer (src/engine/init-callback-array.c, docs/engine/metadata-callback-services.md).
 * Matching construct: the owner lookup is declared variadic and called
 * without arguments so it sees the untouched argument register. */
extern "C" {
int Memory_AllocateDefaultBuffer(...);
void **Memory_FindOwningAllocator(...);
int Memory_ReallocateBuffer(int buffer, int size);
}
/* Stand-in for the pool's vtable; vX is the method at vtable offset 232. */
class DW4VC_232_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual int vX(int, int); };
int Memory_ReallocateBuffer(int buffer, int size) {
    void **owner;

    if (buffer == 0) {
        return Memory_AllocateDefaultBuffer(size);
    }
    owner = (void **)(Memory_FindOwningAllocator());
    if (owner != 0) {
        return ((DW4VC_232_2 *)(owner))->vX((int)(buffer), (int)(size));
    }
    return 0;
}
