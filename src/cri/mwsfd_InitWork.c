/* Clears the MWSFD work area (the header and the 8 player handles, 5676 bytes) and takes its init
 * parameters from iprm, or the defaults (59.94 Hz, display cycle 1, latency 1, no decode server)
 * without them. */
typedef struct {
    float vhz;          /* +0 */
    int dispCycle;      /* +4 */
    int dispLatency;    /* +8 */
    void *decSvr;       /* +12 */
} MwsfdInitPrm;

typedef struct {
    int pad0;
    MwsfdInitPrm prm;   /* +4 */
    char pad20[36];
    int picUsrEnable;   /* +56: picture user data is handled */
    int waitSvrOnStart; /* +60 */
    char pad64[24];
    int svrLock;        /* +88 */
    int execLock;       /* +92 */
} MwsfdWork;

MwsfdWork *mwsfd_GetWork(void);
void *memset(void *dst, int c, unsigned int n);
void mwsfd_SetSvrLock(int value);

void mwsfd_InitWork(MwsfdInitPrm *iprm) {
    MwsfdWork *work = mwsfd_GetWork();
    MwsfdInitPrm *prm;

    memset(work, 0, 5676);
    mwsfd_SetSvrLock(0);
    work->execLock = 0;
    prm = &work->prm;
    if (iprm != 0) {
        prm->vhz = iprm->vhz;
        prm->dispCycle = iprm->dispCycle;
        prm->dispLatency = iprm->dispLatency;
        prm->decSvr = iprm->decSvr;
    } else {
        prm->vhz = 59.94f;
        prm->dispCycle = 1;
        prm->dispLatency = 1;
        prm->decSvr = 0;
    }
    work->picUsrEnable = 1;
    work->waitSvrOnStart = 1;
}
