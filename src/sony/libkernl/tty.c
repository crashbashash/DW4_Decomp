/* tty.c - libkernl's console over DECI2: sceTtyWrite sends a TTYP packet to the host and polls until
 * the handler reports it written; the handler queues what the host types, and sceTtyRead takes it out
 * a line at a time. */

#include "dw4/libkernl.h"

typedef unsigned int u_int;
typedef unsigned char u_char;

#define DECI2_READ 1
#define DECI2_READDONE 2
#define DECI2_WRITE 3
#define DECI2_WRITEDONE 4

#define DECI2_NODE_EE 'E'
#define DECI2_NODE_HOST 'H'

#define PROTO_TTYP 0x210

#define TTY_BUFSZ 320
#define TTY_MAX_DATA 256
#define TTY_QUEUE_SIZE 256

/* KSEG1: the buffers are read and written by DMA, so the CPU reaches them uncached */
#define UNCACHED(p) ((u_char *)((u_int)(p) | 0x20000000))

typedef struct {
    unsigned short len;
    unsigned short rsvd;
    unsigned short proto;
    unsigned char source;
    unsigned char destination;
} sceDeci2Hdr;

/* a TTYP packet: the DECI2 header, a word the protocol leaves zero, then the text */
typedef struct {
    sceDeci2Hdr hdr;
    u_int reserved;
    char data[TTY_MAX_DATA];
} TtyPacket;

/* the ring of characters received from the host */
typedef struct {
    int size;
    volatile int count;
    char *rp;
    char *wp;
    char buf[TTY_QUEUE_SIZE];
} Queue;

/* the state shared with the DECI2 handler */
typedef struct {
    volatile int s;
    volatile u_int wlen;
    volatile u_int rlen;
    volatile int writing;
    u_char *wptr;
    u_char *rptr;
    Queue *queue;
} TtyInfo;

int kprintf(const char *format, ...);
int sceDeci2Open(unsigned short protocol, void *opt, void (*handler)(int event, int param, void *opt));
int sceDeci2ReqSend(int s, char dest);
void sceDeci2Poll(int s);
int sceDeci2ExRecv(int s, void *buf, unsigned short size);
int sceDeci2ExSend(int s, void *buf, unsigned short size);

static Queue *QueueInit(int size);
static void QueuePeekWriteDone(Queue *queue);
static void QueuePeekReadDone(Queue *queue);
void sceTtyHandler(int event, int param, TtyInfo *ti);

static TtyInfo tinfo;
static u_char wbuf[TTY_BUFSZ] __attribute__((aligned(64)));
static u_char rbuf[TTY_BUFSZ] __attribute__((aligned(64)));

static Queue *QueueInit(int size)
{
    static Queue q;
    Queue *queue = &q;

    queue->size = size;
    queue->count = 0;
    queue->wp = queue->buf;
    queue->rp = queue->buf;
    return queue;
}

static void QueuePeekWriteDone(Queue *queue)
{
    queue->count++;
    if (++queue->wp == queue->buf + queue->size) {
        queue->wp = queue->buf;
    }
}

static void QueuePeekReadDone(Queue *queue)
{
    queue->count--;
    if (++queue->rp == queue->buf + queue->size) {
        queue->rp = queue->buf;
    }
}

void sceTtyHandler(int event, int param, TtyInfo *ti)
{
    int n;
    TtyPacket *packet;

    switch (event) {
    case DECI2_READ:
    case DECI2_READDONE:
        if (param != 0) {
            if (ti->rlen + param > TTY_BUFSZ) {
                kprintf("TTY: packet size larger than expect\n");
            }
            if ((param = sceDeci2ExRecv(ti->s, &ti->rptr[ti->rlen], param)) < 0) {
                kprintf("TTY: receive error");
            }
            ti->rlen += param;
        } else {
            packet = (TtyPacket *)ti->rptr;
            for (param = sizeof(sceDeci2Hdr) + sizeof(u_int); param < packet->hdr.len; param++) {
                *ti->queue->wp = ti->rptr[param];
                QueuePeekWriteDone(ti->queue);
            }
            ti->rlen = 0;
        }
        break;
    case DECI2_WRITE:
        if ((n = sceDeci2ExSend(ti->s, ti->wptr, ti->wlen)) < 0) {
            kprintf("TTY: send err %d\n", n);
            ti->writing = 0;
        } else {
            ti->wptr += n;
            ti->wlen -= n;
        }
        break;
    case DECI2_WRITEDONE:
        if (ti->wlen != 0) {
            kprintf("TTY: err ti->wlen=%08x\n", ti->wlen);
        }
        ti->writing = 0;
        break;
    }
}

int sceTtyWrite(char *buf, int n)
{
    int written = 0;
    int datalen = 0;
    int intr;
    TtyPacket *packet;
    char *data;

    if (tinfo.writing) {
        return -1;
    }
    intr = DIntr();
    tinfo.writing = 1;
    tinfo.wptr = UNCACHED(wbuf);
    packet = (TtyPacket *)tinfo.wptr;
    data = packet->data;
    while (n--) {
        if (*buf == '\n') {
            *data++ = '\r';
            datalen++;
            if (datalen >= TTY_MAX_DATA) {
                break;
            }
        }
        *data++ = *buf++;
        datalen++;
        written++;
        if (datalen >= TTY_MAX_DATA) {
            break;
        }
    }
    tinfo.wlen = sizeof(sceDeci2Hdr) + sizeof(u_int) + datalen;
    packet->hdr.len = tinfo.wlen;
    if (sceDeci2ReqSend(tinfo.s, packet->hdr.destination) < 0) {
        tinfo.writing = 0;
        if (intr) {
            EIntr();
        }
        return -1;
    }
    while (tinfo.writing) {
        sceDeci2Poll(tinfo.s);
    }
    if (intr) {
        EIntr();
    }
    return written;
}

int sceTtyRead(char *buf, int n)
{
    int i;

    for (i = 0; i < n; i++) {
        while (tinfo.queue->count == 0) {
        }
        buf[i] = *tinfo.queue->rp;
        QueuePeekReadDone(tinfo.queue);
        if (buf[i] == '\n' || buf[i] == '\r') {
            return i + 1;
        }
    }
    return i;
}

int sceTtyInit(void)
{
    TtyPacket *packet;

    FlushCache(0);
    if ((tinfo.s = sceDeci2Open(PROTO_TTYP, &tinfo, (void *)sceTtyHandler)) < 0) {
        return 0;
    }
    tinfo.writing = 0;
    tinfo.wlen = 0;
    tinfo.rlen = 0;
    tinfo.rptr = UNCACHED(rbuf);
    tinfo.wptr = UNCACHED(wbuf);
    packet = (TtyPacket *)tinfo.wptr;
    packet->hdr.proto = PROTO_TTYP;
    packet->hdr.source = DECI2_NODE_EE;
    packet->hdr.destination = DECI2_NODE_HOST;
    packet->hdr.rsvd = 0;
    packet->reserved = 0;
    tinfo.queue = QueueInit(TTY_QUEUE_SIZE);
    return 1;
}
