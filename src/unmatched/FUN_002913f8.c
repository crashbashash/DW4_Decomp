/* 0x002913f8 — FUN_002913f8 (36 bytes). Records `obj` as the current object (DAT_00573f74) and returns 0 when it is non-NULL and in state 2 (+392), else -1. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void *DAT_00573f74;

typedef struct {
    char pad0[392];
    int state;    /* 392 */
} Obj2913f8;

int FUN_002913f8(Obj2913f8 *obj) {
    DAT_00573f74 = obj;
    if (obj == 0) {
        return -1;
    }
    if (obj->state != 2) {
        return -1;
    }
    return 0;
}
