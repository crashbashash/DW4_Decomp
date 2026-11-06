/* Releases the current frame of a Sofdec playback handle (its error string names it
 * mwPlyRelCurFrm): rejects an invalid handle, otherwise frees the frame through FUN_002ac600 when
 * one is held and advances the frame counters. */
extern int FUN_002968c0(void *ply);
extern void FUN_0029a320(const char *msg);
extern void *FUN_002963a8(void *ply);
extern int FUN_002ac600(void *stream, int frame);
extern char DAT_004f31d8[]; /* "E1122615: mwPlyRelCurFrm: handle is invalid." */

typedef struct {
    char pad0[124];
    int frame;    /* 124 */
    int f128;
    int f132;
} Ply294138;

void FUN_00294138(Ply294138 *ply) {
    int limit;
    int count;
    int frame;
    void *stream;

    if (FUN_002968c0(ply) == 0) {
        FUN_0029a320(DAT_004f31d8);
        return;
    }
    limit = ply->f128;
    count = ply->f132;
    frame = ply->frame;
    stream = FUN_002963a8(ply);
    if (count < limit) {
        FUN_002ac600(stream, frame);
        ply->f128 = ply->f132 = ply->f132 + 1;
    }
}
