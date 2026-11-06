/* Returns a playback handle's SFD decoder handle at +64,
 * or 0 for an invalid handle. */
extern int FUN_002968c0(void *ply);
extern void FUN_0029a320(const char *msg);
extern char DAT_004f39e8[]; /* "E1122640: mwPlyGetSfdHn: handle is invalid." */

typedef struct {
    char pad0[64];
    int sfdHn;    /* 64 */
} Ply2963a8;

int FUN_002963a8(Ply2963a8 *ply) {
    if (FUN_002968c0(ply) == 0) {
        FUN_0029a320(DAT_004f39e8);
        return 0;
    }
    return ply->sfdHn;
}
