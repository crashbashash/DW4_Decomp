/* 0x002f8830 — igMemoryPoolContextInfo_DeleteAllocation.
 * Releases an allocation owned by a pool context.  While the object system is
 * active (flag byte at the start of the record behind g_objectSystem,
 * see docs/engine/field-factories.md) the call goes to Memory_FreeBuffer
 * through its j-thunk at 0x002ff810; otherwise it takes the early-boot path
 * FUN_00126360.  Neither callee's argument is touched here: `allocation` is
 * passed straight through in the first argument register. */
/* Object-system record pointer; byte 0 is the "object system active" flag. */
extern unsigned char *g_objectSystem[4];
void FUN_00126360(void *allocation);
void thunk_FUN_002ed460__002ff810(void *allocation);

void igMemoryPoolContextInfo_DeleteAllocation(void *allocation) {
    if (*g_objectSystem[0] != 0) {
        thunk_FUN_002ed460__002ff810(allocation);
        return;
    }
    FUN_00126360(allocation);
}
