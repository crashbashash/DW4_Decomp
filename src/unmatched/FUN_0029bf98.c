/* 0x0029bf98 — FUN_0029bf98 (80 bytes). Looks up an entry with FUN_0029ceb8 and copies its +12 and +16 words out; returns 0, or -1 when there is no entry. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct {
    char pad0[12];
    int f12;
    int f16;
} Entry29bf98;

extern Entry29bf98 *FUN_0029ceb8(void *obj);

int FUN_0029bf98(void *obj, int *out12, int *out16) {
    Entry29bf98 *entry = FUN_0029ceb8(obj);

    if (entry == 0) {
        return -1;
    }
    *out12 = entry->f12;
    *out16 = entry->f16;
    return 0;
}
