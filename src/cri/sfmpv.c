#include "dw4/cri/sfmpv.h"

extern char DAT_00581570[];
extern SfdMpvCond DAT_005855b0;
extern SfdMpvWorkBufs DAT_005855d8;
extern SfdMpvFrameBufs DAT_005855e0;
extern char *DAT_00585620;
extern int DAT_00585624;
extern int DAT_00585628;
extern int DAT_004beb08;
extern int DAT_004f5060[];

extern void *memset(void *dst, int value, unsigned int size);
extern void *memcpy(void *dst, const void *src, unsigned int size);
int FUN_0027c760(int sj, int id, int mode);
int FUN_00285118(int id, int arg, int a, int b);
int FUN_0028b0c0(void *dst, void *src, int n);
void FUN_0028b530(void *dst, int value, int size);
int FUN_0028dc78();
int FUN_0028ea48(void *handle, void (*callback)(SfdPlayer *, int), SfdPlayer *player);
int FUN_0028ed30(void *handle, int sj);
int FUN_0028eef0(void *handle, int *value);
void FUN_0028ef50(void *handle, int *x, int *y, int *z);
int FUN_0028f018(void *handle, int *a, int *b);
int FUN_0028f098(void *handle, int index, int a, int b, int c);
int FUN_0028f360(void *handle, void *chunk, int *result);
int FUN_00290bd0(int count, void *work);
int FUN_00291020(void);
void *FUN_00291048(void);
int FUN_002911d0();
int FUN_00291250(void *handle, int index, int value);
int FUN_00291368(void *handle, int index, int *value);
int UTY_MulDiv(int a, int b, int c);
int FUN_0029dd98(SfdPlayer *player, int index, SfdRingInfo *info);
void FUN_0029de70(SfdPlayer *player, int index, int n);
int FUN_0029e290(SfdPlayer *player, int index);
int FUN_0029e2d0(SfdPlayer *player, int index);
void FUN_0029e370(SfdPlayer *player, int index, int *entry);
void FUN_0029e3d0(SfdPlayer *player, int index, int amount);
int FUN_0029ea28(SfdPlayer *player, int index, int value);
int FUN_0029ea48(SfdPlayer *player, int index);
int FUN_0029ea68(SfdPlayer *player, int index, int value);
int FUN_0029ea88(SfdPlayer *player, int index);
int FUN_0029eaa8(SfdPlayer *player, int index);
void FUN_0029eaf8(int entry, int *a, int *b);
long FUN_0029ecb0(long total, int a);
void FUN_0029edf8(SfdPlayer *player, int count);
int FUN_002a0960(SfdPlayer *player);
int sfd_ReportError();
int sfd_CheckHn(SfdPlayer *player);
void sfd_Lock(void *guard);
void sfd_Unlock(void *guard);
char *FUN_002a41a8(SfdRingInfo *ring, int mask, int *code);
void FUN_002a7278(void *source, int *kind, char **data, int *size);
void FUN_002a7af0(SfdBufPool *pool);
void FUN_002a7e30(SfdPlayer *player, SfdSlot *slot, SfdFrameInfo **out);
void FUN_002a96f0(void);
int FUN_002a96e0(SfdPlayer *player);
void FUN_002a97a0(SfdPlayer *player);
void FUN_002a9bc8(SfdPlayer *player);
int FUN_002aa040(SfdPlayer *player);
void FUN_002abc98(SfdPlayer *player, int a, int b);
int FUN_002abf68(void);
int FUN_002ada78(SfdPlayer *player, int option, int value);
int SFD_GetCond(SfdPlayer *player, int option);
void FUN_002ae248(SfdTimeStamp *stamp, int value);
void FUN_002af070(SfdTimeCode *tc, int *a, int *b);
int FUN_002af6c0(SfdPlayer *player, int a, int b);
int FUN_002b03e8(SfdPlayer *player, int index);

int FUN_002a3558();
int FUN_002a3708(void);
int FUN_002a3748(SfdPlayer *player);
void FUN_002a37e0(SfdPlayer *player);
void FUN_002a3850(SfdPlayer *player);
int FUN_002a38f0(SfdPlayer *player);
void FUN_002a3908(SfdPlayer *player);
int FUN_002a39b8(SfdPlayer *player);
int FUN_002a3a18(SfdPlayer *player);
int FUN_002a3a60(SfdPlayer *player);
void FUN_002a3b48(SfdPlayer *player);
void FUN_002a3b70(SfdPlayer *player);
void FUN_002a3c18(SfdPlayer *player, int value);
int FUN_002a3c38(SfdPlayer *player);
int FUN_002a3cb8(SfdPlayer *player, int *a, int *b, int *c);
int FUN_002a4468(SfdPlayer *player, int a, int b, int c, int *more);
int FUN_002a4888(SfdPlayer *player);
int FUN_002a4958(SfdPlayer *player);
int FUN_002a49b8(SfdPlayer *player);
void FUN_002a4a60(SfdPlayer *player, SfdStream *stream);
void FUN_002a4b20(SfdPlayer *player, int amount);
int FUN_002a4bb0(SfdPlayer *player);
int FUN_002a4bc8(SfdPlayer *player, int status, int n, int code);
int FUN_002a5680(SfdPlayer *player, SfdPicInfo *pic);
void FUN_002a5740(SfdPlayer *player, SfdPicInfo *pic, int id, int flag);
void FUN_002a5838(int id, int a, int b, int c, SfdTimeCode *tc);
void FUN_002a5a50(SfdTimeCode *src, SfdTimeCode *dst);
void FUN_002a5ef0(SfdPlayer *player, int pts, SfdChunk *chunk);
void FUN_002a6010(SfdPicGeom *geom, int pts, SfdPicInfo *pic, int x);
int FUN_002a6048(SfdPlayer *player, SfdPicGeom *geom);
int FUN_002a6308(SfdPlayer *player, int kind);
int FUN_002a64c0(SfdPlayer *player, unsigned int kind);
void FUN_002a6870(SfdPlayer *player);
int FUN_002a6470(SfdPlayer *player);
int FUN_002a6510(SfdPlayer *player, unsigned int type, SfdChunk *chunk);
int FUN_002a65f0(SfdPlayer *player, unsigned int type);
void FUN_002a6368(SfdPlayer *player, SfdPicInfo *pic, int kind);
void FUN_002a70e8(SfdPlayer *player, SfdSlot *slot);
void FUN_002a73f0(SfdChunk *dst, SfdChunk *src);
void FUN_002a7598(SfdPlayer *player, int n);
int FUN_002a7770(SfdPlayer *player, SfdMpv *mpv);
int FUN_002a7968(void);
void FUN_002a7a30(SfdSlot *slot, int *ids, int count);
void FUN_002a7ad0(SfdSlotInfo *info);
void FUN_002a7b48(SfdPlayer *player, int code);
int FUN_002a7d18(void *handle);
int FUN_002a8088(SfdPlayer *player, char *body);
SfdPicRecord *FUN_002a8158(SfdPlayer *player, char *body);
int FUN_002a81d0(SfdPlayer *player, SfdMpv *mpv, int *ok);
SfdPicture *FUN_002a82c8(SfdPlayer *player);
SfdSlot *FUN_002a8440(SfdPlayer *player, char *body);
int FUN_002a84e0(SfdPlayer *player);
int FUN_002a8500(SfdPlayer *player);
void FUN_002a8668(SfdSlot *slot);
SfdSlot *FUN_002a86b8(SfdPlayer *player, int *out);
int FUN_002a8878(SfdPlayer *player);
SfdSlot *FUN_002a8998(SfdPlayer *player);
void FUN_002a8a30();
int FUN_002a8b30(SfdSlot *a, SfdSlot *b);
void FUN_002a75b8(SfdPlayer *player);

