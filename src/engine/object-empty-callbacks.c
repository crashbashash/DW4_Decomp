/* igObject_CreateEmptyInitCallbacks igObject's class-registration "extra callbacks" factory
 * (passed to igMetaObject_RegisterClass by igObject_Register): allocate a 12-byte callback array
 * from the metadata allocator selector and construct it empty. Returns the array, or 0 when the
 * allocation fails. */
int igArray_Construct();
int Memory_AllocateBufferDirect();
int Memory_GetAllocatorBySelector();
/* Allocator selector used for metadata objects (queried here and before every
 * igMetaObject_Create).md calls it "allocator key 587040". */
extern int g_metadataAllocatorKey[4];
int igObject_CreateEmptyInitCallbacks(void) {
    int callbacks;

    callbacks = Memory_AllocateBufferDirect(0xC, Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    if (callbacks != 0) {
        callbacks = igArray_Construct(callbacks);
    }
    return callbacks;
}
