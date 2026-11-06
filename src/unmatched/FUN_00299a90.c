/* When FUN_00299f88 reports state 1, invokes the +24 callback of the record from FUN_00299f68 (if
 * both exist) with the object's +20 word. */
typedef struct {
    char pad0[24];
    void (*callback)(int arg); /* 24 */
} Hooks299a90;

typedef struct {
    char pad0[20];
    int f20;
} Obj299a90;

extern int FUN_00299f88(void *obj);
extern Hooks299a90 *FUN_00299f68(void);

void FUN_00299a90(Obj299a90 *obj) {
    Hooks299a90 *hooks;

    if (FUN_00299f88(obj) == 1) {
        int arg;

        hooks = FUN_00299f68();
        /* matching construct: manual — the argument is read before the hook tests (retail
         * loads it in the first branch's delay slot). */
        arg = obj->f20;
        if (hooks != 0 && hooks->callback != 0) {
            hooks->callback(arg);
        }
    }
}