void FUN_002a2f30(SfdMpvCond *cond) {
    DAT_005855b0 = *cond;
    DAT_005855b0.f16 = (DAT_005855b0.f16 + 0x3F) & ~0x3F;
    DAT_005855b0.f32 = (DAT_005855b0.f32 + 0x3F) & ~0x3F;
    memset(&DAT_005855d8, 0, 8);
    memset(&DAT_005855e0, 0, 0x40);
}

void FUN_002a2fe0(SfdMpvCond *cond, int *work, int *bufs)
{
    int i;
    int count;
    DAT_005855b0 = *cond;
    DAT_005855b0.f16 = 0;
    DAT_005855b0.f32 = 0;
    for (i = 0; i < 2; i++)
        DAT_005855d8.w[i] = (work[i] + 63) & ~63;
    count = cond->count;
    for (i = 0; i < 16; i++) {
        if (i < count)
            DAT_005855e0.w[i] = (bufs[i] + 63) & ~63;
        else
            DAT_005855e0.w[i] = 0;
    }
}

void FUN_002a30d0(SfdMpvCond *cond, SfdPlanes *planes) {
    int columns = (cond->f0 + 15) / 16;
    int rows;
    int lumaBlocks = (columns * 16 + 63) / 64;
    int chromaBlocks;
    char *base;
    rows = (cond->f4 + 15) / 16;
    chromaBlocks = (columns * 8 + 63) / 64;
    base = (char *)cond->f32;
    planes->lumaStride = lumaBlocks << 6;
    planes->chromaStride = chromaBlocks << 6;
    planes->base = base;
    planes->luma = base + ((lumaBlocks * rows) << 10);
    planes->chroma = planes->luma + ((chromaBlocks * rows) << 9);
}

void FUN_002a3170(char *base, int width, int height, SfdPlanes *planes) {
    int columns = (width + 15) / 16;
    int rows;
    int lumaBlocks = (columns * 16 + 63) / 64;
    int chromaBlocks;
    rows = (height + 15) / 16;
    chromaBlocks = (columns * 8 + 63) / 64;
    planes->lumaStride = lumaBlocks << 6;
    planes->chromaStride = chromaBlocks << 6;
    planes->base = base;
    planes->luma = base + ((lumaBlocks * rows) << 10);
    planes->chroma = planes->luma + ((chromaBlocks * rows) << 9);
}

void FUN_002a3200(SfdPlayer *player, int mode, int value) {
    void *h = 0;
    if (player != 0) {
        SfdMpv *mpv;
        if (sfd_CheckHn(player) != 0) {
            sfd_ReportError(0, 0xff000181);
            return;
        }
        mpv = player->streams.mpv;
        h = mpv->handle;
    }
    if (FUN_00291250(h, mode, mode != 5 ? value : 0) != 0) {
        sfd_ReportError(player, 0xff000f12);
        return;
    }
}

int FUN_002a32b8(SfdPlayer *player, int *values, unsigned int size) {
    SfdMpv *mpv = player->streams.mpv;
    void *handle = mpv->handle;
    int count;
    int i;
    if (handle == 0) {
        return 0;
    }
    count = size / 4 > 16 ? 16 : size / 4;
    for (i = 0; i < count; i++) {
        FUN_00291368(handle, i, &values[i]);
    }
    return count;
}

void FUN_002a3340(SfdPlayer *player, int *values, int count) {
    SfdMpv *mpv;
    int *value;
    int index;
    void *handle;
    mpv = player->streams.mpv;
    handle = mpv->handle;
    if (handle != 0) {
        index = 0;
        if (count > 0) {
            value = values;
            do {
                FUN_00291250(handle, index++, *value++);
            } while (index < count);
        }
    }
}

int FUN_002a33b8(SfdPlayer *player, int *out) {
    *out = 0;
    if (sfd_CheckHn(player) != 0) {
        return sfd_ReportError(0, 0xFF000182);
    }
    *out = FUN_002a8500(player);
    return 0;
}

int FUN_002a3428(SfdPlayer *player, int index, int a, int b, int c) {
    SfdMpv *mpv;
    if (sfd_CheckHn(player) != 0) {
        return sfd_ReportError(0, 0xFF000184, a, b, c);
    }
    mpv = player->streams.mpv;
    FUN_0028f098(mpv->handle, index, a, b, c);
    return 0;
}

void FUN_002a34d0(SfdPlayer *player, char *base, int count, int size) {
    if (sfd_CheckHn(player) != 0) {
        sfd_ReportError(0, 0xFF000185, count, size);
        return;
    }
    FUN_002a3558(player, base);
}

int FUN_002a3558(SfdPlayer *player, char *base, int count, int size)
{
    SfdMpv *mpv = player->streams.mpv;
    SfdBufPool *pool = &mpv->pool;
    int i;
    if (base == 0 || count == 0 || size == 0) {
        FUN_002a7af0(pool);
        return 0;
    }
    if (count < player->f44 + 4)
        return sfd_ReportError(player, 0xFF000F1D);
    pool->base = base;
    i = 0;
    pool->slot[0].addr = base;
    base += size;
    pool->count = count;
    count -= 2;
    pool->slot[1].addr = base;
    base += size;
    pool->size = size;
    pool->slot[0].size = 0;
    pool->slot[1].size = 0;
    for (; i < (count < 17 ? count : 16); i++) {
        pool->slot[i + 2].size = 0;
        pool->slot[i + 2].addr = base;
        base += size;
    }
    return 0;
}

