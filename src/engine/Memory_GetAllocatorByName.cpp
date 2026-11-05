/* 0x002f8920
 * Ask the current memory context (Memory_GetCurrentContextAlias, a jump to
 * 0x002f8680) for an allocator by name: virtual call through vtable slot 24
 * (+0x60) of the context, passing the context and the name.  Callers use the
 * result as the allocator of a new object.
 * The context's first 24 virtuals are placeholders; the declared return type
 * is void, as matched (the result stays in v0). */
extern "C" {
void **Memory_GetCurrentContextAlias(...);
void Memory_GetAllocatorByName(int name);
}
class MemoryContext { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(int); };
void Memory_GetAllocatorByName(int name) {
    void **context;

    context = (void **)(Memory_GetCurrentContextAlias());
    ((MemoryContext *)(context))->vX((int)(name));
}
