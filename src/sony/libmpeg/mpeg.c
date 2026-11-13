/* libmpeg's public calls: setting up a stream over its work area, feeding it data, decoding pictures
   into the caller's buffer, and the callbacks; with the work-area allocator and the decode loop. */
#include "dw4/sony/libmpeg.h"
#include "dw4/eekernel_gp.h"

/* The DMA controller's suspend bit (D_ENABLEW), a channel's start bit (Dn_CHCR), the IPU's reset bit (IPU_CTRL). */
#define D_ENABLE_SUSPEND 0x10000
#define CHCR_STR 0x100
#define IPU_CTRL_RST 0x40000000

#define I_TYPE 1
#define P_TYPE 2
#define B_TYPE 3
#define D_TYPE 4

#define SPR 0x70000000

int DIntr(void);
int EIntr(void);
int scePrintf(const char *format, ...);
void *memset(void *dst, int value, unsigned int size);
void sceIpuInit(void);
void sceIpuSync(int mode, int timeout);
void _ipuSetMpeg1(int mpeg1);
int _sceMpegNextHeader(_sceMpegDecoder *dec);
int _decPicture(_sceMpegDecoder *dec);
int _updateRefImage(_sceMpegDecoder *dec, int second);
void _sceMpegOutputFrame(_sceMpegDecoder *dec, int count, int output);
int _sendDataToIPU(_sceMpegDecoder *dec, unsigned char *data, int size);
int _sceMpegDefaultStopDMA(sceMpeg *mp, sceMpegCbData *cbdata, void *anyData);
int _sceMpegDefaultRestartDMA(sceMpeg *mp, sceMpegCbData *cbdata, void *anyData);
int sceMpegReset(sceMpeg *mp);
int sceMpegClearRefBuff(sceMpeg *mp);
void _sceMpegAlalcInit(_sceMpegAlalc *alalc, char *start, int size);
void _sceMpegAlalcSetDynamic(_sceMpegAlalc *alalc);
int _getpic(sceMpeg *mp);
int _decodeOrSkip(sceMpeg *mp, int count, int limit);
int _decodeOrSkipFrame(sceMpeg *mp, int count, int limit);
int _decodeOrSkipField(sceMpeg *mp, int count, int limit);
int _sceMpegFlush(sceMpeg *mp);
void _setMpeg1(_sceMpegDecoder *dec);
void _initSpr(_sceMpegDecoder *dec);
void _clearEach(_sceMpegDecoder *dec);

/* Stops the IPU's two DMA channels with the DMA controller suspended, then sets up libipu. */
int sceMpegInit(void)
{
    int intr = DIntr();

    *(volatile unsigned int *)0x1000F590 = *(volatile unsigned int *)0x1000F520 | D_ENABLE_SUSPEND;
    *(volatile unsigned int *)0x1000B000 &= ~CHCR_STR;    /* D3_CHCR: IPU_FROM */
    *(volatile unsigned int *)0x1000B400 &= ~CHCR_STR;    /* D4_CHCR: IPU_TO */
    *(volatile unsigned int *)0x1000F590 = *(volatile unsigned int *)0x1000F520 & ~D_ENABLE_SUSPEND;
    if (intr) {
        EIntr();
    }
    *(volatile unsigned int *)0x1000B020 = 0;             /* D3_QWC */
    *(volatile unsigned int *)0x1000B420 = 0;             /* D4_QWC */
    sceIpuInit();
    return 1;
}