int FUN_002a3628(void) {
    int result;
    FUN_002a96f0();
    if (FUN_002a3708() != 0) {
        /* The EE short-loop workaround pads this empty loop with nops. */
        for (;;) {
        }
    }
    result = FUN_00290bd0(8, DAT_00581570);
    if (result != 0) {
        return sfd_ReportError(0, (result == (int)0xFF03FF05) ? 0xFF000F13 : 0xFF000F01);
    }
    memset(&DAT_005855b0, 0, 36);
    memset(&DAT_005855d8, 0, 8);
    memset(&DAT_005855e0, 0, 64);
    DAT_004beb08 = 0;
    return 0;
}

int FUN_002a3708(void) {
    return 0;
}

int FUN_002a3710(void) {
    FUN_00291020();
    return 0;
}

void FUN_002a3730(SfdPlayer *player) {
    FUN_002a3748(player);
}

int FUN_002a3748(SfdPlayer *player) {
    int status;
    int result;
    result = SFD_GetCond(player, 5);
    if (result != 0) {
        if (FUN_002a38f0(player) == 1) {
            return 0;
        }
        FUN_002a37e0(player);
        if (player->f72 == 2) {
            FUN_002a3850(player);
        }
        status = FUN_002a3c38(player);
        FUN_002a3908(player);
        FUN_002a3b70(player);
        result = status;
        return result;
    }
    return result;
}

void FUN_002a37e0(SfdPlayer *player) {
    int value;
    int mode;
    if (SFD_GetCond(player, 28) == 0) {
        return;
    }
    value = FUN_002a0960(player);
    if (value == 0) {
        mode = 1;
    } else if (value > 0) {
        mode = 0;
    } else if (value == -1) {
        return;
    } else {
        mode = 0;
    }
    FUN_002a3200(player, 5, mode);
}

void FUN_002a3850(SfdPlayer *player) {
    SfdMpv *mpv = player->streams.mpv;
    void *handle = mpv->handle;
    int pair[2];
    int result[4];
    pair[0] = SFD_GetCond(player, 93);
    pair[1] = SFD_GetCond(player, 94);
    if (pair[0] != 0 && pair[1] != 0 && mpv->state == 192) {
        if (FUN_0028f360(handle, pair, result) == 0) {
            mpv->f116 = 2;
            mpv->state = 200;
        }
    }
}

int FUN_002a38f0(SfdPlayer *player) {
    return FUN_0029ea88(player, player->streams.f20);
}

void FUN_002a3908(SfdPlayer *player) {
    SfdStreams *streams = &player->streams;
    int target = streams->f20;
    int source = streams->f16;
    if (FUN_0029ea48(player, target) != 1 && FUN_0029ea48(player, source) == 1 && FUN_002a39b8(player) != 0) {
        FUN_0029ea28(player, target, 1);
        FUN_002a3b48(player);
    }
}

int FUN_002a39b8(SfdPlayer *player) {
    if ((FUN_002a84e0(player) != 0) || ((FUN_002a3a18(player) != 0) && (FUN_002a3a60(player) != 0))) {
        return 1;
    }
    return 0;
}

int FUN_002a3a18(SfdPlayer *player) {
    int limit = player->pending.f92;
    int size = player->f44;
    if (limit == -1) {
        limit = size;
    }
    if (size < limit) {
        limit = size;
    }
    if (FUN_002a8500(player) < limit) {
        return 0;
    }
    return 1;
}

int FUN_002a3a60(SfdPlayer *player)
{
    SfdMpv *mpv = player->streams.mpv;
    void *handle = mpv->handle;
    SfdPicWait *wait = &player->picWait;
    int value;
    int idx;
    if (FUN_002a4bb0(player) == 1)
        return 1;
    if (wait->busy != 0 && wait->f124 == 0)
        return 1;
    FUN_0028eef0(handle, &value);
    if (value == 0x3FFFF)
        return 1;
    if (FUN_0029e2d0(player, 1) >= mpv->limit)
        return 1;
    idx = FUN_002b03e8(player, 1) == 0;
    if (FUN_0029e2d0(player, idx) < FUN_0029e290(player, idx))
        return 0;
    return 1;
}

void FUN_002a3b48(SfdPlayer *player) {
    SfdTimeStamp *stamp = &player->timer.f280;
    if (stamp->a != 0x7FFFFFFF) {
        stamp->done = 1;
    }
}

void FUN_002a3b70(SfdPlayer *player) {
    SfdDecodeFlags *decode = &player->decode;
    int status = FUN_002a8500(player);
    if (status == -1 || (FUN_002a84e0(player) != 0 && status == 1 && decode->f24 != 0)) {
        FUN_002a3c18(player, 1);
        if (decode->f0 == 0) {
            FUN_002ada78(player, 5, 0);
        }
    }
}

void FUN_002a3c18(SfdPlayer *player, int value) {
    FUN_0029ea68(player, player->streams.f20, value);
}

int FUN_002a3c38(SfdPlayer *player) {
    int a;
    int b;
    int c;
    int more;
    int status;
    do {
        status = FUN_002a3cb8(player, &a, &b, &c);
        if (status != 0) {
            break;
        }
        status = FUN_002a4468(player, a, b, c, &more);
        if (status != 0) {
            break;
        }
    } while (more != 0);
    FUN_002a75b8(player);
    return status;
}

int FUN_002a40b8(SfdRingInfo *ring, char *addr) {
    int offset;
    if (addr >= ring->addr0 && addr < ring->addr0 + ring->len0) {
        offset = addr - ring->addr0;
    } else if (addr >= ring->addr1 && addr < ring->addr1 + ring->len1) {
        offset = addr - ring->addr1 + ring->len0;
    } else {
        offset = 0;
    }
    return offset;
}

int FUN_002a4120(SfdPlayer *player) {
    int index = player->streams.f16;
    int total = FUN_0029e290(player, index);
    if (total - FUN_0029eaa8(player, index) < player->f40) {
        return sfd_ReportError(player, 0xFF000F1C);
    }
    return 0;
}

void FUN_002a4730(SfdPlayer *player, SfdChunk *out) {
    SfdRingInfo info;
    if (FUN_0029dd98(player, player->streams.f16, &info) != 0) {
        out->addr = 0;
        out->size = 0;
    } else {
        out->addr = info.addr0;
        out->size = info.len0;
    }
}

int FUN_002a4838(SfdPlayer *player, SfdStream *stream) {
    if (FUN_002a4888(player) == -1) {
        return -1;
    }
    FUN_002a4a60(player, stream);
    return 0;
}

