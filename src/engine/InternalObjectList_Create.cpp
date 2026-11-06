/* The factory for the internal object list (the 16-byte raw/retaining list behind
 * __internalObjectList). With the object system active it registers the class and
 * creates the instance through its metaobject; otherwise it allocates 16 bytes and runs the
 * concrete constructor plus the post-construction virtual hooks, the same two branches as the
 * other descriptor factories. */
extern "C" {
int __internalObjectList_EnsureRegistered(...);
void **InternalObjectList_Construct(...);
void **igObject_AllocateRawStorage(...);
void **igMetaObject_CreateInstance(...);
extern int g___internalObjectList_metaObject[4];
/* object-system runtime pointer; its byte 0 is the "object system active" flag */
extern unsigned char * g_objectSystem[4];
void **InternalObjectList_Create(int allocator);
}
class DW4VC_36_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual int vX(int); };
class DW4VC_44_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual int vX(); };
void **InternalObjectList_Create(int allocator) {
    void **list;

    if (*g_objectSystem[0] != 0) {
        __internalObjectList_EnsureRegistered(); /* class registration guard: RunStaticInit(__internalObjectList_Register) */
        list = (void **)(igMetaObject_CreateInstance(g___internalObjectList_metaObject[0], allocator));
    } else {
        list = (void **)(igObject_AllocateRawStorage(0x10, 0, allocator));
        if (list != 0) {
            list = (void **)(InternalObjectList_Construct(list, 1));
        }
        ((DW4VC_44_0 *)(list))->vX();
        ((DW4VC_36_1 *)(list))->vX((int)(0));
    }
    return list;
}
