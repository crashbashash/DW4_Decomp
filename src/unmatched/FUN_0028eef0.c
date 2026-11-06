/* Reads the object's +680 word into *out; when FUN_002913f8 rejects the object it reports error
 * 0xFF03020D through FUN_0028eb38 instead. */
extern int FUN_002913f8(void *obj);
extern int FUN_0028eb38(int zero, int code);

typedef struct {
    char pad0[680];
    int f680;
} Obj28eef0;

int FUN_0028eef0(Obj28eef0 *obj, int *out) {
    if (FUN_002913f8(obj) != 0) {
        return FUN_0028eb38(0, 0xFF03020D);
    }
    *out = obj->f680;
    return 0;
}