int FUN_002a4888(SfdPlayer *player) {
    SfdTimer *timer = &player->timer;
    SfdMpv *mpv = player->streams.mpv;
    int count;
    if (SFD_GetCond(player, 6) == 0) {
        count = FUN_002a4958(player);
    } else {
        count = FUN_002a49b8(player);
        if (count < 0) {
            return -1;
        }
    }
    if (count > 0) {
        FUN_0029edf8(player, count);
        mpv->f136++;
        if (FUN_002a96e0(player) != 0) {
            timer->f352 = FUN_002aa040(player) + 1;
        }
    }
    FUN_002ae248(&timer->state, 0x7FFFFFFF);
    FUN_002ae248(&timer->best, -1);
    mpv->state = 192;
    return 0;
}

int FUN_002a4958(SfdPlayer *player) {
    SfdTimeStamp *state = &player->timer.state;
    SfdTimeCode tc;
    int position;
    int size;
    /* matching construct: manual — best.done/best.tc read through the player, state.a through the state pointer */
    if (player->timer.best.done == 0) {
        return 0;
    }
    FUN_002a5a50(&player->timer.best.tc, &tc);
    tc.add = 0;
    FUN_002af070(&tc, &position, &size);
    return position - state->a;
}

void FUN_002a4a60(SfdPlayer *player, SfdStream *stream) {
    int buf[4];
    for (;;) {
        stream->ops->read(stream, 1, 4, buf);
        if (buf[1] != 4 || FUN_0028dc78(buf[0]) != 128) {
            break;
        }
        stream->ops->skip(stream, 0, buf);
        FUN_002a4b20(player, 4);
    }
    stream->ops->end(stream, 1, buf);
}

void FUN_002a4b20(SfdPlayer *player, int amount) {
    FUN_0029e3d0(player, player->streams.f16, amount);
    player->f2464 += amount;
}

int FUN_002a4b68(SfdPlayer *player, int level, int kind) {
    if (kind == 128) {
        return 1;
    }
    if (level < 5 && FUN_002a4bb0(player) == 1) {
        return 1;
    }
    return 0;
}

int FUN_002a4bb0(SfdPlayer *player) {
    return FUN_0029ea88(player, player->streams.f16);
}

int FUN_002a4bc8(SfdPlayer *player, int status, int n, int code)
{
    switch (status) {
    case 0:
        return 0;
    case -2:
        if (n > 0)
            return 0;
        return sfd_ReportError(player, status);
    case -3:
        if (n > 0)
            return 0;
        return sfd_ReportError(player, status);
    default:
        return sfd_ReportError(player, code);
    }
}

void FUN_002a5060(SfdRecord *record) {
    SfdRecordTail *tail = &record->tail;
    record->f0 = 0;
    record->f4 = 0;
    record->f8 = 0;
    tail->f0 = -1;
    tail->f12 = -1;
    tail->f8 = 0;
}

long FUN_002a5208(int count, int rate) {
    return (long)count * 90000000 / rate;
}

void FUN_002a54d0(SfdPlayer *player, SfdSlot *slot) {
    int t[2];
    SfdTimer *timer;
    int d;
    timer = &player->timer;
    FUN_002af070(&slot->stamp.tc, &t[0], &t[1]);
    d = t[0] - timer->state.a;
    slot->stamp.done = 1;
    slot->stamp.a = d;
    slot->stamp.b = t[1];
    if (d >= timer->best.a) {
        timer->best = slot->stamp;
    }
}

void FUN_002a55a0(SfdPlayer *player, SfdPicInfo *pic, int a, int b) {
    int enabled = SFD_GetCond(player, 52);
    if (enabled == 0) {
        if (a >= 0 || pic->f48 == 0 || pic->f87 != 0
            || (b != 0 && FUN_002a5680(player, pic) != 0)) {
            enabled = 1;
            FUN_002ada78(player, 52, 1);
        }
    }
    if (enabled == 1) {
        FUN_002a5740(player, pic, a, b);
    }
}

int FUN_002a5680(SfdPlayer *player, SfdPicInfo *pic) {
    SfdTimeCode tc;
    int now;
    int rate;
    int start;
    int span;
    if (player->timer.best.done == 0) {
        return 0;
    }
    tc = player->timer.tc;
    FUN_002af070(&tc, &now, &rate);
    FUN_002af070(&player->timer.best.tc, &start, &rate);
    span = SFD_GetCond(player, 53) * rate;
    if (now <= start) {
        return 1;
    }
    if (now < start + span) {
        return 0;
    }
    return 1;
}

void FUN_002a5740(SfdPlayer *player, SfdPicInfo *pic, int id, int flag)
{
    SfdTimer *timer = &player->timer;
    int b = pic->f28;
    int a = pic->rateIndex;
    int idx = pic->number;
    if (flag != 0 && id >= 0) {
        FUN_002a5838(id, a, b, idx, &player->timer.tc);
        return;
    }
    if (timer->best.done == 0) {
        if (player->userWork == 0) {
            timer->tc.rate = a;
            timer->tc.drop = 0;
            timer->tc.hour = 0;
            timer->tc.minute = 0;
            timer->tc.second = 0;
            timer->tc.frame = 0;
        }
    } else if (flag != 0) {
        FUN_002a5a50(&timer->best.tc, &timer->tc);
        timer->fields[0].f2 = timer->tc.field;
        timer->fields[idx].f2 = timer->tc.field;
    } else {
        timer->tc.rate = timer->best.tc.rate;
        timer->tc.drop = timer->best.tc.drop;
        timer->tc.hour = timer->best.tc.hour;
        timer->tc.minute = timer->best.tc.minute;
        timer->tc.second = timer->best.tc.second;
        timer->tc.frame = timer->best.tc.frame;
    }
}

void FUN_002a5b48(SfdPlayer *player)
{
    SfdTimeStamp *state = &player->timer.state;
    SfdTimeCode tc;
    int a, b;
    if (state->done != 0)
        return;
    tc = player->timer.tc;
    tc.add = 0;
    FUN_002af070(&tc, &a, &b);
    state->tc = tc;
    state->a = a;
    state->b = b;
    state->done = 1;
}

void FUN_002a5c28(SfdPlayer *player)
{
    SfdTimeStamp *state = &player->timer.state;
    SfdTimeCode tc;
    int a, b;
    SfdTimeStamp *cur;
    SfdTimeStamp *best;
    int d;
    tc = player->timer.tc;
    FUN_002af070(&tc, &a, &b);
    player->timer.cur.tc = tc;
    cur = &player->timer.cur;
    best = &player->timer.best;
    d = a - state->a;
    cur->done = 1;
    cur->a = d;
    cur->b = b;
    if (d >= best->a)
        *best = *cur;
}