/* Lays the decoder out at the start of the work area and gives the rest to its allocator. */
int sceMpegCreate(sceMpeg *mp, unsigned char *work_area, int work_area_size)
{
    _sceMpegDecoder *dec;
    int size;

    memset(work_area, 0, work_area_size);
    dec = (_sceMpegDecoder *)(((unsigned int)work_area + 3) / 4 * 4);
    size = work_area_size - ((unsigned char *)dec - work_area);
    if ((unsigned int)size < sizeof(_sceMpegDecoder)) {
        _sceMpegError(dec, "The size of work area is too small");
        return 0;
    }
    mp->sys = dec;
    _sceMpegAlalcInit(&dec->alalc, (char *)dec + sizeof(_sceMpegDecoder), size - sizeof(_sceMpegDecoder));

    mp->width = 0;
    mp->height = 0;
    mp->frameCount = 0;
    mp->pts = -1;
    mp->dts = -1;
    mp->flags = 0;
    mp->pts2nd = -1;
    mp->dts2nd = -1;
    mp->flags2nd = 0;

    dec->center_offsets[0] = 0;
    dec->center_offsets[1] = 0;
    dec->center_offsets[2] = 0;
    dec->center_offsets[3] = 0;
    dec->center_offsets[4] = 0;
    dec->center_offsets[5] = 0;
    dec->disp_width = 0;
    dec->disp_height = 0;
    dec->first_picture_structure = 0;
    dec->image_buff = 0;
    dec->image_width = 0;
    dec->image_height = 0;
    dec->image_size = 0;
    dec->set_broken_link = 0;
    dec->ptm_state = 0;
    dec->ptm = -1;

    dec->callbacks[sceMpegCbError].func = 0;
    dec->callbacks[sceMpegCbNodata].func = 0;
    dec->callbacks[sceMpegCbStopDMA].func = _sceMpegDefaultStopDMA;
    dec->callbacks[sceMpegCbRestartDMA].func = _sceMpegDefaultRestartDMA;
    dec->callbacks[sceMpegCbBackground].func = 0;
    dec->callbacks[sceMpegCbTimeStamp].func = 0;
    dec->callbacks[sceMpegCbStr].func = 0;

    dec->spare_buffer = _sceMpegAlalcAlloc(dec, &dec->alalc, 2048, 8);
    dec->spare = 0;
    dec->frame_buffers[0] = 0;
    dec->frame_buffers[1] = 0;
    dec->frame_buffers[2] = 0;
    dec->has_pts_gap = 0;
    dec->pts_gap = 0;
    dec->last_pts = -1;
    dec->field_count = 0;
    dec->half_field = 0;
    dec->first_frame_no = 0;
    dec->ni = -1;
    dec->np = -1;
    dec->nb = -1;
    dec->mp = mp;
    dec->rgb32 = 1;
    _initSpr(dec);
    sceMpegReset(mp);
    sceMpegClearRefBuff(mp);

    dec->slots[0].ref_image = &dec->pictures[0];
    dec->slots[0].prev_image = &dec->pictures[1];
    dec->slots[0].image = &dec->pictures[2];
    dec->slots[1].ref_image = &dec->pictures[3];
    dec->slots[1].prev_image = &dec->pictures[4];
    dec->slots[1].image = &dec->pictures[5];
    dec->slots[2].ref_image = &dec->pictures[6];
    dec->slots[2].prev_image = &dec->pictures[7];
    dec->slots[2].image = &dec->pictures[8];
    _sceMpegAlalcSetDynamic(&dec->alalc);

    dec->temporal_max = -1;
    dec->gop_started = 0;
    dec->temporal_base = 0;
    dec->mc_work = SPR + 0x3600;
    return 1;
}

int sceMpegDelete(sceMpeg *mp)
{
    return 1;
}

/* The IPU reads whole quadwords: the size is rounded up to them. */
int sceMpegAddBs(sceMpeg *mp, unsigned char *bs, int size)
{
    _sendDataToIPU(mp->sys, bs, (size + 19) / 16 * 16);
    return 1;
}

/* Decodes the next picture into the buffer as RGB32. */
int sceMpegGetPicture(sceMpeg *mp, unsigned int image, int image_size)
{
    _sceMpegDecoder *dec = mp->sys;

    image = (image & 0x0FFFFFFF) | 0x20000000;
    dec->rgb32 = 1;
    dec->image_buff = image;
    dec->image_size = image_size;
    dec->image_height = 0;
    dec->image_width = 0;
    return _getpic(mp);
}

