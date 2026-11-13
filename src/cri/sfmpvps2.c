#include "dw4/cri/sfmpv.h"

#define D_ENABLER ((volatile unsigned int *)0x1000F520)
#define D_ENABLEW ((volatile unsigned int *)0x1000F590)
#define D3_CHCR ((volatile unsigned int *)0x1000B000)
#define D4_CHCR ((volatile unsigned int *)0x1000B400)
#define D4_MADR ((volatile unsigned int *)0x1000B410)
#define D4_QWC  ((volatile unsigned int *)0x1000B420)
#define D4_TADR ((volatile unsigned int *)0x1000B430)
#define REG(a) (*(volatile int *)(a))
#define UNCACHED(address) (((address) & 0x0FFFFFFF) | 0x20000000)

extern int DAT_004beb10;
extern SfdMpegCtx DAT_00585630;
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
void mpsutl_CopyBytes(void *dst, void *src, int size);
void mpsutl_FillBytes(void *dst, int value, int size);
int sfd_ReportError();
int FUN_002abf68(void);
void sceMpegGetPictureAbort(SfdMpegCtx *mpeg);

extern char sfmpv_seqend_codes[16];

void FUN_002a8e50(SfdIpuStream *stream, unsigned int *first, int *firstSize, unsigned int *second, int *secondSize);
int sfmpvps2_SendIpu(SfdIpuStream *stream);
void FUN_002a8f40(SfdIpuStream *stream, int bytes);
int FUN_002a8f90(SfdIpuStream *stream, int count);
int FUN_002a9210(SfdIpuStream *stream);
int FUN_002a9310(SfdIpuStream *stream);
int FUN_002a9628(SfdIpuStream *stream);
void FUN_002a9680(SfdIpuStream *stream);
int FUN_002a96e0(SfdPlayer *player);
int sfmpvps2_PutData(SfdIpuStream *stream, char *src, int pos);
void FUN_002a9c50(SfdPlayer *player);
int FUN_002a9dc8(char *buf, int size, char *dst, int cap, char *src, int pos, char *data, int len);

