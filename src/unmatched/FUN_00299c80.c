/* 0x00299c80 — FUN_00299c80 (104 bytes). When FUN_00299f88 reports state 1, returns the +44 callback of the record from FUN_00299f68 (if both exist) applied to the object's +20 word; otherwise 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct {
    char pad0[44];
    int (*callback)(int ctx); /* 44 */
} Hooks299c80;

typedef struct {
    char pad0[20];
    int f20;
} Obj299c80;

extern int FUN_00299f88(void *obj);
extern Hooks299c80 *FUN_00299f68(void);

int FUN_00299c80(Obj299c80 *obj) {
    Hooks299c80 *hooks;
    int ctx;
    int result = 0;

    if (FUN_00299f88(obj) != 1) {
        return 0;
    }
    hooks = FUN_00299f68();
    /* matching construct: manual — the context is read before the hook tests (retail
     * loads it in the first branch's delay slot). */
    ctx = obj->f20;
    if (hooks != 0 && hooks->callback != 0) {
        result = hooks->callback(ctx);
    }
    return result;
}