/* Decodes the next picture into the buffer as raw 8-bit macroblocks. */
int sceMpegGetPictureRAW8(sceMpeg *mp, unsigned int image, int image_size)
{
    _sceMpegDecoder *dec = mp->sys;

    image = (image & 0x0FFFFFFF) | 0x20000000;
    dec->image_size = image_size;
    dec->image_buff = image;
    dec->rgb32 = 0;
    dec->image_height = 0;
    dec->image_width = 0;
    return _getpic(mp);
}

/* As sceMpegGetPictureRAW8, into a buffer of the given size in macroblocks. */
int sceMpegGetPictureRAW8xy(sceMpeg *mp, unsigned int image, int mb_width, int mb_height)
{
    _sceMpegDecoder *dec = mp->sys;

    image = (image & 0x0FFFFFFF) | 0x20000000;
    dec->image_buff = image;
    dec->image_height = mb_height << 4;
    dec->image_size = mb_width * mb_height;
    dec->image_width = mb_width << 4;
    dec->rgb32 = 0;
    return _getpic(mp);
}

/* _getpic and the IPU waits stop at the flag; the stream must be set up again after it. */
void sceMpegGetPictureAbort(sceMpeg *mp)
{
    mp->sys->abort = 1;
}

void sceMpegSetDecodeMode(sceMpeg *mp, int ni, int np, int nb)
{
    _sceMpegDecoder *dec = mp->sys;

    dec->ni = ni;
    dec->np = np;
    dec->nb = nb;
}

void sceMpegGetDecodeMode(sceMpeg *mp, int *ni, int *np, int *nb)
{
    _sceMpegDecoder *dec = mp->sys;

    *ni = dec->ni;
    *np = dec->np;
    *nb = dec->nb;
}

int sceMpegIsEnd(sceMpeg *mp)
{
    return mp->sys->is_end;
}

int sceMpegIsRefBuffEmpty(sceMpeg *mp)
{
    return mp->sys->ref_count == 0;
}

int sceMpegReset(sceMpeg *mp)
{
    _sceMpegDecoder *dec = mp->sys;

    dec->abort = 0;
    dec->is_end = 0;
    dec->ref_count = 0;
    dec->seq_state = 0;
    mp->frameCount = 0;
    dec->first_frame_no = 0;
    dec->last_pts = -1;
    _clearEach(dec);
    dec->frame_no = 0;
    _setMpeg1(dec);
    return 1;
}

/* Marks the reference pictures of every picture structure as not decoded. */
int sceMpegClearRefBuff(sceMpeg *mp)
{
    _sceMpegDecoder *dec = mp->sys;

    if (dec->slots[0].ref_image) {
        dec->slots[0].ref_image->decoded = 0;
    }
    if (dec->slots[1].ref_image) {
        dec->slots[1].ref_image->decoded = 0;
    }
    if (dec->slots[2].ref_image) {
        dec->slots[2].ref_image->decoded = 0;
    }
    if (dec->slots[0].prev_image) {
        dec->slots[0].prev_image->decoded = 0;
    }
    if (dec->slots[1].prev_image) {
        dec->slots[1].prev_image->decoded = 0;
    }
    if (dec->slots[2].prev_image) {
        dec->slots[2].prev_image->decoded = 0;
    }
    return 1;
}

/* Registers the callback with the caller's $gp, which the dispatch restores around the call. */
sceMpegCallback sceMpegAddCallback(sceMpeg *mp, sceMpegCbType type, sceMpegCallback callback, void *anyData)
{
    _sceMpegDecoder *dec = mp->sys;
    sceMpegCallback old = dec->callbacks[type].func;

    dec->callbacks[type].func = callback;
    dec->callbacks[type].data = anyData;
    dec->callbacks[type].gp = GetGp();
    return old;
}

