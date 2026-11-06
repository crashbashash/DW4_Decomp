/* Polls the file transfer (+40) of an lsc object with FUN_0026a138 and updates the current queue
 * entry (slot +32 of the 32-byte ring at +56): state 2 stores the progress from FUN_0026a160,
 * state 3 marks the entry done (2) with the full size (+44), state 4 puts the object in error
 * state (+1 = 3). A missing transfer is reported through FUN_002777f8. */
typedef struct LscEntry_277b00 {
    int id;             /* 0x00 */
    int pad4[5];
    int status;         /* 0x18 */
    int done_bytes;     /* 0x1c */
} LscEntry_277b00;      /* 0x20 bytes */

typedef struct Lsc_277b00 {
    signed char pad0;
    signed char state;              /* 0x01 */
    char pad2[30];
    int head;                       /* 0x20 */
    int pad36;
    int transfer;                   /* 0x28 */
    int size;                       /* 0x2c */
    char pad48[8];
    LscEntry_277b00 entries[16];    /* 0x38 */
} Lsc_277b00;

extern char E0007_lsc_fp_NULL[]; /* 'E0007: lsc->fp=NULL\n' */
void FUN_002777f8(const char *format, ...);
int FUN_0026a138(int transfer);
int FUN_0026a160(int transfer);

void FUN_00277b00(Lsc_277b00 *lsc) {
    LscEntry_277b00 *entry;

    if (lsc->transfer == 0) {
        FUN_002777f8(E0007_lsc_fp_NULL);
        return;
    }
    entry = &lsc->entries[lsc->head];
    switch (FUN_0026a138(lsc->transfer)) {
    case 2:
        entry->done_bytes = FUN_0026a160(lsc->transfer);
        break;
    case 3:
        entry->done_bytes = lsc->size;
        entry->status = 2;
        break;
    case 4:
        lsc->state = 3;
        break;
    }
}

