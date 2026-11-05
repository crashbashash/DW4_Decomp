/* CRI ADX stream-owner poll: when a stream handle (+28) is attached, take the
 * library lock, query its state and settle the owner (kind byte at +2) for the
 * three terminal states 0, 3 and 9 (jump table at 0x4f01c0, ten entries),
 * then release the handle; the lock is dropped on every non-null path. */
typedef struct AdxOwner {
    char used;
    char pad0;
    signed char kind;
    char pad1;
    int pad2;
    int pad3;
    int total;      /* +12 */
    int step;       /* +16 */
    int last_step;  /* +20 */
    int pad4;
    int stm;        /* +28 */
} AdxOwner;

extern void FUN_0027e1f0(void);
extern void FUN_0027e268(void);
extern int FUN_00271938(int stm);
extern void FUN_002716f8(int stm);

void FUN_00273a90(AdxOwner *o)
{
    if (o->stm == 0)
        return;
    FUN_0027e1f0();
    switch (FUN_00271938(o->stm)) {
    case 9:
        o->kind = 3;
        FUN_002716f8(o->stm);
        o->stm = 0;
        break;
    case 3:
        o->last_step = o->step;
        o->total += o->step;
        o->kind = 1;
        FUN_002716f8(o->stm);
        o->stm = 0;
        break;
    case 0:
        o->kind = 0;
        FUN_002716f8(o->stm);
        o->stm = 0;
        break;
    case 1: case 2: case 4: case 5: case 6: case 7: case 8:
        break;
    }
    FUN_0027e268();
}
