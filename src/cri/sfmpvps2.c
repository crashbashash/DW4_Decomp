#include "dw4/cri/sfdply.h"
#include "dw4/sony/libmpeg.h"
#include "dw4/support/eekernel.h"
#include <string.h>
#include "dw4/cri/mps.h"
#include "dw4/sony/libkernl.h"
#include "dw4/cri/sfd.h"
#include "dw4/cri/mpv.h"

#define D_ENABLER ((volatile unsigned int *)0x1000F520)
#define D_ENABLEW ((volatile unsigned int *)0x1000F590)
#define D3_CHCR ((volatile unsigned int *)0x1000B000)
#define D4_CHCR ((volatile unsigned int *)0x1000B400)
#define D4_MADR ((volatile unsigned int *)0x1000B410)
#define D4_QWC  ((volatile unsigned int *)0x1000B420)
#define D4_TADR ((volatile unsigned int *)0x1000B430)
#define REG(a) (*(volatile int *)(a))
#define UNCACHED(address) (((address) & 0x0FFFFFFF) | 0x20000000)
#define PHYSICAL(address) ((address) & 0x0FFFFFFF)

extern int sfmpvp_scempeg_useflag;
extern sceMpeg sfmpvp_bkup_buf;
extern int sfmpvp_mpeg_errflg;
extern char sfmpvp_mpeg_errdata[8];

extern int DeleteSema(int sema);
void sfmpvp_ConsumePsc(SfdPly *player);

int mpegError(sceMpeg *mp, sceMpegCbDataError *cbdata, SfdPly *player);
int sfmpvps2_ExecIpu(sceMpeg *mp, sceMpegCbData *cbdata, SfdPly *player);
int mpegStopDMA(sceMpeg *mp, sceMpegCbData *cbdata, SfdPly *player);
int mpegRestartDMA(int unused0, int unused1, SfdPly *player);

extern char sfmpv_seqend_codes[16];

int viBufCreate(SfdIpuStream *stream, void *base, void *address, int sectors, SfdIpuEntry *entries, int entryCount);
int viBufReset(SfdIpuStream *stream);
void scTag2(long long *tag, long long addr, long long id, long long qwc);
void viBufBeginPut(SfdIpuStream *stream, char **first, int *firstSize, char **second, int *secondSize);
int viBufAddDMA(SfdIpuStream *stream);
void viBufEndPut(SfdIpuStream *stream, int bytes);
int viBufUnput(SfdIpuStream *stream, int count);
int viBufStopDMA(SfdIpuStream *stream);
int viBufRestartDMA(SfdIpuStream *stream);
int viBufDelete(SfdIpuStream *stream);
void viBufFlush(SfdIpuStream *stream);
int sfmpvp_PutVibuf(SfdIpuStream *stream, char *src, int pos);
void sfmpvp_SaveMpvp(SfdPly *player);
void sfmpvp_RestoreMpvp(SfdPly *player);
int copy2area(char *buf, int size, char *dst, int cap, char *src, int pos, char *data, int len);

int getFIFOindex(SfdIpuStream *stream, int position) {
    if (position == ((stream->sectors * 16 + (unsigned int)stream->uncached + 16) & 0x0FFFFFFF)) {
        return 0;
    }
    return (position - (int)stream->base) / 2048;
}

void sfmpvps2_setD3_CHCR(unsigned int chcr) {
    DIntr();
    *D_ENABLEW = *D_ENABLER | 0x10000;
    *D3_CHCR = chcr;
    *D_ENABLEW = *D_ENABLER & ~0x10000;
    EIntr();
}

void setD4_CHCR(unsigned int chcr) {
    DIntr();
    *D_ENABLEW = *D_ENABLER | 0x10000;
    *D4_CHCR = chcr;
    *D_ENABLEW = *D_ENABLER & ~0x10000;
    EIntr();
}

void scTag2(long long *tag, long long addr, long long id, long long qwc) {
    *tag = (addr << 0x20) | ((unsigned long long) (id << 0x20) >> 4) | ((unsigned long long) (qwc << 0x20) >> 0x20);
}

void viBufEndPut(SfdIpuStream *stream, int bytes) {
    WaitSema(stream->sema);
    stream->restBytes += bytes;
    stream->totalBytes += bytes;
    SignalSema(stream->sema);
}

int viBufUnput(SfdIpuStream *stream, int count) {
    WaitSema(stream->sema);
    stream->restBytes -= count;
    stream->totalBytes -= count;
    if (stream->restBytes < 0) {
        for (;;) {
        }
    }
    SignalSema(stream->sema);
    return count;
}

