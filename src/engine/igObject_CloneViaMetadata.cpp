/* Generic clone of any object. Asks the source for its metaobject through vtable slot 20 (the
 * GetMetaObject slot: vfunc_20 of beCameraMode returns the class handle), creates an instance of
 * that class on the source's own allocator and copies the contents across. `copyMode` is passed to
 * the contents copy unchanged; its meaning is not inferred (the copy dispatches on 0, 1 and 2). */
extern "C" {
int FUN_00300c00(...);
int igObject_GetAllocator(...);
int igMetaObject_CreateInstance(...);
int igObject_CloneViaMetadata(void **source, int copyMode);
}
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
int igObject_CloneViaMetadata(void **source, int copyMode) {
    int metaObject;
    int copy;

    metaObject = ((DW4VC_88_0 *)(source))->vX();
    copy = igMetaObject_CreateInstance(metaObject, igObject_GetAllocator(source));
    FUN_00300c00(copy, source, copyMode);
    return copy;
}
