/* Reports DAT_004ee270 through FUN_002607e8 for a null object; otherwise, when the byte at offset
 * 1 is 0, calls FUN_002771d0 on the handle at offset 148. */
typedef struct Object_263b40 {
    char f0;
    char f1;            /* 0x01 */
    char pad2[146];
    void *handle;       /* 0x94 */
} Object_263b40;

extern char DAT_004ee270[];
void FUN_002607e8(const char *message);
void FUN_002771d0(void *handle);

void FUN_00263b40(Object_263b40 *object) {
    if (object == 0) {
        FUN_002607e8(DAT_004ee270);
        return;
    }
    /* matching construct: manual — early return (not an if block) lets ee-gcc emit the tail call */
    if (object->f1 != 0) {
        return;
    }
    FUN_002771d0(object->handle);
}
