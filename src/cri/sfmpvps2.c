#include "dw4/cri/sfmpv.h"
#include "dw4/eekernel.h"

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
extern SfdMpegCtx sfmpvp_bkup_buf;
extern int DAT_00585678;
extern char DAT_00585680[8];

extern int WaitSema(int sema);
extern int SignalSema(int sema);
extern int DeleteSema(int sema);
extern int sceMpegInit(void);
extern void *memcpy(void *dst, const void *src, unsigned int size);
void sceMpegDelete(SfdMpegCtx *mpeg);
void sceMpegReset(void);
void DIntr(void);
void EIntr(void);
void UTY_MemcpyByte(void *dst, void *src, int size);
void UTY_MemsetByte(void *dst, int value, int size);
int sfd_ReportError();
int SFPLY_GetResetFlg(void);
typedef struct SfdPicOut {
    char pad0[32];
    int buf;
} SfdPicOut;
int MPV_DecPicSj(int a, int b, SfdPicOut *out, SfdPlayer *player);
int MPV_SkipFrmSj(int a, int b, SfdPicOut *out, SfdPlayer *player);
int sceMpegGetPicture(SfdMpegCtx *mpeg, int buf, int mbs);
int sceMpegGetPictureRAW8(SfdMpegCtx *mpeg, int buf, int mbs);
void sfmpvp_ConsumePsc(SfdPlayer *player);
int SFMPVP_DecodeFrmSj(int a, int b, SfdPicOut *out, SfdPlayer *player);
unsigned char *MPV_SearchDelim(unsigned char *data, int size, int code);
int MPV_CheckDelim(unsigned char *code);
int FUN_0029ed48(SfdPlayer *player);
int FUN_0029edb0(SfdPlayer *player);

void FUN_002aa050(SfdPlayer *player, unsigned char *data, int size);
int sceMpegCreate(SfdMpegCtx *mpeg, int buf, int size);
int sceMpegAddCallback(SfdMpegCtx *mpeg, int type, void *callback, void *arg);
void SFMPVP_Create(SfdPlayer *player);
int mpegError(void *unused, void *record, SfdPlayer *player);
int sfmpvps2_ExecIpu(int unused0, int unused1, SfdPlayer *player);
int mpegStopDMA(int unused0, int unused1, SfdPlayer *player);
int mpegRestartDMA(int unused0, int unused1, SfdPlayer *player);
void sceMpegGetPictureAbort(SfdMpegCtx *mpeg);

extern char sfmpv_seqend_codes[16];

int viBufCreate(SfdIpuStream *stream, int base, unsigned int address, int sectors, SfdIpuEntry *entries, int entryCount);
int viBufReset(SfdIpuStream *stream);
void scTag2(long long *arg0, long long arg1, long long arg2, long long arg3);
void viBufBeginPut(SfdIpuStream *stream, char **first, int *firstSize, char **second, int *secondSize);
int viBufAddDMA(SfdIpuStream *stream);
void viBufEndPut(SfdIpuStream *stream, int bytes);
int viBufUnput(SfdIpuStream *stream, int count);
int viBufStopDMA(SfdIpuStream *stream);
int viBufRestartDMA(SfdIpuStream *stream);
int viBufDelete(SfdIpuStream *stream);
void viBufFlush(SfdIpuStream *stream);
int SFMPVP_IsSceMpegUsed(SfdPlayer *player);
int sfmpvp_PutVibuf(SfdIpuStream *stream, char *src, int pos);
void sfmpvp_SaveMpvp(SfdPlayer *player);
int copy2area(char *buf, int size, char *dst, int cap, char *src, int pos, char *data, int len);

int getFIFOindex(SfdIpuStream *stream, int position) {
    if (position == ((stream->sectors * 16 + stream->uncached + 16) & 0x0FFFFFFF)) {
        return 0;
    }
    return (position - stream->base) / 2048;
}

