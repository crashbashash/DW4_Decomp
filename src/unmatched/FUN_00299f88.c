/* 0x00299f88 — FUN_00299f88 (64 bytes). Returns 1 when the hook record exists (FUN_00299f68), the object is in state 1 and its +20 word is set; else 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void *FUN_00299f68(void *obj);

typedef struct {
    int state;    /* 0 */
    char pad4[16];
    int f20;
} Obj299f88;

int FUN_00299f88(Obj299f88 *obj) {
    if (FUN_00299f68(obj) == 0) {
        return 0;
    }
    if (obj->state != 1) {
        return 0;
    }
    return obj->f20 != 0;
}