int viBufStopDMA(SfdIpuStream *stream) {
    WaitSema(stream->sema);
    stream->active = 0;
    setD4_CHCR(5);
    stream->r28 = REG(0x1000B410);
    stream->r32 = REG(0x1000B430);
    stream->r36 = REG(0x1000B420);
    stream->r40 = REG(0x1000B400);
    while (REG(0x10002010) & 0xF0) {
    }
    sfmpvps2_setD3_CHCR(0);
    stream->r44 = REG(0x1000B010);
    stream->r48 = REG(0x1000B020);
    stream->r52 = REG(0x1000B000);
    stream->r56 = REG(0x10002020);
    stream->r60 = REG(0x10002010);
    SignalSema(stream->sema);
    return 1;
}

int viBufDelete(SfdIpuStream *stream) {
    setD4_CHCR(5);
    *D4_QWC = 0;
    *D4_MADR = 0;
    *D4_TADR = 0;
    DeleteSema(stream->sema);
    return 1;
}

void viBufFlush(SfdIpuStream *stream) {
    WaitSema(stream->sema);
    stream->restBytes = (stream->restBytes + 2051) / 2048 * 2048;
    SignalSema(stream->sema);
}

void SFD_SetSceMpeg(int enable) {
    sfmpvp_scempeg_useflag = enable;
}

int SFMPVP_IsSceMpegUsed(void *sfd) {
    SfdPly *player = sfd;
    SfdMpv *mpv = player->trn[2].hn.mpv;
    return mpv->ipu.enabled != 0;
}

void SFMPVP_Init(void) {
    if (sfmpvp_scempeg_useflag != 0) {
        sceMpegInit();
        UTY_MemsetByte(&sfmpvp_bkup_buf, 0, 0x48);
    }
}

void SFMPVP_GetViBufInf(SfdPly *player, int *bytes, int *position, int *start, int *end) {
    SfdMpv *mpv = player->trn[2].hn.mpv;
    SfdIpuStream *stream = &mpv->ipu.stream;
    *bytes = stream->bytes;
    *start = stream->headSct << 11;
    *position = (((stream->headSct + stream->queuedSct) << 11) + stream->restBytes) % stream->bytes;
    *end = (stream->queuedSct << 11) + stream->restBytes;
}

void SFMPVP_Create(void *sfd) {
    SfdPly *player = sfd;
    SfdMpv *mpv = player->trn[2].hn.mpv;
    SfdMpvCond *cond = &mpv->cond;
    SfdIpuCtl *ctl = &mpv->ipu;
    sceMpeg *mpeg = &ctl->mpeg;
    sceMpegCbDataError *error = &ctl->error;
    int size;
    int work;
    int vibuf;
    int ring;
    int tags;
    int vibufArea;

    if (sfmpvp_scempeg_useflag == 0) {
        ctl->enabled = 0;
        return;
    }
    size = cond->max_width * cond->max_height * 9 / 2 + 10240;
    if (mpv->work.w[0] == 0) {
        mpv->work.w[0] = ((int)cond->rfb_adr + 63) & ~63;
        vibufArea = (mpv->work.w[0] + size + 63) & ~63;
        mpv->work.w[1] = vibufArea;
    } else {
        mpv->work.w[0] = (mpv->work.w[0] + 63) & ~63;
        vibufArea = (mpv->work.w[1] + 63) & ~63;
        mpv->work.w[1] = vibufArea;
    }
    vibuf = mpv->work.w[1];
    work = mpv->work.w[0];
    ring = (vibuf + 0x80000 + 63) & ~63;
    tags = (ring + 0x1010 + 63) & ~63;
    if (SFPLY_GetResetFlg() != 1) {
        sceMpegCreate(mpeg, (unsigned char *)work, size);
        sceMpegAddCallback(mpeg, sceMpegCbError, (sceMpegCallback)mpegError, player);
        sceMpegAddCallback(mpeg, sceMpegCbNodata, (sceMpegCallback)sfmpvps2_ExecIpu, player);
        sceMpegAddCallback(mpeg, sceMpegCbStopDMA, (sceMpegCallback)mpegStopDMA, player);
        sceMpegAddCallback(mpeg, sceMpegCbRestartDMA, (sceMpegCallback)mpegRestartDMA, player);
    } else {
        sfmpvp_RestoreMpvp(player);
    }
    viBufCreate(&ctl->stream, (void *)vibuf, (void *)ring, 256, (SfdIpuEntry *)tags, 512);
    viBufAddDMA(&ctl->stream);
    viBufStopDMA(&ctl->stream);
    ctl->enabled = 1;
    ctl->tail0 = 0;
    ctl->tail1 = 0;
    ctl->tail2 = 0;
    error->type = (sceMpegCbType)-1;
    error->errMessage = 0;
    ctl->pscNext = 0;
    ctl->pscFound = 0;
    ctl->pscCount = 0;
    ctl->endRequest = 0;
    ctl->endSent = 0;
    ctl->stopped = 0;
    ctl->value = 0;
}