/* Calls the stream's callback for the record's type under the $gp it was registered with. */
int _sceMpegDispatchMpegCallback(sceMpeg *mp, sceMpegCbData *cbdata)
{
    _sceMpegDecoder *dec;
    sceMpegCallback callback;
    void *gp;
    int result = 0;

    if (mp != 0 && (dec = mp->sys) != 0) {
        callback = dec->callbacks[cbdata->type].func;
        if (callback != 0) {
            gp = SetGp(dec->callbacks[cbdata->type].gp);
            result = callback(mp, cbdata, dec->callbacks[cbdata->type].data);
            __asm__("move $28, %0" : : "r"(gp));
        }
    }
    return result;
}

int _sceMpegDispatchMpegCbNodata(sceMpeg *mp)
{
    sceMpegCbData cbdata;

    cbdata.type = sceMpegCbNodata;
    _sceMpegDispatchMpegCallback(mp, &cbdata);
    return 1;
}

/* The pts gap added for each displayed field when the stream gives no pts. */
int sceMpegSetDefaultPtsGap(sceMpeg *mp, long pts_gap)
{
    _sceMpegDecoder *dec = mp->sys;

    dec->has_pts_gap = 1;
    dec->pts_gap = pts_gap;
    return 1;
}

int sceMpegResetDefaultPtsGap(sceMpeg *mp)
{
    _sceMpegDecoder *dec = mp->sys;

    dec->has_pts_gap = 0;
    dec->pts_gap = 0;
    return 1;
}

int sceMpegSetImageBuff(sceMpeg *mp, void *image_buff)
{
    mp->sys->image_buff = (unsigned int)image_buff;
    return 1;
}

int sceMpegDispWidth(sceMpeg *mp)
{
    return mp->sys->disp_width;
}

int sceMpegDispHeight(sceMpeg *mp)
{
    return mp->sys->disp_height;
}

int *sceMpegDispCenterOffX(sceMpeg *mp)
{
    return mp->sys->center_offsets;
}

int *sceMpegDispCenterOffY(sceMpeg *mp)
{
    return mp->sys->center_offsets;
}

int _sceMpegSetBrokenLink(sceMpeg *mp, int set_broken_link)
{
    _sceMpegDecoder *dec = mp->sys;
    int old = dec->set_broken_link;

    dec->set_broken_link = set_broken_link;
    return old;
}

int _sceMpegSetPtm(sceMpeg *mp, long ptm)
{
    _sceMpegDecoder *dec = mp->sys;

    dec->ptm = ptm;
    dec->ptm_state = 1;
    return 1;
}

void _sceMpegAlalcInit(_sceMpegAlalc *alalc, char *start, int size)
{
    alalc->size = size;
    alalc->start = start;
    alalc->cur = start;
    alalc->dynamic = start;
}

/* Allocations made after this are the stream's own, released by _sceMpegAlalcFree. */
void _sceMpegAlalcSetDynamic(_sceMpegAlalc *alalc)
{
    alalc->dynamic = alalc->cur;
}

void _sceMpegAlalcFree(_sceMpegAlalc *alalc)
{
    alalc->cur = alalc->dynamic;
}

char *_sceMpegAlalcAlloc(_sceMpegDecoder *dec, _sceMpegAlalc *alalc, int size, unsigned int align)
{
    char *p = (char *)(((unsigned int)alalc->cur + align - 1) / align * align);
    char *end = p + size;

    if (alalc->start + alalc->size >= end) {
        alalc->cur = end;
        return p;
    }
    _sceMpegError(dec, "work area size is too small");
    return 0;
}

/* The bytes left to allocate. */
int _sceMpegAlalcReset(_sceMpegAlalc *alalc)
{
    return alalc->start + alalc->size - alalc->cur;
}

