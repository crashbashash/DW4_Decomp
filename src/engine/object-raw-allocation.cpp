/* Storage for a new object. Reserves size + prefix_size bytes from the given allocator, falls back
 * to the default allocator (looked up by selector) when none is passed, and to the global heap
 * (FUN_00126308) when there is no allocator at all. It returns the address prefix_size bytes into
 * the block, so a header can precede the object. The object factories in src/unmatched call it
 * with prefix_size 0. The allocator method called is vtable offset 216 (vfunc_54), the allocate-
 * bytes slot. */
extern "C" {
/* libc-style allocation fallback taking the total size (docs/engine/field-factories.md,
 * "Raw allocation"); finding #3189 suggests the name Memory_AllocateFromGlobalHeap. */
char *FUN_00126308(int);
/* Default allocator provider: selector in, allocator object (or null) out. */
void **Memory_GetAllocatorBySelector(...);
/* Selector word the provider is queried with when no allocator is passed
 * (docs/engine/allocator-builder.md, global 0x587018). */
extern int g_allocatorSelector[4];
char *igObject_AllocateRawStorage(int size, int prefix_size, void **requested_allocator);
}
/* matching construct: dummy-virtual allocator class; only vtable offset 216 (vfunc_54) is called */
class DW4VC_216_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual char *vX(int); };
char *igObject_AllocateRawStorage(int size, int prefix_size, void **requested_allocator) {
    int total_size;
    void **allocator;

    allocator = requested_allocator;
    total_size = size + prefix_size;
    if (allocator == 0) {
        allocator = (void **)Memory_GetAllocatorBySelector(g_allocatorSelector[0]);
    }
    if (allocator == 0) {
        /* no allocator at all: the prefix is not added on this path (retail behaviour) */
        return FUN_00126308(total_size);
    }
    return ((DW4VC_216_2 *)allocator)->vX(total_size) + prefix_size;
}