char *SFD_GetSceErrMessage(void *sfd) {
    SfdPly *player = sfd;
    SfdMpv *mpv = player->trn[2].hn.mpv;
    return mpv->ipu.error.errMessage;
}

int mpegError(sceMpeg *mp, sceMpegCbDataError *cbdata, SfdPly *player) {
    SfdMpv *mpv;
    sfmpvp_mpeg_errflg = 1;
    __builtin_memcpy(sfmpvp_mpeg_errdata, cbdata, 8);
    mpv = player->trn[2].hn.mpv;
    __builtin_memcpy(&mpv->ipu.error, cbdata, 8);
    sfd_ReportError(player, 0xFF000F40);
    return 1;
}

int sfmpvp_PutVibuf(SfdIpuStream *stream, char *src, int pos) {
    char *first;
    int firstSize;
    char *second;
    int secondSize;
    int result;
    viBufBeginPut(stream, &first, &firstSize, &second, &secondSize);
    result = copy2area((char *)UNCACHED((unsigned int)first), firstSize, (char *)UNCACHED((unsigned int)second), secondSize, src, pos, 0, 0);
    viBufEndPut(stream, result);
    return result;
}

int sfmpvps2_ExecIpu(sceMpeg *mp, sceMpegCbData *cbdata, SfdPly *player) {
    SfdMpv *mpv = player->trn[2].hn.mpv;
    SfdIpuCtl *ctl = &mpv->ipu;
    SfdIpuStream *stream = &mpv->ipu.stream;
    if (ctl->endSent == 1) {
        sceMpegGetPictureAbort(&mpv->ipu.mpeg);
        return 1;
    }
    viBufAddDMA(stream);
    if (ctl->endRequest != 0 && stream->queuedSct == 0) {
        ctl->endSent = 1;
        sfmpvp_PutVibuf(stream, sfmpv_seqend_codes, 16);
        stream->restBytes = stream->bytes;
        viBufAddDMA(stream);
    }
    return 1;
}

int mpegStopDMA(sceMpeg *mp, sceMpegCbData *cbdata, SfdPly *player) {
    SfdMpv *mpv = player->trn[2].hn.mpv;
    viBufStopDMA(&mpv->ipu.stream);
    return 1;
}

int mpegRestartDMA(int unused0, int unused1, SfdPly *player) {
    SfdMpv *mpv = player->trn[2].hn.mpv;
    viBufRestartDMA(&mpv->ipu.stream);
    return 1;
}

void SFMPVP_Destroy(void *sfd)
{
    SfdPly *player = sfd;
    SfdMpv *mpv;
    if (SFMPVP_IsSceMpegUsed(player)) {
        mpv = player->trn[2].hn.mpv;
        viBufDelete(&mpv->ipu.stream);
        if (SFPLY_GetResetFlg() != 1) {
            sceMpegDelete(&mpv->ipu.mpeg);
        } else {
            sceMpegReset(&mpv->ipu.mpeg);
            sfmpvp_SaveMpvp(player);
        }
    }
}

void sfmpvp_SaveMpvp(SfdPly *player) {
    SfdMpv *mpv = player->trn[2].hn.mpv;
    UTY_MemcpyByte(&sfmpvp_bkup_buf, &mpv->ipu.mpeg, 0x48);
}

void sfmpvp_RestoreMpvp(SfdPly *player) {
    SfdMpv *mpv = player->trn[2].hn.mpv;
    UTY_MemcpyByte(&mpv->ipu.mpeg, &sfmpvp_bkup_buf, 0x48);
}

int SFMPVP_Put(void *sfd, char *src, int pos) {
    SfdPly *player = sfd;
    SfdMpv *mpv;
    if (SFMPVP_IsSceMpegUsed(player) == 0) {
        return pos;
    }
    mpv = player->trn[2].hn.mpv;
    return sfmpvp_PutVibuf(&mpv->ipu.stream, src, pos);
}

