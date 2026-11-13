/* Attaches a caller picture user buffer and makes it current, or with buf == 0 detaches it and
 * falls back to the built-in one; the buffer must hold (nfrmPoolWk + 4) units. Then hands the
 * current buffer to SFD. */
#include "dw4/cri/mwply.h"

extern char mwPlyAttachPicUsrBuf_short_msg[]; /* "E02120503: mwPlyAttachPicUsrBuf(): bufsize is short." */
void mwsfcre_AttachPicUsrBuf(MwsfdPly *ply);
void mwsfd_Error(const char *msg);

void mwPlyAttachPicUsrBuf(MwsfdPly *ply, char *buf, int size, int unit)
{
    MwsfdPicUsrBuf *ub = &ply->attPicUsrBuf;
    MwsfdPicUsrBuf *sys = &ply->sysPicUsrBuf;

    if (buf == 0) {
        ub->addr = 0;
        ub->size = 0;
        ub->unit = 0;
        ply->picUsrBuf = sys;
    } else {
        if (size < (ply->cre.nfrmPoolWk + 4) * unit) {
            mwsfd_Error(mwPlyAttachPicUsrBuf_short_msg);
            return;
        }
        ub->addr = buf;
        ub->size = size;
        ub->unit = unit;
        ply->picUsrBuf = ub;
    }
    mwsfcre_AttachPicUsrBuf(ply);
}
