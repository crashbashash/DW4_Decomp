#include "dw4/cri/sfdsj.h"

enum { SJRMT_RPC_PUTCHUNK = 40 };

int DTX_CallUrpc(int fno, int *send, int nsend, int *recv, int nrecv);
extern int sjrmt_sbuf[4];

/* PutChunk on an IOP-side SJ, by remote call. */
int SJRMT_PutChunk(int sjrmt, int line, SfdSjChunk *ck)
{
    char *data = ck->data;

    sjrmt_sbuf[0] = sjrmt;
    sjrmt_sbuf[1] = line;
    sjrmt_sbuf[2] = (int)data;
    sjrmt_sbuf[3] = ck->len;
    return DTX_CallUrpc(SJRMT_RPC_PUTCHUNK, sjrmt_sbuf, 4, 0, 0);
}