int SFMPVP_Unput(void *sfd, int count) {
    SfdPly *player = sfd;
    SfdMpv *mpv;
    if (SFMPVP_IsSceMpegUsed(player) == 0) {
        return count;
    }
    mpv = player->trn[2].hn.mpv;
    return viBufUnput(&mpv->ipu.stream, count);
}

void sfmpvps2_StopIpu(void *sfd, int value) {
    SfdPly *player = sfd;
    SfdMpv *mpv = player->trn[2].hn.mpv;
    SfdIpuCtl *ctl = &mpv->ipu;
    if (ctl->stopped != 1) {
        viBufFlush(&mpv->ipu.stream);
        ctl->stopped = 1;
        ctl->value = value;
    }
}

int copy2area(char *buf, int size, char *dst, int cap, char *src, int pos, char *data, int len) {
    int end = pos + len;
    int r = 0;
    if (size + cap >= end) {
        if (pos >= size) {
            memcpy(buf, src, size);
            memcpy(dst, src + size, pos - size);
            memcpy(dst + pos - size, data, len);
        } else {
            int room = size - pos;
            if (len >= room) {
                memcpy(buf, src, pos);
                memcpy(buf + pos, data, room);
                memcpy(dst, data + size - pos, len - room);
            } else {
                memcpy(buf, src, pos);
                memcpy(buf + pos, data, len);
            }
        }
        r = end;
    }
    return r;
}

int SFMPVP_DecodeFrmSj(MpvHn *hn, SfdSj *sj, SfdFrmPara *para, SfdPly *player) {
    SfdMpv *mpv;
    SfdIpuStream *stream;
    SfdIpuCtl *ipu;
    SfdMpvCond *cond;
    int result;
    int mbs;
    int mode;

    if (SFMPVP_IsSceMpegUsed(player) == 0) {
        return MPV_DecPicSj(hn, sj, para);
    }
    mpv = player->trn[2].hn.mpv;
    result = MPV_SkipFrmSj(hn, sj);
    stream = &mpv->ipu.stream;
    ipu = &mpv->ipu;
    cond = &mpv->cond;
    viBufRestartDMA(stream);
    viBufAddDMA(stream);
    mode = player->cre.bufFmt;
    ipu->endRequest = 1;
    mbs = (cond->max_width / 16) * (cond->max_height / 16);
    if (mode == 2) {
        sceMpegGetPicture(&mpv->ipu.mpeg, (unsigned int)para->dst, mbs);
    } else {
        sceMpegGetPictureRAW8(&mpv->ipu.mpeg, (unsigned int)para->dst, mbs);
    }
    ipu->endRequest = 0;
    viBufStopDMA(&ipu->stream);
    sfmpvp_ConsumePsc(player);
    return ipu->endSent ? -3 : result;
}

int SFMPVP_GetFrameCount(void *sfd) {
    SfdPly *player = sfd;
    SfdMpv *mpv = player->trn[2].hn.mpv;
    return mpv->ipu.mpeg.frameCount;
}

void SFMPVP_SearchPsc(void *sfd, unsigned char *data, int size) {
    SfdPly *player = sfd;
    SfdMpv *mpv = player->trn[2].hn.mpv;
    SfdIpuCtl *ipu = &mpv->ipu;
    unsigned char win[6];
    unsigned char *hit;
    int found = 0;
    int i = 0;
    int skip;
    ipu->pscCount += ipu->pscNext;
    ipu->pscNext = ipu->pscFound;
    ipu->pscFound = 0;
    win[0] = ipu->tail0;
    win[1] = ipu->tail1;
    win[2] = ipu->tail2;
    win[3] = data[0];
    win[4] = data[1];
    win[5] = data[2];
    while (i < (size < 4 ? size : 3)) {
        if (win[i] == 0 && win[i + 1] == 0 && win[i + 2] == 1) {
            if (win[i + 3] == 0) {
                ipu->pscFound++;
                break;
            }
            if (win[i + 3] == 0xB7) {
                found = 1;
                break;
            }
        }
        i++;
    }
    if (size < 3) {
        ipu->tail0 = win[size];
        ipu->tail1 = win[size + 1];
        ipu->tail2 = win[size + 2];
    } else {
        ipu->tail0 = data[size - 3];
        ipu->tail1 = data[size - 2];
        ipu->tail2 = data[size - 1];
    }
    while (size >= 4) {
        hit = MPV_SearchDelim(data, size, 132);
        if (hit == 0) {
            break;
        }
        if (MPV_CheckDelim(hit) & 4) {
            ipu->pscFound++;
        } else {
            found = 1;
        }
        hit += 4;
        skip = hit - data;
        data = hit;
        size -= skip;
    }
    if (found == 1 && SFCON_IsEndcodeSkip(player) == 0 && SFCON_IsVideoEndcodeSkip(player) == 0) {
        sfmpvps2_StopIpu(player, 1);
    }
}

