/* When FUN_00299f88 reports state 1, returns the +28 callback of the record from FUN_00299f68 (if
 * both exist) applied to the object's +20 word; otherwise 0. */
typedef struct {
    char pad0[28];
    int (*callback)(int ctx); /* 28 */
} Hooks299ae8;

typedef struct {
    char pad0[20];
    int f20;
} Obj299ae8;

extern int FUN_00299f88(void *obj);
extern Hooks299ae8 *FUN_00299f68(void);

int FUN_00299ae8(Obj299ae8 *obj) {
    Hooks299ae8 *hooks;
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
