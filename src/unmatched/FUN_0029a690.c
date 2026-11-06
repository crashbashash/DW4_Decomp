/* When the handle's stream reports status 3, prepares playback (FUN_00295398, FUN_00295908 unless
 * flagged at +118) and, if linking is requested at +116, reports a failed stream link (error
 * string from mwPlyStartXX). */
extern int FUN_002ad910(int stream);
extern int FUN_00295398(void *ply);
extern void FUN_00295908(void *ply, int arg);
extern int FUN_0029ece8(int stream);
extern void FUN_0029a320(const char *msg);
extern char DAT_004f4a10[]; /* "E99072103 mwPlyStartXX: can't link stream" */

typedef struct {
    char pad0[64];
    int stream;   /* 64 */
    char pad68[48];
    signed char f116;
    signed char f117;
    signed char f118;
} Ply29a690;

void FUN_0029a690(Ply29a690 *ply) {
    if (FUN_002ad910(ply->stream) == 3) {
        FUN_00295398(ply);
        if (ply->f118 == 0) {
            FUN_00295908(ply, 0);
        }
        if (ply->f116 == 1 && FUN_0029ece8(ply->stream) != 0) {
            FUN_0029a320(DAT_004f4a10);
        }
    }
}
