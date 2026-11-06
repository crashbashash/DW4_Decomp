/* 0x0027d400 — FUN_0027d400 (112 bytes). Returns the length of a handle's linked list (head at +20, next pointer at 0 of each node); a NULL or unused (+4 clear) handle is reported through FUN_0027b2e0 and returns 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Node_27d400 {
    struct Node_27d400 *next;   /* 0x00 */
} Node_27d400;

typedef struct Handle_27d400 {
    int pad0;
    signed char used;           /* 0x04 */
    char pad5[15];
    Node_27d400 *head;          /* 0x14 */
} Handle_27d400;

extern char E2004090281_NULL_pointer_is_specified[];   /* 'E2004090281 : NULL pointer is specified.' */
extern char E2004090282_Specified_handle_is_invalid[]; /* 'E2004090282 : Specified handle is invalid.' */
int FUN_0027b2e0(const char *message);

int FUN_0027d400(Handle_27d400 *handle) {
    Node_27d400 *node;
    int count;

    if (handle == 0) {
        FUN_0027b2e0(E2004090281_NULL_pointer_is_specified);
        return 0;
    }
    if (handle->used == 0) {
        FUN_0027b2e0(E2004090282_Specified_handle_is_invalid);
        return 0;
    }
    count = 0;
    for (node = handle->head; node != 0; node = node->next) {
        count++;
    }
    return count;
}