/* Decodes or skips pictures until one is output, the stream ends, or the stream asks to stop. */
int _getpic(sceMpeg *mp)
{
    _sceMpegDecoder *dec = mp->sys;
    int result = 0;
    int type = 1;

    dec->is_end = 0;
    if (dec->image_buff & 0x3F) {
        _sceMpegError1(dec, "image buffer needs to be aligned to 64byte boundary(0x%08x)", dec->image_buff);
        return -1;
    }
    if (dec->abort) {
        scePrintf("Need to re-setup libipu since sceMpegGetPicture was aborted\n");
        return -1;
    }
    dec->stopped = 0;
    do {
        if (result != -1) {
            do {
                type = _sceMpegNextHeader(dec);
                if (type < 0) {
                    return -1;
                }
                if (type == 0) {
                    break;
                }
                if (dec->picture_structure == dec->first_picture_structure) {
                    break;
                }
            } while (dec->mpeg2);
        }
        switch (type) {
        case 0:
            _sceMpegFlush(mp);
            dec->is_end = 1;
            break;
        case I_TYPE:
            dec->count_b = 0;
            dec->count_p = 0;
            dec->count_i = 0;
            result = _decodeOrSkip(mp, 0, dec->ni);
            dec->count_i++;
            break;
        case P_TYPE:
            result = _decodeOrSkip(mp, dec->count_p, dec->np);
            dec->count_p++;
            break;
        case B_TYPE:
        case D_TYPE:
            result = _decodeOrSkip(mp, dec->count_b, dec->nb);
            dec->count_b++;
            break;
        }
        if (dec->abort) {
            scePrintf("sceMpegGetPicture is aborted\n");
            return -1;
        }
        if (dec->stopped) {
            return 1;
        }
    } while (dec->is_end == 0);
    return 1;
}

/* A frame picture: decoded while fewer than limit of its type have been, else only its reference
   pictures move on. */
int _decodeOrSkipFrame(sceMpeg *mp, int count, int limit)
{
    _sceMpegDecoder *dec = mp->sys;
    int skipped = 0;
    int result;

    if (limit == -1 || count < limit) {
        if (dec->seq_state == 0) {
            mp->frameCount = 0;
            dec->seq_state = 1;
        }
        result = _updateRefImage(dec, 0);
        result = result && _decPicture(dec);
    } else {
        result = _updateRefImage(dec, 0);
        skipped = 1;
        _sceMpegDispatchMpegCbNodata(mp);
    }
    if (dec->abort) {
        return 0;
    }
    _sceMpegOutputFrame(dec, dec->frame_no, dec->ref_count);
    if (dec->picture_structure != MPEG_FRAME_PICTURE && !skipped) {
        dec->second_field = !dec->second_field;
    }
    mp->frameCount = dec->frame_no - dec->first_frame_no;
    if (dec->second_field == 0) {
        dec->frame_no++;
        dec->ref_count++;
    }
    return result;
}

int _decodeOrSkip(sceMpeg *mp, int count, int limit)
{
    if (mp->sys->picture_structure != MPEG_FRAME_PICTURE) {
        return _decodeOrSkipField(mp, count, limit);
    }
    return _decodeOrSkipFrame(mp, count, limit);
}

