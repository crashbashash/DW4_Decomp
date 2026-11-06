/* Returns FUN_0025db90 of the object's handle (+4) when FUN_0025db70 reports it positive and the
 * state byte (+1) is 2 or 3; otherwise 0. */
typedef struct Obj_267438 {
    unsigned char pad0;
    unsigned char state;    /* 0x01 */
    char pad2[2];
    int handle;             /* 0x04 */
} Obj_267438;

int FUN_0025db70(int handle);
int FUN_0025db90(int handle);

int FUN_00267438(Obj_267438 *obj) {
    if (FUN_0025db70(obj->handle) > 0 && (unsigned int)(obj->state - 2) < 2) {
        return FUN_0025db90(obj->handle);
    }
    return 0;
}
