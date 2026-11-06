/* Decode-server step for a playing handle: while
 * the +117 flag is 1, waits for FUN_002773d0 on +76 and then terminates the stream and clears the
 * flag, else runs FUN_00295b10; a stream status of 6 moves the handle to state 3. */
extern int FUN_002773d0(int obj);
extern int FUN_002ac498(int stream);
extern void FUN_00295b10(void *ply);
extern int FUN_002ad910(int stream);
extern void FUN_0029a320(const char *msg);
extern char DAT_004f4a70[]; /* "E99072102 mwlSfdExecDecSvrPlaying: can't term" */

typedef struct {
    char pad0[8];
    int state;    /* 8 */
    char pad12[52];
    int stream;   /* 64 */
    char pad68[8];
    int f76;
    char pad80[37];
    signed char f117;
} Ply29a7d8;

void FUN_0029a7d8(Ply29a7d8 *ply) {
    int stream = ply->stream;

    if (ply->f117 == 1) {
        if (FUN_002773d0(ply->f76) == 0) {
            if (FUN_002ac498(stream) != 0) {
                FUN_0029a320(DAT_004f4a70);
            }
            ply->f117 = 0;
        }
    } else {
        FUN_00295b10(ply);
    }
    if (FUN_002ad910(stream) == 6) {
        ply->state = 3;
    }
}
