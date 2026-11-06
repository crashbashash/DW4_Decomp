/* When FUN_00299f88 reports state 1, invokes the +40 callback of the record from FUN_00299f68 (if
 * both exist) with the object's +20 word and `arg`. */
typedef struct {
    char pad0[40];
    void (*callback)(int ctx, int arg); /* 40 */
} Hooks299c20;

typedef struct {
    char pad0[20];
    int f20;
} Obj299c20;

extern int FUN_00299f88(void *obj);
extern Hooks299c20 *FUN_00299f68(void);

void FUN_00299c20(Obj299c20 *obj, int arg) {
    Hooks299c20 *hooks;

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
