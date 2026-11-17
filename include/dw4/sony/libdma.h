/* libdma.h - Sony libdma: the calls made from outside the library (Sony libdma.h). */
#ifndef DW4_SONY_LIBDMA_H
#define DW4_SONY_LIBDMA_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    unsigned int DIR : 1;
    unsigned int p0 : 1;
    unsigned int MOD : 2;
    unsigned int ASP : 2;
    unsigned int TTE : 1;
    unsigned int TIE : 1;
    unsigned int STR : 1;
} tD_CHCR;

typedef union {
    tD_CHCR f;
    unsigned int word;
} uD_CHCR;

/* One channel's register block in the 0x10008000.. DMAC space. */
typedef struct {
    uD_CHCR chcr;
    unsigned int p0[3];
    unsigned int madr;
    unsigned int p1[3];
    unsigned int qwc;
    unsigned int p2[3];
    unsigned int tadr;
    unsigned int p3[3];
    unsigned int as0;
    unsigned int p4[3];
    unsigned int as1;
    unsigned int p5[11];
    unsigned int sadr;
} sceDmaChan;

typedef struct {
    unsigned char sts;
    unsigned char std;
    unsigned char mfd;
    unsigned char rcycle;
    unsigned short express;
    unsigned short notify;
    unsigned short sqwc;
    unsigned short tqwc;
    void *rbadr;
    unsigned int rbmsk;
} sceDmaEnv;

/* Stops every channel and clears the controller's environment; `enable` 1 turns the controller back
 * on. Returns whether it was on. */
int sceDmaReset(int enable);

/* A channel's register block; the transfers below take it as sceDmaGetChan returns it. */
sceDmaChan *sceDmaGetChan(unsigned int id);
void sceDmaSendN(sceDmaChan *d, void *addr, int qwc);
void sceDmaRecvN(sceDmaChan *d, void *addr, int qwc);
int sceDmaSync(sceDmaChan *d, int mode, int timeout);

#ifdef __cplusplus
}
#endif

#endif
