/* Returns a playback handle's input stream joint at +468 (its error string names it
 * mwPlyGetInputSj), or 0 for an invalid handle. */
extern int FUN_002968c0(void *ply);
extern void FUN_0029a320(const char *msg);
extern char DAT_004f3f08[]; /* "E1122624: mwPlyGetInputSj: handle is invalid." */

typedef struct {
    char pad0[468];
    int inputSj;  /* 468 */
} Ply2971b0;

int FUN_002971b0(Ply2971b0 *ply) {
    if (FUN_002968c0(ply) == 0) {
        FUN_0029a320(DAT_004f3f08);
        return 0;
    }
    return ply->inputSj;
}