void FUN_002a5d70(SfdPicInfo *pic, SfdPicSummary *out) {
    out->f0 = pic->rateIndex;
    out->f4 = pic->f28;
    out->f8 = pic->f32;
    out->f12 = pic->f36;
    out->f16 = pic->f40;
    out->f20 = pic->f44;
    out->f24 = pic->number;
    out->f28 = (signed char)pic->f84;
    out->f30 = 0;
}

int FUN_002a5dc0(SfdPlayer *player, void *sj, SfdPicInfo *pic, SfdChunk *chunk)
{
    SfdPicGeom *geom = &player->geom;
    SfdMpv *mpv = player->streams.mpv;
    int pts;
    int x, y, z;
    int n;
    if (geom->f16 != 0)
        return 0;
    if (FUN_0028eef0(sj, &pts) != 0)
        return sfd_ReportError(player, 0xFF000F16);
    FUN_0028ef50(sj, &x, &y, &z);
    if (SFD_GetCond(player, 60) == 0)
        mpv->limit = 0;
    else {
        n = FUN_0029e290(player, 1);
        if (z == -1)
            z = x;
        mpv->limit = z < n ? z : n;
    }
    FUN_002a5ef0(player, pts, chunk);
    FUN_002a6010(geom, pts, pic, x);
    return FUN_002a6048(player, geom);
}

void FUN_002a5ef0(SfdPlayer *player, int pts, SfdChunk *chunk)
{
    SfdPicture *picture;
    SfdUserData *user;
    int len;
    SfdTimer *timer;
    picture = FUN_002a82c8(player);
    if (picture == 0 || picture->valid != 0)
        return;
    len = chunk->size;
    user = &picture->user;
    if (len > 512)
        len = 512;
    timer = &player->timer;
    user->size = len;
    FUN_0028b0c0(user->data, chunk->addr, len);
    if (pts == 0x3FFFF) {
        picture->pts = 0;
        picture->hasPts = 0;
    } else {
        picture->hasPts = 1;
        picture->pts = pts * 50;
    }
    picture->stamp = timer->state;
    picture->valid = 1;
}

void FUN_002a6010(SfdPicGeom *geom, int pts, SfdPicInfo *pic, int x) {
    /* matching construct: statement-order sweep — pic->rateIndex is read before the copies */
    int fifth = pic->rateIndex;
    geom->width = pic->width;
    geom->height = pic->height;
    geom->f8 = pic->f8;
    geom->f12 = pic->f12;
    geom->f20 = fifth;
    geom->f16 = pts;
    geom->f32 = x;
}

int FUN_002a6200(SfdPlayer *player) {
    return player->timer.base >= 0;
}

int FUN_002a6210(SfdPlayer *player, SfdChunk *chunk) {
    SfdMpv *mpv = player->streams.mpv;
    SfdPicInfo *pic = &mpv->pic;
    int skip;
    int busy;
    unsigned int type;
    if (SFD_GetCond(player, 47) == 1)
        return 1;
    if (SFD_GetCond(player, 39) == 1)
        return 0;
    if (pic->f88 != 0)
        return mpv->f364;
    type = pic->type;
    busy = FUN_002a6470(player);
    skip = 1;
    if (busy == 0 && FUN_002a64c0(player, type) == 0 && FUN_002a6510(player, type, chunk) == 0
        && FUN_002a6308(player, type) == 0)
        skip = FUN_002a65f0(player, type) != 0;
    FUN_002a6368(player, pic, skip);
    return skip;
}

int FUN_002a6308(SfdPlayer *player, int kind) {
    SfdMpv *mpv = player->streams.mpv;
    unsigned int mode = mpv->f116;
    int result = 0;
    switch (mode) {
    case 4: /* matching construct: manual — explicit empty case shapes the compare tree */
        break;
    case 2:
        if ((unsigned int)(kind - 2) < 2) {
            result = 1;
        }
        break;
    case 3:
        result = kind == mode;
        break;
    }
    return result;
}

void FUN_002a6368(SfdPlayer *player, SfdPicInfo *pic, int kind)
{
    SfdMpv *mpv = player->streams.mpv;
    void *handle = mpv->handle;
    int mode = mpv->f116;
    int a, b;
    if (mpv->f272 != 0) {
        FUN_0028f018(handle, &a, &b);
        if (a == 1)
            mode = 5;
        else {
            if (player->timer.f280.done == 0 && SFD_GetCond(player, 73) == 1)
                b = 1;
            if (b == 1)
                mode = 2;
        }
    }
    if (kind == 1) {
        if (pic->type == 1 || pic->type == 2)
            mode = 2;
    } else if (mode == 2)
        mode = 3;
    else if (mode == 3)
        mode = 5;
    mpv->f116 = mode;
}

int FUN_002a6470(SfdPlayer *player) {
    SfdLink *link = &player->link;
    SfdTimeStamp *cur = &player->timer.cur;
    SfdTimeStamp *f280 = &player->timer.f280;
    if (link->id < 0) {
        return 0;
    }
    if (f280->done != 0) {
        return 0;
    }
    return FUN_00285118(link->id, link->arg, cur->a, cur->b) == 0;
}

int FUN_002a64c0(SfdPlayer *player, unsigned int kind) {
    SfdPending *pending = &player->pending;
    int value;
    switch (kind) {
    case 1:
        value = pending->f8;
        break;
    case 2:
        value = pending->f12;
        break;
    case 3:
        value = pending->f16;
        break;
    default:
        return 1;
    }
    return value == 0;
}

void FUN_002a6768(SfdPlayer *player, int unused, int *first, int *second) {
    SfdPending *pending = &player->pending;
    *second = pending->f172;
    *first = pending->f168;
}

int FUN_002a6780(SfdPlayer *player, int sj)
{
    SfdMpv *mpv = player->streams.mpv;
    void *handle = mpv->handle;
    SfdPicInfo *pic;
    int before;
    int status;
    int used;
    int ret;
    FUN_002a6870(player);
    before = FUN_0027c760(sj, 0, 1);
    pic = &mpv->pic;
    status = FUN_0028ed30(handle, sj);
    used = FUN_0027c760(sj, 0, 1) - before;
    ret = FUN_002a4bc8(player, status, used, 0xFF000F07);
    FUN_002a4b20(player, used);
    if (ret != 0)
        return ret;
    if (pic->f88 == 0)
        mpv->f364 = 1;
    FUN_002abc98(player, 1, pic->type);
    return 0;
}

