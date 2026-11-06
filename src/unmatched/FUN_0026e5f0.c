/* Once the source (+4) reports state 3 (FUN_002661d0), checks every one of its FUN_00267228
 * channel streams (+24) with the vtable +36 query; when all report less than 64, sets the object's
 * state byte (+1) to 4. The count and the last query are kept in DAT_004a8ea4/DAT_004a8ea8. */
typedef struct Stream_26e5f0 Stream_26e5f0;
typedef struct StreamVtbl_26e5f0 {
    void *pad0[9];
    int (*query)(Stream_26e5f0 *stream, int which);    /* 0x24 */
} StreamVtbl_26e5f0;
struct Stream_26e5f0 {
    StreamVtbl_26e5f0 *vtbl;  /* 0x00 */
};

typedef struct Obj_26e5f0 {
    signed char pad0;
    signed char state;          /* 0x01 */
    char pad2[2];
    int source;                 /* 0x04 */
    char pad8[16];
    Stream_26e5f0 *streams[8];  /* 0x18 */
} Obj_26e5f0;

extern int DAT_004a8ea4;
extern int DAT_004a8ea8;
int FUN_002661d0(int source);
int FUN_00267228(int source);

/* matching construct: permuter — implicit int: declared int with no return statement (retail's early-exit branch shape) */
int FUN_0026e5f0(Obj_26e5f0 *obj) {
    Stream_26e5f0 *stream;
    int count;
    int i;

    if (FUN_002661d0(obj->source) == 3) {
        count = FUN_00267228(obj->source);
        DAT_004a8ea4 = count;
        for (i = 0; i < count; i++) {
            stream = obj->streams[i];
            DAT_004a8ea8 = stream->vtbl->query(stream, 1);
            if (DAT_004a8ea8 >= 64) {
                break;
            }
        }
        if (i == count) {
            obj->state = 4;
        }
    }
}

