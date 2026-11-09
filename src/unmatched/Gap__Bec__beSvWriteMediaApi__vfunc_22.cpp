/* Memory-card write state machine, polled once per frame by the save-data pipeline. _phase (_st0)
 * selects the phase and _step (_st1) the step inside it. Every phase runs three steps: 0 clears
 * the retry counter, 1 issues one asynchronous memory-card request and raises its in-flight flag,
 * 2 polls the flag (returning 0 while it is set) and reads the result code. A failed request is
 * retried up to three times, then the machine ends with _isEnd = 1 and _result = 3 for the card-
 * unusable codes (-2, -4, -5, ...) or 12 for anything else. Phases: 0 opens the save directory, 1
 * resets the image pass, 2 selects the image offset for the pass, 3 writes the save buffer and
 * flushes it, 4 commits and closes (_result = 2, saved). Returns 1 when already finished, 0 while
 * a request is pending, else _isEnd. getPhase and getStep are const because retail reloads the fields at
 * those uses; the retry test goes through a local because retail does not fold the comparison into
 * the branch. */
struct SvSaveWork;

typedef struct SvCardContext {
    char pad0[0x10];
    int dataSize;            /* +0x10 */
    char pad14[4];
    int volumeNumber;        /* +0x18 */
    char pad1c[0xa8];
    int imageOffsets[2];     /* +0xc4 */
} SvCardContext;

typedef struct SvSaveWork {
    char pad0[8];
    int buffer;              /* +8 */
} SvSaveWork;

/* beSvWriteMediaApi plus the two members the registered metadata does not list (+60 retry count,
 * +72 image pass). */
typedef struct beSvWriteMediaApiRun {
    int _vtable;
    unsigned int _refCount;
    int _dummyCount;
    int _orderType;
    unsigned char _isConAllChk;
    char _pad17[3];
    int _connect;
    int _result;
    unsigned char _isEnd;
    char _pad29[3];
    int _phase;             /* +32 (_st0) */
    int _step;              /* +36 (_st1) */
    int getPhase() const { return _phase; }
    int getStep() const { return _step; }
    int _st2;
    int _st3;
    int _imageWork;
    int _mountWork;
    int _iconWork;
    int _retryCount;         /* +60 */
    int _nowGamedata;
    SvSaveWork *_saveWork;   /* +68 */
    int _imagePass;          /* +72 */
} beSvWriteMediaApiRun;

typedef struct SvCardSlot { int port; int slot; } SvCardSlot;

