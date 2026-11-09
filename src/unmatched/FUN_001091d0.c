typedef int (*MpegCallback)(void *mp, void *cbdata, void *data);
typedef struct {
    MpegCallback func;
    void *data;
    void *gp;
} MpegCallbackSlot;
typedef struct {
    int pad[3];
    MpegCallbackSlot slots[1];
} MpegInternal;
typedef struct {
    int pad[16];
    MpegInternal *sys;
} MpegStream;
static inline void *currentGp(void) {
    void *gp;
    __asm__ volatile("move %0,$28" : "=r"(gp));
    return gp;
}
MpegCallback FUN_001091d0(MpegStream *mp, int type, MpegCallback func, void *data) {
    MpegInternal *sys = mp->sys;
    MpegCallback old = sys->slots[type].func;
    sys->slots[type].func = func;
    sys->slots[type].data = data;
    sys->slots[type].gp = currentGp();
    return old;
}
