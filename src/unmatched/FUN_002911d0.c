/* 0x002911d0 — FUN_002911d0 (104 bytes). Releases a validated handle: FUN_00291498 on it, FUN_00291240 over its 1016 bytes, then marks it free (+392 = 1); error 0xFF030201 goes through FUN_0028eb38. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002913f8(void *handle); /* handle check; non-zero rejects */
int FUN_0028eb38(void *handle, int error);
void FUN_00291498(void *handle);
void FUN_00291240(void *p, int size);

struct Handle002911d0 {
    char pad0[392];
    int free; /* +392: 1 = available (see FUN_002910a0) */
};

int FUN_002911d0(struct Handle002911d0 *handle) {
    if (FUN_002913f8(handle) != 0) {
        return FUN_0028eb38(0, 0xFF030201);
    }
    FUN_00291498(handle);
    FUN_00291240(handle, 1016);
    handle->free = 1;
    return 0;
}
