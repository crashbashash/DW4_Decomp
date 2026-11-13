/* CRI SJRMT: SJs that live on the IOP, driven from the EE by DTX remote calls. A handle is the IOP-side
 * SJ's address; each call packs its arguments into one send buffer and reads the answer from one receive
 * buffer. */
#include "dw4/cri/sfdsj.h"

enum SjRmtRpc {
    SJRMT_RPC_RBF_CREATE = 32,
    SJRMT_RPC_MEM_CREATE = 33,
    SJRMT_RPC_UNI_CREATE = 34,
    SJRMT_RPC_DESTROY = 35,
    SJRMT_RPC_GET_UUID = 36,
    SJRMT_RPC_RESET = 37,
    SJRMT_RPC_GET_CHUNK = 38,
    SJRMT_RPC_UNGET_CHUNK = 39,
    SJRMT_RPC_PUT_CHUNK = 40,
    SJRMT_RPC_GET_NUM_DATA = 41,
    SJRMT_RPC_IS_GET_CHUNK = 42
};

int DTX_CallUrpc(int fno, int *send, int nsend, int *recv, int nrecv);
void DTX_Init(void);
void DTX_Finish(void);

extern int sjrmt_uuid[4];
extern int sjrmt_sbuf[4];
extern int sjrmt_rbuf[4];
extern char *volatile sjrmt_build;  /* the version string, read so it is linked */
extern int sjrmt_init_cnt;

int SJRMT_RbfCreate(int buf, int bsize, int xsize)
{
    sjrmt_sbuf[0] = buf;
    sjrmt_sbuf[1] = bsize;
    sjrmt_sbuf[2] = xsize;
    DTX_CallUrpc(SJRMT_RPC_RBF_CREATE, sjrmt_sbuf, 3, sjrmt_rbuf, 1);
    return sjrmt_rbuf[0];
}

int SJRMT_MemCreate(int buf, int bsize)
{
    sjrmt_sbuf[0] = buf;
    sjrmt_sbuf[1] = bsize;
    DTX_CallUrpc(SJRMT_RPC_MEM_CREATE, sjrmt_sbuf, 2, sjrmt_rbuf, 1);
    return sjrmt_rbuf[0];
}

/* An SJUNI on the IOP over a work area there. */
int SJRMT_Create(int mode, int work, int wksize)
{
    sjrmt_sbuf[0] = mode;
    sjrmt_sbuf[1] = work;
    sjrmt_sbuf[2] = wksize;
    DTX_CallUrpc(SJRMT_RPC_UNI_CREATE, sjrmt_sbuf, 3, sjrmt_rbuf, 1);
    return sjrmt_rbuf[0];
}

void SJRMT_Destroy(int sjrmt)
{
    sjrmt_sbuf[0] = sjrmt;
    DTX_CallUrpc(SJRMT_RPC_DESTROY, sjrmt_sbuf, 1, 0, 0);
}

int *SJRMT_GetUuid(int sjrmt)
{
    sjrmt_sbuf[0] = sjrmt;
    DTX_CallUrpc(SJRMT_RPC_GET_UUID, sjrmt_sbuf, 1, sjrmt_rbuf, 4);
    sjrmt_uuid[0] = sjrmt_rbuf[0];
    sjrmt_uuid[1] = sjrmt_rbuf[1];
    sjrmt_uuid[2] = sjrmt_rbuf[2];
    sjrmt_uuid[3] = sjrmt_rbuf[3];
    return sjrmt_uuid;
}

void SJRMT_Reset(int sjrmt)
{
    sjrmt_sbuf[0] = sjrmt;
    DTX_CallUrpc(SJRMT_RPC_RESET, sjrmt_sbuf, 1, 0, 0);
}

void SJRMT_GetChunk(int sjrmt, int line, int nbyte, SfdSjChunk *ck)
{
    sjrmt_sbuf[0] = sjrmt;
    sjrmt_sbuf[1] = line;
    sjrmt_sbuf[2] = nbyte;
    DTX_CallUrpc(SJRMT_RPC_GET_CHUNK, sjrmt_sbuf, 3, sjrmt_rbuf, 2);
    ck->data = (char *)sjrmt_rbuf[0];
    ck->len = sjrmt_rbuf[1];
}

void SJRMT_UngetChunk(int sjrmt, int line, SfdSjChunk *ck)
{
    char *data = ck->data;

    sjrmt_sbuf[0] = sjrmt;
    sjrmt_sbuf[1] = line;
    sjrmt_sbuf[2] = (int)data;
    sjrmt_sbuf[3] = ck->len;
    DTX_CallUrpc(SJRMT_RPC_UNGET_CHUNK, sjrmt_sbuf, 4, 0, 0);
}

int SJRMT_PutChunk(int sjrmt, int line, SfdSjChunk *ck)
{
    char *data = ck->data;

    sjrmt_sbuf[0] = sjrmt;
    sjrmt_sbuf[1] = line;
    sjrmt_sbuf[2] = (int)data;
    sjrmt_sbuf[3] = ck->len;
    return DTX_CallUrpc(SJRMT_RPC_PUT_CHUNK, sjrmt_sbuf, 4, 0, 0);
}

int SJRMT_GetNumData(int sjrmt, int line)
{
    sjrmt_sbuf[0] = sjrmt;
    sjrmt_sbuf[1] = line;
    DTX_CallUrpc(SJRMT_RPC_GET_NUM_DATA, sjrmt_sbuf, 2, sjrmt_rbuf, 1);
    return sjrmt_rbuf[0];
}

/* The IOP answers in two words, though only one is asked for: the result and the size available. */
int SJRMT_IsGetChunk(int sjrmt, int line, int nbyte, int *rbyte)
{
    sjrmt_sbuf[0] = sjrmt;
    sjrmt_sbuf[1] = line;
    sjrmt_sbuf[2] = nbyte;
    DTX_CallUrpc(SJRMT_RPC_IS_GET_CHUNK, sjrmt_sbuf, 3, sjrmt_rbuf, 1);
    *rbyte = sjrmt_rbuf[1];
    return sjrmt_rbuf[0];
}

void SJRMT_Init(void)
{
    sjrmt_build;
    if (sjrmt_init_cnt == 0) {
        DTX_Init();
    }
    sjrmt_init_cnt++;
}

void SJRMT_Finish(void)
{
    if (--sjrmt_init_cnt == 0) {
        DTX_Finish();
    }
}
