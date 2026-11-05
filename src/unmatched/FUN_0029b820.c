/* 0x0029b820 — FUN_0029b820 (44 bytes). Calls vtable slot +24 of the stream joint as (sj, 0, a, b). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SjObj SjObj;
typedef struct {
    char pad0[24];
    void (*fn24)(SjObj *sj, int zero, int a, int b); /* 24 */
} SjVtbl;
struct SjObj {
    SjVtbl *vtbl;
};

void FUN_0029b820(SjObj *sj, int a, int b) {
    sj->vtbl->fn24(sj, 0, a, b);
}
