/* 0x0028f018 — FUN_0028f018 (120 bytes). Reads the object's +692 and +696 words into the two out pointers; when FUN_002913f8 rejects the object it reports error 0xFF03020E through FUN_0028eb38 instead. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int FUN_002913f8(void *obj);
extern int FUN_0028eb38(int zero, int code);

typedef struct {
    char pad0[692];
    int f692;
    int f696;
} Obj28f018;

int FUN_0028f018(Obj28f018 *obj, int *out692, int *out696) {
    if (FUN_002913f8(obj) != 0) {
        return FUN_0028eb38(0, 0xFF03020E);
    }
    *out692 = obj->f692;
    *out696 = obj->f696;
    return 0;
}
