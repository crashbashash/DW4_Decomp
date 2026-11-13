/* deci2.c - libkernl's DECI2 calls: each packs its arguments into a block and passes it, with the
 * function's number, to the kernel's Deci2Call. */

#define DECI2_OPEN 1
#define DECI2_CLOSE 2
#define DECI2_REQ_SEND 3
#define DECI2_POLL 4
#define DECI2_KPUTS 16
#define DECI2_GRP_OPEN 32
#define DECI2_GRP_CLOSE 33
#define DECI2_EX_RECV -5
#define DECI2_EX_SEND -6
#define DECI2_EX_REQ_SEND -7
#define DECI2_EX_LOCK -8
#define DECI2_EX_UNLOCK -9

/* uncached alias of KSEG0 */
#define UNCACHED 0x20000000

int Deci2Call(int call, int *args);

/* the kernel's DECI2 work area, read through the uncached alias */
static char userarea[64];

int sceDeci2Open(unsigned short protocol, void *opt, void (*handler)(int event, int param, void *opt))
{
    int args[4];
    args[0] = protocol;
    args[1] = (int)opt;
    args[2] = (int)handler;
    args[3] = (int)userarea | UNCACHED;
    return Deci2Call(DECI2_OPEN, args);
}

int sceDeci2Close(int socket)
{
    int args[4];
    args[0] = socket;
    return Deci2Call(DECI2_CLOSE, args);
}

int sceDeci2ReqSend(int socket, char dest)
{
    int args[4];
    args[0] = socket;
    args[1] = dest;
    return Deci2Call(DECI2_REQ_SEND, args);
}

void sceDeci2Poll(int socket)
{
    int args[4];
    args[0] = socket;
    Deci2Call(DECI2_POLL, args);
}

int sceDeci2GrpOpen(unsigned char group, void *opt, void (*handler)(int event, int param, void *opt))
{
    int args[8];
    args[0] = group;
    args[1] = (int)opt;
    args[2] = (int)handler;
    return Deci2Call(DECI2_GRP_OPEN, args);
}

int sceDeci2GrpClose(int socket)
{
    int args[4];
    args[0] = socket;
    return Deci2Call(DECI2_GRP_CLOSE, args);
}

int sceDeci2ExRecv(int socket, void *buf, unsigned short size)
{
    int args[4];
    args[0] = socket;
    args[1] = (int)buf;
    args[2] = size;
    return Deci2Call(DECI2_EX_RECV, args);
}

int sceDeci2ExSend(int socket, void *buf, unsigned short size)
{
    int args[4];
    args[0] = socket;
    args[1] = (int)buf;
    args[2] = size;
    return Deci2Call(DECI2_EX_SEND, args);
}

int sceDeci2ExReqSend(int socket, char dest)
{
    int args[4];
    args[0] = socket;
    args[1] = dest;
    return Deci2Call(DECI2_EX_REQ_SEND, args);
}

int sceDeci2ExLock(int socket)
{
    int args[4];
    args[0] = socket;
    return Deci2Call(DECI2_EX_LOCK, args);
}

int sceDeci2ExUnLock(int socket)
{
    int args[4];
    args[0] = socket;
    return Deci2Call(DECI2_EX_UNLOCK, args);
}

int kputs(char *s)
{
    int args[4];
    args[0] = (int)s;
    return Deci2Call(DECI2_KPUTS, args);
}
