/* Attaches the additional-information buffer to a playback handle (its warning string names it
 * mwPlyAttachAddInfBuf), warning when it is shorter than 0x20000 bytes. */
extern void FUN_0029a320(const char *msg);
extern char DAT_004f4420[]; /* "W2121001 : mwPlyAttachAddInfBuf(): bufsize is short." */

typedef struct {
    void *buf;
    int size;
} AddInfBuf;

typedef struct {
    char pad0[412];
    AddInfBuf addInf;   /* 412 */
} Ply2985b8;

void FUN_002985b8(Ply2985b8 *ply, void *buf, int size) {
    AddInfBuf *addInf = &ply->addInf;

    if (size < 0x20000) {
        FUN_0029a320(DAT_004f4420);
    }
    addInf->buf = buf;
    addInf->size = size;
}
