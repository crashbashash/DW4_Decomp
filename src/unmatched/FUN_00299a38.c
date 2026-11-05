/* 0x00299a38 — FUN_00299a38 (88 bytes). When FUN_00299f88 reports state 1, invokes the +20 callback of the record from FUN_00299f68 (if both exist) with the object's +20 and +12 words. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct {
    char pad0[20];
    void (*callback)(int a, int b); /* 20 */
} Hooks299a38;

typedef struct {
    char pad0[12];
    int f12;
    char pad16[4];
    int f20;
} Obj299a38;

extern int FUN_00299f88(void *obj);
extern Hooks299a38 *FUN_00299f68(void);

void FUN_00299a38(Obj299a38 *obj) {
    Hooks299a38 *hooks;

    if (FUN_00299f88(obj) == 1) {
        int arg20;
        int arg12;

        hooks = FUN_00299f68();
        /* matching construct: manual — the argument is read before the hook tests (retail
         * loads it in the first branch's delay slot). */
        arg20 = obj->f20;
        arg12 = obj->f12;
        if (hooks != 0 && hooks->callback != 0) {
            hooks->callback(arg20, arg12);
        }
    }
}