void sfmpvp_ConsumePsc(SfdPly *player) {
    SfdMpv *mpv = player->trn[2].hn.mpv;
    SfdIpuCtl *ctl = &mpv->ipu;
    ctl->pscCount--;
}

int SFMPVP_IsPscEnough(void *sfd) {
    SfdPly *player = sfd;
    SfdMpv *mpv;
    SfdIpuCtl *ctl;
    if (SFMPVP_IsSceMpegUsed(player) == 0) {
        return 1;
    }
    mpv = player->trn[2].hn.mpv;
    ctl = &mpv->ipu;
    if (ctl->value == 1) {
        return 1;
    }
    if (ctl->pscCount < 3) return 0;
    return 1;
}

sceMpeg *SFMPVP_GetSceMpegHn(SfdPly *player) {
    SfdMpv *mpv = player->trn[2].hn.mpv;
    return &mpv->ipu.mpeg;
}

int SFMPVP_GetSizeSceMpegHn(void) {
    return 72;
}
int viBufCreate(SfdIpuStream *stream, void *base, void *address, int sectors, SfdIpuEntry *entries, int entryCount) {
    struct SemaParam param;

    stream->base = base;
    stream->uncached = (SfdDmaTag *)UNCACHED((unsigned int)address);
    stream->sectors = sectors;
    stream->bytes = sectors * 2048;
    stream->entries = entries;
    stream->entryCount = entryCount;
    param.initCount = 1;
    param.maxCount = 1;
    stream->sema = CreateSema(&param);
    viBufReset(stream);
    stream->totalBytes = 0;
    return 1;
}
int viBufReset(SfdIpuStream *stream) {
    int i;

    stream->headSct = 0;
    stream->queuedSct = 0;
    stream->restBytes = 0;
    stream->active = 1;
    stream->tsCount = 0;
    stream->tsWrite = 0;
    for (i = 0; i < stream->entryCount; i++) {
        stream->entries[i].pts = -1;
        stream->entries[i].dts = -1;
        stream->entries[i].pos = 0;
        stream->entries[i].len = 0;
    }
    for (i = 0; i < stream->sectors; i++) {
        scTag2((long long *)(stream->uncached + i), PHYSICAL(i * 2048 + (unsigned int)stream->base), 3, 128);
    }
    scTag2((long long *)(stream->uncached + i), PHYSICAL((unsigned int)stream->uncached), 2, 0);
    *D4_QWC = 0;
    *D4_MADR = PHYSICAL((unsigned int)stream->base);
    *D4_TADR = PHYSICAL((unsigned int)stream->uncached);
    setD4_CHCR(5);
    return 1;
}
void viBufBeginPut(SfdIpuStream *stream, char **first, int *firstSize, char **second, int *secondSize) {
    int es;
    int en;
    int fs;
    int fn;

    WaitSema(stream->sema);
    fs = (stream->headSct + stream->queuedSct) * 2048;
    fn = (stream->sectors - 2 - stream->queuedSct) * 2048;
    es = (fs + stream->restBytes) % stream->bytes;
    en = fn - stream->restBytes;
    if (stream->bytes - es >= en) {
        *first = (char *)stream->base + es;
        *firstSize = en;
        *second = 0;
        *secondSize = 0;
    } else {
        *first = (char *)stream->base + es;
        *firstSize = stream->bytes - es;
        *second = (char *)stream->base;
        *secondSize = en - (stream->bytes - es);
    }
    SignalSema(stream->sema);
}
int viBufAddDMA(SfdIpuStream *stream) {
    int i;
    int index;
    int id;
    int last;
    unsigned int d4chcr;
    int isNewData = 0;
    int consume;
    int readStart;
    int readN;

    WaitSema(stream->sema);
    if (!stream->active) {
        SignalSema(stream->sema);
        return 0;
    }
    setD4_CHCR(5);
    d4chcr = *D4_CHCR;
    index = getFIFOindex(stream, *D4_MADR);
    consume = (index + stream->sectors - stream->headSct) % stream->sectors;
    stream->headSct = (stream->headSct + consume) % stream->sectors;
    stream->queuedSct -= consume;
    readStart = (stream->headSct + stream->queuedSct) % stream->sectors;
    readN = stream->restBytes / 2048;
    stream->restBytes %= 2048;
    if (readN > 0) {
        last = (stream->headSct + stream->queuedSct - 1 + stream->sectors) % stream->sectors;
        scTag2((long long *)(stream->uncached + last), (int)((char *)stream->base + 2048 * last), 3, 128);
        isNewData = 1;
    }
    index = readStart;
    for (i = 0; i < readN; i++) {
        id = (i == readN - 1) ? 0 : 3;
        scTag2((long long *)(stream->uncached + index), (int)((char *)stream->base + 2048 * index), id, 128);
        index = (index + 1) % stream->sectors;
    }
    stream->queuedSct += readN;
    if (stream->queuedSct) {
        if (isNewData) {
            d4chcr = (d4chcr & 0x0FFFFFFF) | (3 << 28);
        }
        setD4_CHCR(d4chcr | 0x100);
    }
    SignalSema(stream->sema);
    return 1;
}
int viBufRestartDMA(SfdIpuStream *stream) {
    int bp;
    int fp;
    int ifc;
    unsigned int madr;
    unsigned int qwc;
    unsigned int tadr;
    unsigned int chcr;
    int index;
    int indexNext;
    int id;

    WaitSema(stream->sema);
    bp = stream->r56 & 0x7F;
    fp = (stream->r56 >> 16) & 0x3;
    ifc = (stream->r56 >> 8) & 0xF;
    madr = stream->r28 - ((fp + ifc) << 4);
    qwc = stream->r36 + (fp + ifc);
    tadr = stream->r32;
    chcr = stream->r40 | 0x100;
    if (madr < (unsigned int)stream->base) {
        qwc = ((unsigned int)stream->base - madr) >> 4;
        madr += (unsigned int)(stream->sectors * 2048);
        tadr = PHYSICAL((unsigned int)stream->uncached);
        id = (stream->r28 == (unsigned int)stream->base
              || stream->r28 == (unsigned int)stream->base + 2048 * stream->sectors) ? 0 : 3;
        chcr = (stream->r40 & 0x0FFFFFFF) | (id << 28) | 0x100;
        if (!(0 <= (0 + stream->sectors - stream->headSct) % stream->sectors
              && (0 + stream->sectors - stream->headSct) % stream->sectors < stream->queuedSct)) {
            stream->headSct = stream->sectors - 1;
            stream->queuedSct++;
        }
    } else if ((index = getFIFOindex(stream, stream->r28)) != (indexNext = getFIFOindex(stream, madr))) {
        tadr = PHYSICAL(index * 16 + (unsigned int)stream->uncached);
        qwc = ((unsigned int)stream->base + 2048 * index - madr) >> 4;
        id = ((unsigned int)stream->base + (stream->r28 - (unsigned int)stream->base) % (2048 * stream->sectors)
              == (unsigned int)stream->base + 2048 * ((stream->headSct + stream->queuedSct) % stream->sectors)) ? 0 : 3;
        chcr = (stream->r40 & 0x0FFFFFFF) | (id << 28) | 0x100;
        if (!(0 <= (indexNext + stream->sectors - stream->headSct) % stream->sectors
              && (indexNext + stream->sectors - stream->headSct) % stream->sectors < stream->queuedSct)) {
            stream->headSct = indexNext;
            stream->queuedSct++;
        }
    }
    if (stream->r44 != 0 && stream->r48 != 0) {
        REG(0x1000B010) = stream->r44;
        REG(0x1000B020) = stream->r48;
        sfmpvps2_setD3_CHCR(stream->r52 | 0x100);
    }
    while (REG(0x10002010) < 0) {
    }
    REG(0x10002000) = bp;
    while (REG(0x10002010) < 0) {
    }
    *D4_MADR = madr;
    *D4_TADR = tadr;
    *D4_QWC = qwc;
    if (stream->queuedSct != 0) {
        setD4_CHCR(chcr);
    }
    REG(0x10002010) = stream->r60;
    stream->active = 1;
    SignalSema(stream->sema);
    return 1;
}