void FUN_002a8ba0(unsigned int chcr) {
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

void scTag2(long long *arg0, long long arg1, long long arg2, long long arg3) {
    *arg0 = (arg1 << 0x20) | ((unsigned long long) (arg2 << 0x20) >> 4) | ((unsigned long long) (arg3 << 0x20) >> 0x20);
}

void viBufEndPut(SfdIpuStream *stream, int bytes) {
    WaitSema(stream->sema);
    stream->restBytes += bytes;
    stream->f72 += bytes;
    SignalSema(stream->sema);
}

int viBufUnput(SfdIpuStream *stream, int count) {
    WaitSema(stream->sema);
    stream->restBytes -= count;
    stream->f72 -= count;
    if (stream->restBytes < 0) {
        for (;;) {
        }
    }
    SignalSema(stream->sema);
    return count;
}

int viBufStopDMA(SfdIpuStream *stream) {
    WaitSema(stream->sema);
    stream->f68 = 0;
    setD4_CHCR(5);
    stream->r28 = REG(0x1000B410);
    stream->r32 = REG(0x1000B430);
    stream->r36 = REG(0x1000B420);
    stream->r40 = REG(0x1000B400);
    while (REG(0x10002010) & 0xF0) {
    }
    FUN_002a8ba0(0);
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

int SFMPVP_IsSceMpegUsed(SfdPlayer *player) {
    SfdMpv *mpv = player->streams.mpv;
    return mpv->ipu.enabled != 0;
}

void SFMPVP_Init(void) {
    if (sfmpvp_scempeg_useflag != 0) {
        sceMpegInit();
        UTY_MemsetByte(&sfmpvp_bkup_buf, 0, 0x48);
    }
}

void SFMPVP_GetViBufInf(SfdPlayer *player, int *bytes, int *position, int *start, int *end) {
    SfdMpv *mpv = player->streams.mpv;
    SfdIpuStream *stream = &mpv->stream;
    *bytes = stream->bytes;
    *start = stream->f12 << 11;
    *position = (((stream->f12 + stream->queuedSct) << 11) + stream->restBytes) % stream->bytes;
    *end = (stream->queuedSct << 11) + stream->restBytes;
}

int SFD_GetSceErrMessage(SfdPlayer *player) {
    SfdMpv *mpv = player->streams.mpv;
    return mpv->event.f4;
}

int mpegError(void *unused, void *record, SfdPlayer *player) {
    SfdMpv *mpv;
    DAT_00585678 = 1;
    __builtin_memcpy(DAT_00585680, record, 8);
    mpv = player->streams.mpv;
    __builtin_memcpy(&mpv->event, record, 8);
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

int sfmpvps2_ExecIpu(int unused0, int unused1, SfdPlayer *player) {
    SfdMpv *mpv = player->streams.mpv;
    SfdIpuCtl *ctl = &mpv->ipu;
    SfdIpuStream *stream = &mpv->stream;
    if (ctl->endSent == 1) {
        sceMpegGetPictureAbort(&mpv->mpeg);
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

int mpegStopDMA(int unused0, int unused1, SfdPlayer *player) {
    SfdMpv *mpv = player->streams.mpv;
    viBufStopDMA(&mpv->stream);
    return 1;
}

int mpegRestartDMA(int unused0, int unused1, SfdPlayer *player) {
    SfdMpv *mpv = player->streams.mpv;
    viBufRestartDMA(&mpv->stream);
    return 1;
}

void FUN_002a9bc8(SfdPlayer *player)
{
    SfdMpv *mpv;
    if (SFMPVP_IsSceMpegUsed(player)) {
        mpv = player->streams.mpv;
        viBufDelete(&mpv->stream);
        if (SFPLY_GetResetFlg() != 1) {
            sceMpegDelete(&mpv->mpeg);
        } else {
            sceMpegReset();
            sfmpvp_SaveMpvp(player);
        }
    }
}

void sfmpvp_SaveMpvp(SfdPlayer *player) {
    SfdMpv *mpv = player->streams.mpv;
    UTY_MemcpyByte(&sfmpvp_bkup_buf, &mpv->mpeg, 0x48);
}

void sfmpvp_RestoreMpvp(SfdPlayer *player) {
    SfdMpv *mpv = player->streams.mpv;
    UTY_MemcpyByte(&mpv->mpeg, &sfmpvp_bkup_buf, 0x48);
}

int SFMPVP_Put(SfdPlayer *player, char *src, int pos) {
    SfdMpv *mpv;
    if (SFMPVP_IsSceMpegUsed(player) == 0) {
        return pos;
    }
    mpv = player->streams.mpv;
    return sfmpvp_PutVibuf(&mpv->stream, src, pos);
}

int SFMPVP_Unput(SfdPlayer *player, int count) {
    SfdMpv *mpv;
    if (SFMPVP_IsSceMpegUsed(player) == 0) {
        return count;
    }
    mpv = player->streams.mpv;
    return viBufUnput(&mpv->stream, count);
}

void sfmpvps2_StopIpu(SfdPlayer *player, int value) {
    SfdMpv *mpv = player->streams.mpv;
    SfdIpuCtl *ctl = &mpv->ipu;
    if (ctl->stopped != 1) {
        viBufFlush(&mpv->stream);
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



int SFMPVP_GetFrameCount(SfdPlayer *player) {
    SfdMpv *mpv = player->streams.mpv;
    return mpv->mpeg.f8;
}

void FUN_002aa050(SfdPlayer *player, unsigned char *data, int size) {
    SfdMpv *mpv = player->streams.mpv;
    SfdIpuCtl *ipu = &mpv->ipu;
    unsigned char win[6];
    unsigned char *hit;
    int found = 0;
    int i = 0;
    int skip;
    ipu->f12 += ipu->f4;
    ipu->f4 = ipu->f8;
    ipu->f8 = 0;
    win[0] = ipu->f16;
    win[1] = ipu->f17;
    win[2] = ipu->f18;
    win[3] = data[0];
    win[4] = data[1];
    win[5] = data[2];
    while (i < (size < 4 ? size : 3)) {
        if (win[i] == 0 && win[i + 1] == 0 && win[i + 2] == 1) {
            if (win[i + 3] == 0) {
                ipu->f8++;
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
        ipu->f16 = win[size];
        ipu->f17 = win[size + 1];
        ipu->f18 = win[size + 2];
    } else {
        ipu->f16 = data[size - 3];
        ipu->f17 = data[size - 2];
        ipu->f18 = data[size - 1];
    }
    while (size >= 4) {
        hit = MPV_SearchDelim(data, size, 132);
        if (hit == 0) {
            break;
        }
        if (MPV_CheckDelim(hit) & 4) {
            ipu->f8++;
        } else {
            found = 1;
        }
        hit += 4;
        skip = hit - data;
        data = hit;
        size -= skip;
    }
    if (found == 1 && FUN_0029ed48(player) == 0 && FUN_0029edb0(player) == 0) {
        sfmpvps2_StopIpu(player, 1);
    }
}

void sfmpvp_ConsumePsc(SfdPlayer *player) {
    SfdMpv *mpv = player->streams.mpv;
    SfdIpuCtl *ctl = &mpv->ipu;
    ctl->f12--;
}

int SFMPVP_IsPscEnough(SfdPlayer *player) {
    SfdMpv *mpv;
    SfdIpuCtl *ctl;
    if (SFMPVP_IsSceMpegUsed(player) == 0) {
        return 1;
    }
    mpv = player->streams.mpv;
    ctl = &mpv->ipu;
    if (ctl->value == 1) {
        return 1;
    }
    if (ctl->f12 < 3) return 0;
    return 1;
}

SfdMpegCtx *FUN_002aa2d8(SfdPlayer *player) {
    SfdMpv *mpv = player->streams.mpv;
    return &mpv->mpeg;
}

int SFMPVP_GetSizeSceMpegHn(void) {
    return 72;
}
