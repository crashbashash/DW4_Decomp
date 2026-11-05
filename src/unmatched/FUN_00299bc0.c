/* 0x00299bc0 — FUN_00299bc0 (96 bytes). When FUN_00299f88 reports state 1, invokes the +36 callback of the record from FUN_00299f68 (if both exist) with the object's +20 word and `arg`. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct {
    char pad0[36];
    void (*callback)(int ctx, int arg); /* 36 */
} Hooks299bc0;

typedef struct {
    char pad0[20];
    int f20;
} Obj299bc0;

extern int FUN_00299f88(void *obj);
extern Hooks299bc0 *FUN_00299f68(void);

void FUN_00299bc0(Obj299bc0 *obj, int arg) {
    Hooks299bc0 *hooks;

    if (FUN_00299f88(obj) == 1) {
        int ctx;

        hooks = FUN_00299f68();
        /* matching construct: manual — the context is read before the hook tests (retail
         * loads it in the first branch's delay slot). */
        ctx = obj->f20;
        if (hooks != 0 && hooks->callback != 0) {
            hooks->callback(ctx, arg);
        }
    }
}
