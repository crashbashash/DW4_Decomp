/* Forwards arg to FUN_0025db80 on the object's handle (+4) when FUN_0025db70 reports it positive
 * and the state byte (+1) is 2 or 3; otherwise returns -128. */
typedef struct Obj_2673d0 {
    unsigned char pad0;
    unsigned char state;    /* 0x01 */
    char pad2[2];
    int handle;             /* 0x04 */
} Obj_2673d0;

int FUN_0025db70(int handle);
int FUN_0025db80(int handle, int arg);

int FUN_002673d0(Obj_2673d0 *obj, int arg) {
    if (FUN_0025db70(obj->handle) > 0) {
        if ((unsigned int)(obj->state - 2) < 2) {
            /* matching construct: permuter — the do/while(0) wrapper returns the call result through the shared epilogue */
            do {
                return FUN_0025db80(obj->handle, arg);
            } while (0);
        }
    }
    return -128;
}