#define SV_NEXT_STEP(self)  ((self)->_step = (self)->getStep() + 1, (self)->_st3 = 0, (self)->_st2 = 0)
#define SV_FIRST_STEP(self) ((self)->_st3 = 0, (self)->_st2 = 0, (self)->_step = 0)
#define SV_RETRY_STEP(self) ((self)->_step = 1, (self)->_st3 = 0, (self)->_st2 = 0)
extern "C" {
extern int sprintf(char *, const char *, ...);
extern int FUN_001198a8(int, int, char *, int);
extern int FUN_00119a08(int);
extern int FUN_00119ac8(int, int, int);
extern int FUN_00119d58(int, int, int);
extern int FUN_0011a6f0(int);
extern void FUN_003a9990(struct SvSaveWork *);
extern unsigned char GPR_00554e60;
extern unsigned char GPR_00554e64;
extern SvCardContext *DAT_0058a600[4];
extern SvCardSlot DAT_004c91b0[];
extern char DAT_00510310[];       /* "/%s/%s" */
extern int DAT_0058a808[4];
extern int DAT_0058a838[4];
extern int DAT_0058a83c[4];
extern int DAT_0058a840[4];
extern int DAT_0058a848[4];
extern int DAT_0058a858[4];
extern int DAT_0058a898[4];
extern int DAT_0058a89c[4];
extern int DAT_0058a8a0[4];
extern int DAT_0058a8a8[4];
extern int DAT_0058a8b8[4];
int Gap__Bec__beSvWriteMediaApi__vfunc_22(beSvWriteMediaApiRun *self);
}
int Gap__Bec__beSvWriteMediaApi__vfunc_22(beSvWriteMediaApiRun *self)
{
    char path[256];
    int ok;
    int res;
    SvCardContext *ctx;

    if (self->_isEnd != 0) {
        return 1;
    }
    if (GPR_00554e64 == 1) {
        return 0;
    }
    ctx = DAT_0058a600[0];
    switch (self->getPhase()) {
    case 0:
        switch (self->_step) {
        case 0:
            self->_retryCount = 0;
            SV_NEXT_STEP(self);
            break;
        case 1:
            sprintf(path, DAT_00510310, ctx->volumeNumber, ctx->volumeNumber);
            if (FUN_001198a8(DAT_004c91b0[self->_connect].port, DAT_004c91b0[self->_connect].slot, path, 3) >= 0) {
                DAT_0058a838[0] = 1;
                SV_NEXT_STEP(self);
            }
            break;
        case 2:
            if (DAT_0058a838[0] == 1) {
                return 0;
            }
            res = DAT_0058a898[0];
            if (res >= 0) {
                DAT_0058a808[0] = res;
                self->_phase = self->_phase + 1;
                SV_FIRST_STEP(self);
            } else {
                self->_retryCount = self->_retryCount + 1;
                ok = self->_retryCount < 3; if (ok == 1) {
                    SV_RETRY_STEP(self);
                } else {
                    switch (res) {
                    case -2:
                    case -3:
                    case -4:
                    case -5:
                    case -7:
                        self->_result = 3;
                        self->_isEnd = 1;
                        break;
                    default:
                        self->_result = 12;
                        self->_isEnd = 1;
                        break;
                    }
                }
            }
            break;
        }
        break;
    case 1:
        self->_imagePass = 0;
        self->_phase = self->_phase + 1;
        SV_FIRST_STEP(self);
        /* fall through */
    case 2:
        switch (self->_step) {
        case 0:
            self->_retryCount = 0;
            SV_NEXT_STEP(self);
            break;
        case 1:
            if (FUN_00119ac8(DAT_0058a808[0], ctx->imageOffsets[self->_imagePass], 0) >= 0) {
                DAT_0058a840[0] = 1;
                SV_NEXT_STEP(self);
            }
            break;
        case 2:
            if (DAT_0058a840[0] == 1) {
                return 0;
            }
            res = DAT_0058a8a0[0];
            if (res >= 0) {
                self->_phase = self->_phase + 1;
                SV_FIRST_STEP(self);
            } else {
                self->_retryCount = self->_retryCount + 1;
                ok = self->_retryCount < 3; if (ok == 1) {
                    SV_RETRY_STEP(self);
                } else {
                    switch (res) {
                    case -2:
                    case -4:
                    case -5:
                        self->_result = 3;
                        self->_isEnd = 1;
                        break;
                    default:
                        self->_result = 12;
                        self->_isEnd = 1;
                        break;
                    }
                }
            }
            break;
        }
        break;
    case 3:
        switch (self->_step) {
        case 0:
            self->_retryCount = 0;
            SV_NEXT_STEP(self);
            break;
        case 1:
            if (FUN_00119d58(DAT_0058a808[0], self->_saveWork->buffer, ctx->dataSize) >= 0) {
                DAT_0058a848[0] = 1;
                SV_NEXT_STEP(self);
            }
            break;
        case 2:
            if (DAT_0058a848[0] == 1) {
                return 0;
            }
            res = DAT_0058a8a8[0];
            if (res >= 0) {
                SV_NEXT_STEP(self);
            } else {
                self->_retryCount = self->_retryCount + 1;
                ok = self->_retryCount < 3; if (ok == 1) {
                    SV_RETRY_STEP(self);
                } else {
                    switch (res) {
                    case -2:
                    case -4:
                    case -5:
                    case -8:
                        self->_result = 3;
                        self->_isEnd = 1;
                        break;
                    default:
                        self->_result = 12;
                        self->_isEnd = 1;
                        break;
                    }
                }
            }
            break;
        case 3:
            self->_retryCount = 0;
            SV_NEXT_STEP(self);
            break;
        case 4:
            if (FUN_0011a6f0(DAT_0058a808[0]) >= 0) {
                DAT_0058a858[0] = 1;
                SV_NEXT_STEP(self);
            }
            break;
        case 5:
            if (DAT_0058a858[0] == 1) {
                return 0;
            }
            res = DAT_0058a8b8[0];
            if (res >= 0) {
                if (self->_imagePass == 0) {
                    self->_imagePass = 1;
                    self->_phase = self->_phase - 1;
                    SV_FIRST_STEP(self);
                } else {
                    self->_phase = self->_phase + 1;
                    SV_FIRST_STEP(self);
                }
            } else {
                self->_retryCount = self->_retryCount + 1;
                ok = self->_retryCount < 3; if (ok == 1) {
                    SV_RETRY_STEP(self);
                } else switch (res) {
 case -2:
     self->_result = 3;
     self->_isEnd = 1;
     break;
 default:
     self->_result = 12;
     self->_isEnd = 1;
     break;
 }
            }
            break;
        }
        break;
    case 4:
        switch (self->_step) {
        case 0:
            self->_retryCount = 0;
            SV_NEXT_STEP(self);
            break;
        case 1:
            if (FUN_00119a08(DAT_0058a808[0]) >= 0) {
                DAT_0058a83c[0] = 1;
                SV_NEXT_STEP(self);
            }
            break;
        case 2:
            if (DAT_0058a83c[0] == 1) {
                return 0;
            }
            res = DAT_0058a89c[0];
            if (res >= 0) {
                self->_isEnd = 1;
                self->_result = 2;
                self->_phase = self->_phase + 1;
                SV_FIRST_STEP(self);
            } else {
                self->_retryCount = self->_retryCount + 1;
                ok = self->_retryCount < 3; if (ok == 1) {
                    SV_RETRY_STEP(self);
                } else {
                    switch (res) {
                    case -2:
                    case -4:
                    case -5:
                    case -8:
                        self->_result = 3;
                        self->_isEnd = 1;
                        break;
                    default:
                        self->_result = 12;
                        self->_isEnd = 1;
                        break;
                    }
                }
            }
            break;
        }
        break;
    case 5:
        break;
    }
    if (self->_isEnd != 0) {
        FUN_003a9990(self->_saveWork);
        GPR_00554e60 = 0;
    }
    return self->_isEnd;
}