void FUN_002a6870(SfdPlayer *player) {
    SfdTimeStamp *current = &player->timer.cur;
    SfdTimeStamp *latest = &player->timer.latest;
    if (current->a < player->timer.f280.a) {
        *latest = *current;
    }
}

void FUN_002a6ea0(SfdPlayer *player, SfdMpv *mpv, int *out64, int *out68) {
    if (player->f56 == 3) {
        switch (mpv->pic.type) {
        case 1: /* matching construct: manual — explicit single-layer case shapes the compare tree */
            break;
        case 2:
            *out64 = mpv->first->f64;
            *out68 = mpv->first->f68;
            return;
        case 3:
            *out64 = mpv->first->f64 + mpv->second->f64;
            *out68 = mpv->first->f68 + mpv->second->f68;
            return;
        }
    }
    *out64 = 0;
    *out68 = 0;
}

void FUN_002a6f28(SfdPlayer *player)
{
    SfdTimeStamp *state2 = &player->timer.f280;
    SfdTimeStamp *state = &player->timer.state;
    SfdTimeCode tc;
    int a, b;
    if (state2->done != 0)
        return;
    tc = player->timer.cur.tc;
    if (FUN_002a6308(player, 3) == 0 && FUN_002a64c0(player, 3) == 0)
        tc.add = 0;
    FUN_002af070(&tc, &a, &b);
    state2->tc = tc;
    state2->a = a - state->a;
    state2->b = b;
    state2->done = 1;
}

void FUN_002a7040(SfdPlayer *player, SfdSlot *slot) {
    slot->stamp = player->timer.cur;
    if (FUN_002a96e0(player) != 0) {
        slot->f224 = FUN_002aa040(player);
    }
    FUN_002a70e8(player, slot);
}

void FUN_002a70e8(SfdPlayer *player, SfdSlot *slot) {
    SfdTimer *timer = &player->timer;
    SfdTimeStamp *in = &slot->stamp;
    int t;
    slot->f60 = in->b;
    slot->f56 = in->a - player->timer.f280.a + timer->base;
    slot->f76 = in->a;
    slot->f80 = in->a + timer->base;
    if (FUN_002a96e0(player) != 0) {
        t = UTY_MulDiv(slot->f60, (slot->f224 - timer->f352) * 1000, DAT_004f5060[slot->info.rateIndex]);
        slot->f76 = t;
        slot->f56 = slot->f80 = t + timer->base;
    }
    if (timer->f644 < slot->f56) {
        timer->f644 = slot->f56;
        timer->f648 = slot->f60;
    }
}

void FUN_002a71d0(SfdPlayer *player, SfdSlot *slot, void *source) {
    SfdMpv *mpv = player->streams.mpv;
    int kind;
    char *data;
    int size;
    if ((unsigned int)(slot->info.kind - 1) < 2) {
        FUN_002a73f0(&mpv->pool.slot[1], slot->blob);
    }
    FUN_002a7278(source, &kind, &data, &size);
    if (kind == 3) {
        memcpy(slot->blob->addr, data, size);
        slot->blob->size = size;
    } else {
        FUN_002a73f0(slot->blob, &mpv->pool.slot[1]);
    }
}

void FUN_002a73f0(SfdChunk *dst, SfdChunk *src) {
    memcpy(dst->addr, src->addr, src->size);
    dst->size = src->size;
}

int FUN_002a7438(SfdPlayer *player, int unused, int mask)
{
    SfdRingInfo area;
    int code;
    char *p;
    int n;
    int i;
    int found;
    int c;
    if (FUN_0029dd98(player, player->streams.f16, &area) != 0)
        return 0;
    if (area.len0 == 0)
        return 0;
    p = FUN_002a41a8(&area, mask, &code);
    if (p == 0) {
        n = area.len0 + area.len1 - 3;
        if (n < 0)
            n = 0;
    } else if (p >= area.addr0 && p < area.addr0 + area.len0)
        n = p - area.addr0;
    else if (p >= area.addr1 && p < area.addr1 + area.len1)
        n = p - area.addr1 + area.len0;
    else
        n = 0;
    FUN_002a7598(player, n);
    found = 0;
    for (i = 0; i < (n < 4 ? n : 3); i++) {
        if (i < area.len0)
            c = area.addr0[i];
        else
            c = area.addr1[i - area.len0];
        if (c != 0) {
            found = 1;
            break;
        }
    }
    if (found)
        player->f2472 += n;
    player->f2464 += n;
    return n;
}

/* matching construct: hand search — an empty macro after the call keeps it from being a tail call */
#define EMPTY_MACRO() do { } while (0)
void FUN_002a7598(SfdPlayer *player, int n)
{
    FUN_0029de70(player, player->streams.f16, n);
    EMPTY_MACRO();
}

void FUN_002a75b8(SfdPlayer *player) {
    int entry;
    int a;
    int b;
    FUN_0029e370(player, player->streams.f16, &entry);
    if (entry != 0) {
        FUN_0029eaf8(entry, &a, &b);
        player->f2456 = FUN_0029ecb0(player->f2456, a);
    }
}

int FUN_002a7610(SfdPlayer *player)
{
    SfdMpv *mpv = &player->mpvBody;
    void *dec;
    int ret;
    ret = SFD_GetCond(player, 5);
    if (ret == 0)
        return ret;
    player->streams.mpv = mpv;
    ret = FUN_002a7770(player, mpv);
    if (ret != 0)
        return ret;
    FUN_002a97a0(player);
    dec = FUN_00291048();
    if (dec == 0)
        return sfd_ReportError(0, 0xFF000F0A);
    if (FUN_0028ea48(dec, FUN_002a7b48, player) != 0) {
        FUN_002a7d18(dec);
        return sfd_ReportError(0, 0xFF000F0B);
    }
    FUN_00291250(dec, 1, SFD_GetCond(player, 0));
    FUN_00291250(dec, 2, SFD_GetCond(player, 1));
    FUN_00291250(dec, 6, player->f56);
    mpv->handle = dec;
    if (FUN_002abf68() != 0)
        FUN_002a3558(player, DAT_00585620, DAT_00585624, DAT_00585628);
    return 0;
}

int FUN_002a7968(void) {
    int i;
    if ((unsigned)(DAT_005855b0.count - 1) >= 16) {
fail:
        return -1;
    }
    if (DAT_005855b0.f16 == 0 || DAT_005855b0.f32 == 0) {
        for (i = 0; i < 2; i++) {
            if (DAT_005855d8.w[i] == 0) goto fail;
        }
        for (i = 0; i < DAT_005855b0.count; i++) {
            if (DAT_005855e0.w[i] == 0) goto fail;
        }
    }
    return 0;
}

