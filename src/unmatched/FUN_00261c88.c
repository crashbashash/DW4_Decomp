/* Releases an object: notifies FUN_00260c20 (event 3, phase 0), stops it when its state is 2,
 * frees its attached handle through FUN_0026a0e0 and FUN_00269f98, clears the 68-byte record and
 * notifies phase 1. */
typedef struct Object_261c88 {
    char used;          /* 0x00 */
    signed char state;  /* 0x01: 2 = running (FUN_00262118 is called first) */
    char pad2[2];
    void *handle;       /* 0x04 */
    char rest[60];
} Object_261c88;

void FUN_00260c20(int event, int phase, void *object, int a3, int a4);
void FUN_00262118(Object_261c88 *object);
void FUN_0026a0e0(void *handle);
void FUN_00269f98(void *handle);
void *memset(void *dst, int value, unsigned int size);

void FUN_00261c88(Object_261c88 *object) {
    void *handle;

    FUN_00260c20(3, 0, object, -1, -1);
    if (object != 0) {
        if (object->state == 2) {
            FUN_00262118(object);
        }
        handle = object->handle;
        if (handle != 0) {
            object->used = 0;
            object->handle = 0;
            FUN_0026a0e0(handle);
            FUN_00269f98(handle);
        }
        memset(object, 0, sizeof(Object_261c88));
        FUN_00260c20(3, 1, object, -1, -1);
    }
}