int FUN_002a8b50(SfdIpuStream *stream, int position) {
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

void FUN_002a8c08(unsigned int chcr) {
    DIntr();
    *D_ENABLEW = *D_ENABLER | 0x10000;
    *D4_CHCR = chcr;
    *D_ENABLEW = *D_ENABLER & ~0x10000;
    EIntr();
}

void FUN_002a8c70(long long *arg0, long long arg1, long long arg2, long long arg3) {
    *arg0 = (arg1 << 0x20) | ((unsigned long long) (arg2 << 0x20) >> 4) | ((unsigned long long) (arg3 << 0x20) >> 0x20);
}

void FUN_002a8f40(SfdIpuStream *stream, int bytes) {
    WaitSema(stream->sema);
    stream->restBytes += bytes;
    stream->f72 += bytes;
    SignalSema(stream->sema);
}

int FUN_002a8f90(SfdIpuStream *stream, int count) {
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

int FUN_002a9210(SfdIpuStream *stream) {
    WaitSema(stream->sema);
    stream->f68 = 0;
    FUN_002a8c08(5);
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

int FUN_002a9628(SfdIpuStream *stream) {
    FUN_002a8c08(5);
    *D4_QWC = 0;
    *D4_MADR = 0;
    *D4_TADR = 0;
    DeleteSema(stream->sema);
    return 1;
}

void FUN_002a9680(SfdIpuStream *stream) {
    WaitSema(stream->sema);
    stream->restBytes = (stream->restBytes + 2051) / 2048 * 2048;
    SignalSema(stream->sema);
}

void FUN_002a96d0(int enable) {
    DAT_004beb10 = enable;
}

int FUN_002a96e0(SfdPlayer *player) {
    SfdMpv *mpv = player->streams.mpv;
    return mpv->ipu.enabled != 0;
}

void FUN_002a96f0(void) {
    if (DAT_004beb10 != 0) {
        sceMpegInit();
        mpsutl_FillBytes(&DAT_00585630, 0, 0x48);
    }
}

void FUN_002a9738(SfdPlayer *player, int *bytes, int *position, int *start, int *end) {
    SfdMpv *mpv = player->streams.mpv;
    SfdIpuStream *stream = &mpv->stream;
    *bytes = stream->bytes;
    *start = stream->f12 << 11;
    *position = (((stream->f12 + stream->queuedSct) << 11) + stream->restBytes) % stream->bytes;
    *end = (stream->queuedSct << 11) + stream->restBytes;
}

int FUN_002a99b8(SfdPlayer *player) {
    SfdMpv *mpv = player->streams.mpv;
    return mpv->event.f4;
}

int FUN_002a99c8(void *unused, void *record, SfdPlayer *player) {
    SfdMpv *mpv;
    DAT_00585678 = 1;
    __builtin_memcpy(DAT_00585680, record, 8);
    mpv = player->streams.mpv;
    __builtin_memcpy(&mpv->event, record, 8);
    sfd_ReportError(player, 0xFF000F40);
    return 1;
}

int sfmpvps2_PutData(SfdIpuStream *stream, char *src, int pos) {
    unsigned int first;
    int firstSize;
    unsigned int second;
    int secondSize;
    int result;
    FUN_002a8e50(stream, &first, &firstSize, &second, &secondSize);
    result = FUN_002a9dc8((char *)UNCACHED(first), firstSize, (char *)UNCACHED(second), secondSize, src, pos, 0, 0);
    FUN_002a8f40(stream, result);
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
    sfmpvps2_SendIpu(stream);
    if (ctl->endRequest != 0 && stream->queuedSct == 0) {
        ctl->endSent = 1;
        sfmpvps2_PutData(stream, sfmpv_seqend_codes, 16);
        stream->restBytes = stream->bytes;
        sfmpvps2_SendIpu(stream);
    }
    return 1;
}

int FUN_002a9b78(int unused0, int unused1, SfdPlayer *player) {
    SfdMpv *mpv = player->streams.mpv;
    FUN_002a9210(&mpv->stream);
    return 1;
}

int FUN_002a9ba0(int unused0, int unused1, SfdPlayer *player) {
    SfdMpv *mpv = player->streams.mpv;
    FUN_002a9310(&mpv->stream);
    return 1;
}

void FUN_002a9bc8(SfdPlayer *player)
{
    SfdMpv *mpv;
    if (FUN_002a96e0(player)) {
        mpv = player->streams.mpv;
        FUN_002a9628(&mpv->stream);
        if (FUN_002abf68() != 1) {
            sceMpegDelete(&mpv->mpeg);
        } else {
            sceMpegReset();
            FUN_002a9c50(player);
        }
    }
}

void FUN_002a9c50(SfdPlayer *player) {
    SfdMpv *mpv = player->streams.mpv;
    mpsutl_CopyBytes(&DAT_00585630, &mpv->mpeg, 0x48);
}

void FUN_002a9c78(SfdPlayer *player) {
    SfdMpv *mpv = player->streams.mpv;
    mpsutl_CopyBytes(&mpv->mpeg, &DAT_00585630, 0x48);
}

int FUN_002a9ca0(SfdPlayer *player, char *src, int pos) {
    SfdMpv *mpv;
    if (FUN_002a96e0(player) == 0) {
        return pos;
    }
    mpv = player->streams.mpv;
    return sfmpvps2_PutData(&mpv->stream, src, pos);
}

int FUN_002a9d10(SfdPlayer *player, int count) {
    SfdMpv *mpv;
    if (FUN_002a96e0(player) == 0) {
        return count;
    }
    mpv = player->streams.mpv;
    return FUN_002a8f90(&mpv->stream, count);
}

void sfmpvps2_StopIpu(SfdPlayer *player, int value) {
    SfdMpv *mpv = player->streams.mpv;
    SfdIpuCtl *ctl = &mpv->ipu;
    if (ctl->stopped != 1) {
        FUN_002a9680(&mpv->stream);
        ctl->stopped = 1;
        ctl->value = value;
    }
}

int FUN_002a9dc8(char *buf, int size, char *dst, int cap, char *src, int pos, char *data, int len) {
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

int FUN_002aa040(SfdPlayer *player) {
    SfdMpv *mpv = player->streams.mpv;
    return mpv->mpeg.f8;
}

void FUN_002aa268(SfdPlayer *player) {
    SfdMpv *mpv = player->streams.mpv;
    SfdIpuCtl *ctl = &mpv->ipu;
    ctl->f12--;
}

int FUN_002aa280(SfdPlayer *player) {
    SfdMpv *mpv;
    SfdIpuCtl *ctl;
    if (FUN_002a96e0(player) == 0) {
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

int FUN_002aa2e8(void) {
    return 72;
}