void FUN_002a7a30(SfdSlot *slot, int *ids, int count) {
    if (count > 0) {
        int *id = ids;
        int remaining = count;
        do {
            slot->state = 0;
            slot->refs = 0;
            FUN_002ae248(&slot->stamp, 0);
            slot->id = *id++;
            slot->f56 = 0;
            slot->f60 = 1;
            slot->f64 = 0;
            slot->f68 = 0;
            slot->f72 = 0;
            slot->f76 = 0;
            slot->f80 = 0;
            FUN_002a7ad0(&slot->info);
            slot->f224 = 0;
            slot++;
        } while (--remaining != 0);
    }
}

void FUN_002a7ad0(SfdSlotInfo *info) {
    FUN_0028b530(info, -1, 32);
}

void FUN_002a7af0(SfdBufPool *pool) {
    int i;
    pool->base = 0;
    pool->count = 0;
    pool->size = 0;
    pool->slot[0].addr = 0;
    pool->slot[0].size = 0;
    pool->slot[1].addr = 0;
    pool->slot[1].size = 0;
    for (i = 0; i < 16; i++) {
        pool->slot[i + 2].addr = 0;
        pool->slot[i + 2].size = 0;
    }
}

void FUN_002a7b48(SfdPlayer *player, int code) {
    if (code < -3 || (code >= -1 && code != 0)) {
        sfd_ReportError(player, code);
    }
}

int FUN_002a7b88(SfdPlayer *player)
{
    SfdMpv *mpv = player->streams.mpv;
    void *dec = mpv->handle;
    if (dec == 0)
        return 0;
    DAT_005855b0 = mpv->cond;
    DAT_005855d8 = mpv->work;
    DAT_005855e0 = mpv->bufs;
    DAT_00585620 = mpv->pool.base;
    DAT_00585624 = mpv->pool.count;
    DAT_00585628 = mpv->pool.size;
    FUN_002a9bc8(player);
    if (FUN_002a7d18(dec) != 0)
        return sfd_ReportError(player, 0xFF000F0C);
    mpv->handle = 0;
    return 0;
}

int FUN_002a7d18(void *handle) {
    return FUN_002911d0(handle);
}

int FUN_002a7d30(void) {
    return 0;
}

int FUN_002a7d38(void) {
    return 0;
}

int FUN_002a7d40(void) {
    return 0;
}

int FUN_002a7d48(void) {
    return 0;
}

void FUN_002a7d50(SfdPlayer *player) {
    sfd_ReportError(player, 0xFF000F0D);
}

void FUN_002a7d70(SfdPlayer *player) {
    sfd_ReportError(player, 0xFF000F0D);
}

int FUN_002a7d90(SfdPlayer *player, SfdFrameInfo **out) {
    int buf[4];
    SfdTimer *timer = &player->timer;
    SfdSlot *slot;
    if (FUN_002a8500(player) == -1) {
        *out = 0;
        return 0;
    }
    slot = FUN_002a86b8(player, buf);
    if (slot == 0) {
        *out = 0;
        return 0;
    }
    FUN_002a7e30(player, slot, out);
    timer->f636 = (*out)->f20;
    timer->f640 = (*out)->f24;
    return 0;
}

int FUN_002a8038(SfdPlayer *player, char *body) {
    char guard[16];
    int result;
    sfd_Lock(guard);
    result = FUN_002a8088(player, body);
    sfd_Unlock(guard);
    return result;
}

int FUN_002a8088(SfdPlayer *player, char *body) {
    SfdMpv *mpv = player->streams.mpv;
    SfdPicRecord *record = FUN_002a8158(player, body);
    SfdSlot *found;
    SfdSlot *current;
    if (record->f0 != 1) {
        return sfd_ReportError(player, 0xFF000F0E);
    }
    found = FUN_002a8440(player, body);
    current = mpv->current;
    if (current != found) {
        return sfd_ReportError(player, 0xFF000F0F);
    }
    record->f0 = 0;
    FUN_002a8668(current);
    return 0;
}

SfdPicRecord *FUN_002a8158(SfdPlayer *player, char *body) {
    return (SfdPicRecord *)(body - 8);
}

int FUN_002a8160(SfdPlayer *player) {
    SfdMpv *mpv = player->streams.mpv;
    int flag[4];
    int ready;
    int status;
    status = FUN_002a81d0(player, mpv, flag);
    if (status != 0) {
        return status;
    }
    ready = flag[0];
    mpv->f116 = 2;
    if (ready == 0 || SFD_GetCond(player, 48) == 0) {
        mpv->state = 192;
    } else {
        mpv->state = 200;
    }
    return 0;
}

int FUN_002a81d0(SfdPlayer *player, SfdMpv *mpv, int *ok)
{
    SfdPicture *picture;
    SfdChunk chunk;
    SfdUserData *user;
    int out[4];
    *ok = 0;
    picture = FUN_002a82c8(player);
    if (picture == 0)
        return 0;
    if (picture->valid == 0)
        return 0;
    player->timer.state = picture->stamp;
    user = &picture->user;
    chunk.addr = user->data;
    chunk.size = user->size;
    if (FUN_0028f360(mpv->handle, &chunk, out) != 0)
        return sfd_ReportError(player, 0xFF000F1B);
    *ok = 1;
    return 0;
}

SfdPicture *FUN_002a82c8(SfdPlayer *player) {
    char *work = player->userWork;
    SfdMpv *mpv = player->streams.mpv;
    if (work == 0) {
        return 0;
    }
    if (mpv->f136 > 0) {
        return 0;
    }
    return (SfdPicture *)(work + 2768);
}

void FUN_002a82f8(SfdPlayer *player, char *body) {
    SfdSlot *slot;
    if (sfd_CheckHn(player) != 0) {
        sfd_ReportError(0, 0xFF000188);
        return;
    }
    slot = FUN_002a8440(player, body);
    if (slot == 0) {
        sfd_ReportError(player, 0xFF000F30);
    } else {
        slot->refs++;
    }
    player->decode.f44++;
}

void FUN_002a8398(SfdPlayer *player, char *body) {
    SfdSlot *slot;
    int count;
    if (sfd_CheckHn(player) != 0) {
        sfd_ReportError(0, 0xFF000189);
    } else {
        slot = FUN_002a8440(player, body);
        if (slot == 0) {
            sfd_ReportError(player, 0xFF000F31);
        } else {
            count = slot->refs - 1;
            slot->refs = count < 0 ? 0 : count;
        }
        player->decode.f44--;
    }
}

