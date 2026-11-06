/* Runs one decode-server pass for a playback handle bracketed by FUN_0029af20(ply, 1)..(ply, 0):
 * handles in state 1 become current (DAT_004be8b0), drive their stream with FUN_002aa7b8 and, if
 * requested at +8, run FUN_0029a868; returns non-zero unless FUN_002aa728 reports 1. */
extern void FUN_0029af20(void *ply, int flag);
extern void FUN_0029af30(void *ply, int flag);
extern void FUN_002aa7b8(int stream);
extern int FUN_002aa728(int stream);
extern void FUN_0029a868(void *ply);
extern void *DAT_004be8b0; /* current handle */

typedef struct {
    int f0;
    int state;    /* 4 */
    int f8;
    char pad12[52];
    int stream;   /* 64 */
    char pad68[40];
    int f108;
} Ply29ade0;

int FUN_0029ade0(Ply29ade0 *ply) {
    int stream = ply->stream;
    int state;

    FUN_0029af20(ply, 1);
    state = ply->state;
    if (state != 1) {
        FUN_0029af20(ply, 0);
        return 0;
    }
    DAT_004be8b0 = ply;
    FUN_0029af30(ply, 1);
    FUN_002aa7b8(stream);
    FUN_0029af30(ply, 0);
    if (ply->f8 == 0) {
        ply->f108 = 0;
    } else {
        ply->f108 = state;
        FUN_0029a868(ply);
    }
    FUN_0029af20(ply, 0);
    return FUN_002aa728(stream) != 1;
}
