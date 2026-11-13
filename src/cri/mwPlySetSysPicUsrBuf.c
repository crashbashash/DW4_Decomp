/* Installs the player's own picture user buffer: the part of `buf` past `offset` becomes the
 * built-in picture user buffer (unit = offset) and is made current; the first `offset` bytes are
 * kept as the user data buffer, and the current user data is cleared. */
#include "dw4/cri/mwply.h"

void mwPlySetSysPicUsrBuf(MwsfdPly *ply, char *buf, int bufsize, int offset) {
    MwsfdPicUsrBuf *ub;
    int size;
    char *addr;

    /* matching construct: brute-force grouping — statement blocks in do/while(0) (loop notes are
     * scheduling barriers); retail keeps exactly this store order with the arithmetic hoisted */
    do { ub = &ply->sysPicUsrBuf; } while (0);
    do {
        size = bufsize - offset;
        addr = buf + offset;
        ply->udbufsize = offset;
        ply->udsize = 0;
    } while (0);
    do {
        ply->udbuf = buf;
        ply->ud = 0;
    } while (0);
    do {
        ply->picUsrBuf = ub;
        ub->size = size;
    } while (0);
    do {
        ub->unit = offset;
        ub->addr = addr;
    } while (0);
}
