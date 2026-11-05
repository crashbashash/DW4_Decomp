/* 0x002a9628 — FUN_002a9628 (88 bytes). Stops the IPU_TO DMA channel, clears its MADR/QWC/TADR and deletes the stream semaphore. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int DeleteSema();
void FUN_002a8c08();

/* EE DMAC channel 4 (IPU_TO) registers (addresses as in ps2sdk reference: common/include/ee_regs.h). */
#define D4_MADR ((volatile unsigned int *)0x1000B410)
#define D4_QWC  ((volatile unsigned int *)0x1000B420)
#define D4_TADR ((volatile unsigned int *)0x1000B430)

/* IPU stream buffer descriptor guarded by a semaphore at +64. */
struct Stream {
    int f0;
    char *uncached;                       /* +4: buffer address in the uncached segment */
    int sectors;                          /* +8 */
    int pad12;
    int pad16;
    int f20;                              /* +20: bytes buffered */
    int bytes;                            /* +24: sectors * 2048 */
    char pad28[64 - 28];
    int sema;                             /* +64 */
    int pad68;
    long f72;                             /* +72 */
    int f80;
    int f84;
};

/* Stops the IPU_TO channel (CHCR 5 via FUN_002a8c08), clears its address/count registers and deletes the stream semaphore. */
int FUN_002a9628(struct Stream *stream) {
    FUN_002a8c08(5);
    *D4_QWC = 0;
    *D4_MADR = 0;
    *D4_TADR = 0;
    DeleteSema(stream->sema);
    return 1;
}
