/* 0x00291048 — FUN_00291048 (88 bytes). Takes a free handle (FUN_002910a0), clears 1016 bytes of it (FUN_00291238), initialises it (FUN_002910f0) and stores FUN_00291480's result at +944. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Handle00291048 {
    char pad0[944];
    int f944; /* +944 */
};

struct Handle00291048 *FUN_002910a0(void);
void FUN_00291238(void *p, int size);
struct Handle00291048 *FUN_002910f0(struct Handle00291048 *handle);
int FUN_00291480(struct Handle00291048 *handle);

struct Handle00291048 *FUN_00291048(void) {
    struct Handle00291048 *handle;

    handle = FUN_002910a0();
    if (handle == 0) {
        return 0;
    }
    FUN_00291238(handle, 1016);
    handle = FUN_002910f0(handle);
    handle->f944 = FUN_00291480(handle);
    return handle;
}