SfdSlot *FUN_002a8440(SfdPlayer *player, char *body) {
    SfdPicRecord *record = player->records;
    SfdMpv *mpv = player->streams.mpv;
    SfdSlot *slot = mpv->slots;
    int i;
    for (i = 0; i < 16; i++) {
        if (record->body == body) {
            return slot;
        }
        record++;
        slot++;
    }
    return 0;
}

SfdPicRecord *FUN_002a8488(SfdPlayer *player, SfdSlot *target) {
    SfdMpv *mpv = player->streams.mpv;
    int i = 0;
    int count = mpv->slotCount;
    SfdSlot *slot = mpv->slots;
    SfdPicRecord *record;
    if (count > 0) {
        record = player->records;
        do {
            /* matching construct: hand — the candidate is taken before the
               advance, so the compare sits in the copy's delay slot */
            SfdPicRecord *found = record;
            record++;
            if (slot == target) {
                return found;
            }
            i++;
            slot++;
        } while (i < count);
    }
    return 0;
}

void FUN_002a84d0(SfdPlayer *player) {
    SfdMpv *mpv = player->streams.mpv;
    mpv->f124 = 1;
}

int FUN_002a84e0(SfdPlayer *player) {
    SfdMpv *mpv = player->streams.mpv;
    return mpv->f124;
}

SfdMpv *FUN_002a84f0(SfdPlayer *player, int value) {
    SfdMpv *mpv = player->streams.mpv;
    mpv->f128 = value;
    return mpv;
}

int FUN_002a8500(SfdPlayer *player) {
    char guard[16];
    SfdMpv *mpv;
    SfdSlot *slot;
    int count;
    int i;
    int n;
    sfd_Lock(guard);
    mpv = player->streams.mpv;
    count = 0;
    slot = mpv->slots;
    n = mpv->slotCount;
    for (i = 0; i < n; i++) {
        if (slot->state == 2 || slot->state == 4) {
            count++;
        }
        slot++;
    }
    if (mpv->f124 == 1 && count == 0) {
        count = -1;
    }
    sfd_Unlock(guard);
    return count;
}

void FUN_002a8628(SfdSlot *slot) {
    if (slot != 0) {
        slot->state = 0;
    }
}

void FUN_002a8638(SfdSlot *slot) {
    if (slot != 0) {
        slot->state = 2;
    }
}

void FUN_002a8650(SfdSlot *slot) {
    if (slot != 0) {
        slot->state = 4;
    }
}

void FUN_002a8668(SfdSlot *slot) {
    if (slot != 0) {
        if (slot->state == 4) {
            slot->state = 3;
        } else {
            slot->state = 0;
        }
    }
}

void FUN_002a8690(SfdSlot *slot) {
    if (slot != 0) {
        if (slot->state == 4) {
            slot->state = 2;
        } else {
            slot->state = 0;
        }
    }
}

SfdSlot *FUN_002a86b8(SfdPlayer *player, int *out) {
    int c;
    SfdSlot *best = 0;
    int n = 0;
    SfdMpv *mpv;
    SfdSlot *slot;
    int i, cnt;
    sfd_Lock(&c);
    mpv = player->streams.mpv;
    cnt = mpv->slotCount;
    slot = mpv->slots;
    *out = 0;
    for (i = 0; i < cnt; i++, slot++) {
        if (slot->state == 2 || slot->state == 4) {
            if (FUN_002a8b30(best, slot) != 0) best = slot;
            n++;
        }
    }
    if (n == 1 && mpv->f124 != 0) *out = n;
    sfd_Unlock(&c);
    return best;
}

int FUN_002a8800(SfdPlayer *player) {
    int refused;
    int count;
    refused = sfd_CheckHn(player);
    if (refused != 0) {
        sfd_ReportError(0, 0xFF000187);
        return 0;
    }
    count = FUN_002a8878(player);
    if (player->decode.f24 == 1 && count > 0) {
        count--;
    }
    return count;
}

int FUN_002a8878(SfdPlayer *player) {
    int c;
    SfdSlot *p, *q;
    int k, r;
    sfd_Lock(&c);
    FUN_002a8a30(player, &p, &q);
    if (player->f72 != 4) q = 0;
    k = SFD_GetCond(player, 15);
    if (p != 0 && (k == 0 || FUN_002af6c0(player, p->f56, p->f60) != 0)) {
        if (q != 0 && (k == 0 || FUN_002af6c0(player, q->f56, q->f60) != 0)) {
            r = 2;
        } else {
            r = 1;
        }
    } else {
        r = 0;
    }
    sfd_Unlock(&c);
    return r;
}

int FUN_002a8940(SfdPlayer *player) {
    if (sfd_CheckHn(player) != 0) {
        sfd_ReportError(0, 0xFF000183);
        return 0;
    }
    return FUN_002a8998(player) != 0;
}

SfdSlot *FUN_002a8998(SfdPlayer *player) {
    int guard;
    SfdSlot *best;
    SfdSlot *second;
    sfd_Lock(&guard);
    if (player->f72 != 4) {
        second = 0;
    } else {
        FUN_002a8a30(player, &best, &second);
        if (second != 0 && SFD_GetCond(player, 15) != 0) {
            if (FUN_002af6c0(player, second->f56, second->f60) == 0) {
                second = 0;
            }
        }
    }
    sfd_Unlock(&guard);
    return second;
}

/* matching construct: manual — out-parameters and the context link are void * (same alias set), which keeps the clearing stores after the context load */
void FUN_002a8a30(SfdPlayer *player, void **best, void **second) {
    SfdMpv *mpv;
    SfdSlot *slot;
    int held = 0;
    int i;
    int n;
    mpv = player->streams.mpv;
    *best = 0;
    *second = 0;
    n = mpv->slotCount;
    slot = mpv->slots;
    for (i = 0; i < n; i++) {
        if (slot->state == 2 || slot->state == 4) {
            held++;
            if (FUN_002a8b30(*best, slot) != 0) {
                *second = *best;
                *best = slot;
            } else if (FUN_002a8b30(*second, slot) != 0) {
                *second = slot;
            }
        }
        slot++;
    }
    if (held <= 0) {
        *best = 0;
        *second = 0;
    } else if (held == 1) {
        *second = 0;
    }
}

int FUN_002a8b30(SfdSlot *a, SfdSlot *b) {
    int result;
    result = 1;
    if (a != 0) {
        result = a->f56 > b->f56;
    }
    return result;
}