/* A field picture: decodes it and the field that must follow it as one frame. */
int _decodeOrSkipField(sceMpeg *mp, int count, int limit)
{
    _sceMpegDecoder *dec = mp->sys;
    int decode = 0;
    int result;
    int updated;
    int second;

    dec->second_field = 0;
    if (limit == -1 || count < limit) {
        decode = 1;
    }
    if (dec->seq_state == 0) {
        mp->frameCount = 0;
        dec->seq_state = 1;
    }
    if (_updateRefImage(dec, 0) && decode) {
        _decPicture(dec);
    }
    if (dec->abort) {
        return 0;
    }
    dec->second_field = 1;
    if (!_sceMpegNextHeader(dec)) {
        _sceMpegFlush(mp);
        dec->is_end = 1;
        return 0;
    }
    second = MPEG_TOP_FIELD;
    if (dec->first_picture_structure == MPEG_TOP_FIELD) {
        second = MPEG_BOTTOM_FIELD;
    }
    if (dec->picture_structure != second) {
        return -1;
    }
    updated = 0;
    if (_updateRefImage(dec, 1)) {
        updated = 1;
    }
    result = 0;
    if (updated && decode && _decPicture(dec)) {
        result = 1;
    }
    if (dec->abort) {
        return 0;
    }
    _sceMpegOutputFrame(dec, dec->frame_no, dec->ref_count);
    dec->second_field = 0;
    mp->frameCount = dec->frame_no - dec->first_frame_no;
    dec->frame_no++;
    dec->ref_count++;
    if (!decode) {
        _sceMpegDispatchMpegCbNodata(mp);
    }
    return result;
}

/* At the end of the stream, outputs the picture still held. */
int _sceMpegFlush(sceMpeg *mp)
{
    _sceMpegDecoder *dec = mp->sys;
    int flushed = 0;

    if (dec->ref_count != 0 && dec->seq_state != 0) {
        _flushLastPicture(dec);
        flushed = 1;
        mp->frameCount = dec->frame_no - dec->first_frame_no;
        dec->ref_count = 0;
    }
    return flushed;
}

void _setMpeg1(_sceMpegDecoder *dec)
{
    dec->mpeg2 = 0;
    _ipuSetMpeg1(1);
}

void _flushLastPicture(_sceMpegDecoder *dec)
{
    int frame_no = dec->frame_no;

    if (dec->second_field) {
        _sceMpegError(dec, "the second field is missing");
    } else if (dec->picture_structure == MPEG_FRAME_PICTURE) {
        _outputFrame(dec, dec->slots[0].prev_image, frame_no - 1);
    } else {
        _outputFieldPair(dec, dec->slots[1].prev_image, dec->slots[2].prev_image, frame_no - 1);
    }
    dec->second_field = 0;
}

/* The two scratchpad halves macroblocks are decoded through. */
void _initSpr(_sceMpegDecoder *dec)
{
    unsigned int spr = SPR;

    _ipuSetMpeg1(1);
    dec->spr[0].src = spr;
    dec->spr[0].dst = spr + 0x1800;
    dec->spr[1].src = spr + 0x1B00;
    dec->spr[1].dst = spr + 0x3300;
    dec->mb_buffer = 0;
}

/* Stops the IPU's DMA channels and the scratchpad channel, then resets the IPU. */
void _clearEach(_sceMpegDecoder *dec)
{
    int intr;

    dec->ipu_cmd_pending = 1;
    dec->dc_reset = 0;
    intr = DIntr();
    *(volatile unsigned int *)0x1000F590 = *(volatile unsigned int *)0x1000F520 | D_ENABLE_SUSPEND;
    *(volatile unsigned int *)0x1000B000 = 0;             /* D3_CHCR: IPU_FROM */
    *(volatile unsigned int *)0x1000B400 = 0;             /* D4_CHCR: IPU_TO */
    *(volatile unsigned int *)0x1000D400 = 0;             /* D9_CHCR: toSPR */
    *(volatile unsigned int *)0x1000F590 = *(volatile unsigned int *)0x1000F520 & ~D_ENABLE_SUSPEND;
    if (intr) {
        EIntr();
    }
    *(volatile unsigned int *)0x1000B020 = 0;             /* D3_QWC */
    *(volatile unsigned int *)0x1000B420 = 0;             /* D4_QWC */
    *(volatile unsigned int *)0x1000D420 = 0;             /* D9_QWC */
    *(volatile unsigned int *)0x10002010 = IPU_CTRL_RST;  /* IPU_CTRL */
    sceIpuSync(0, 0);
}
