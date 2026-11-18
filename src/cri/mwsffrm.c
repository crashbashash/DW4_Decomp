/* MWSFFRM: the MWSFD player's frame side. Frame sync, the frame handed out by mwPlyGetCurFrm and its
 * release, the picture types and plane layout converted between SFD and MWSFD, the picture user
 * data, and the per-picture log ring the SFD's picture callback fills. */
#include "dw4/cri/mwply.h"
#include "dw4/cri/sfh.h"
#include "dw4/cri/sfmpv.h"
#include <string.h>
#include "dw4/cri/uty.h"
#include "dw4/cri/sud.h"
#include "dw4/cri/cri_mwsfd.h"
#include "dw4/cri/sfd.h"

#define SFD_STM_VIDEO 224
#define SFD_CB_PICUSR 0x4B    /* the picture user data callback */
#define SFD_CB_PICUSR_OBJ 0x4C

extern char E1122614_mwPlyGetCurFrm_inv_hn[]; /* "E1122614: mwPlyGetCurFrm: handle is invalid." */
extern char E201301_mwply_SetFrmInf_GetFps_failed[]; /* "E201301: MWSFD: GetFps failed." */
extern char E1122629_mwPlySetFrmSync_inv_hn[]; /* "E1122629: mwPlySetFrmSync: handle is invalid." */
extern char E2010801_mwPlyGetFrmSync_inv_hn[]; /* "E2010801: mwPlyGetFrmSync: handle is invalid." */
extern char mwl_convPtypeFromSFD_Invalid_Ptype[]; /* "mwl_convPtypeFromSFD : Invalid Ptype" */
extern char E301271_mwsffrm_DecideFrmType_Invalid_Pstruct[]; /* "E301271: mwsffrm_DecideFrmType() : Invalid Pstruct" */
extern char mwl_convPtypeToSFD_Invalid_Ptype[]; /* "mwl_convPtypeToSFD : Invalid Ptype" */
extern char E1122615_mwPlyRelCurFrm_inv_hn[]; /* "E1122615: mwPlyRelCurFrm: handle is invalid." */
extern char E1122618_mwPlyIsNextFrmReady_inv_hn[]; /* "E1122618: mwPlyIsNextFrmReady: handle is invalid." */
extern char E3122201_mwPlyGetNextPicUsr_inv_hn[]; /* "E3122201: mwPlyGetNextPicUsr: handle is invalid." */
extern char E202231_mwPlyGetNumSkipDisp_inv_hn[]; /* "E202231: mwPlyGetNumSkipDisp: handle is invalid." */
extern char E409171_mwPlyGetNumRemainFrm_inv_hn[]; /* "E409171: mwPlyGetNumRemainFrm: handle is invalid." */

void mwply_UpdateUsrLen(MwsfdPly *ply, MwsfdFrm *frm);
void mwply_SetFrmInf(MwsfdPly *ply, SfdFrameInfo *frm, MwsfdFrm *out);
void mwply_GetFrmUsrData(MwsfdPly *ply, SfdFrameInfo *frm, MwsfdFrm *out);
int mwply_MulDivMs(int time, int fps, int tunit);

int MWSFD_GetFrmSync(MwsfdPly *ply);
int MWSFD_IsEnablePicUsr(MwsfdPly *ply);
void mwl_convYccPlaneFromSFD(SfdPlanes *src, MwsfdPlanes *dst);
int mwl_convBufFmtToSFD(unsigned int ptype);
int mwl_convPtypeToSFD(unsigned int ptype);
int mwply_GetCurPicHdrInfo(MwsfdPly *ply);
int mwsffrm_AnalyTotalFrm(SfhHn *hdr);
int mwply_GetMuxKind1(SfhHn *hdr);
int mwply_GetMuxKind2(SfhHn *hdr);
int mwply_GetPicCompoMode(SfhHn *hdr);
int mwply_IsPicItemType3(SfhHn *hdr);
void mwply_LogPic(MwsfdPly *ply, char *buf, unsigned int size);
int mwply_GetLogItemTypeThree(MwsfdPly *ply, int slot);
int mwply_GetLogHdrInfo(MwsfdPly *ply, int slot);
int mwply_GetLogCompoMode(MwsfdPly *ply, int slot);
int mwply_GetCurPicCompoMode(MwsfdPly *ply);
void mwply_SetPicInf(MwsfdPly *ply, SfdFrameInfo *frm);
void mwply_UpdatePicUsrData(MwsfdPly *ply, SfdFrameInfo *frm);
void mwply_ApplyItemType3(MwsfdPly *ply);
int mwply_IsCurPicItemTypeThree(MwsfdPly *ply);
int mwPlyIsNextFrmReady(MwsfdPly *ply);
int mwl_convBufFmtFromSFD(unsigned int ptype);
int mwl_convPtypeFromSFD(unsigned int ptype);
int mwsffrm_DecideFrmType(MwsfdPly *ply, SfdFrameInfo *frm);

void mwPlySetFrmSync(MwsfdPly *ply, int frmSync)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error(E1122629_mwPlySetFrmSync_inv_hn);
        return;
    }
    ply->frmSync = frmSync;
}

int mwPlyGetFrmSync(MwsfdPly *ply)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error(E2010801_mwPlyGetFrmSync_inv_hn);
        return 0;
    }
    return MWSFD_GetFrmSync(ply);
}

int MWSFD_GetFrmSync(MwsfdPly *ply)
{
    return ply->frmSync;
}

/* hands out the current frame in out, catching up first when the sync is off (frmSync 0): frames
 * past the pool size that are already waiting are released and counted as skipped */
void mwPlyGetCurFrm(MwsfdPly *ply, MwsfdFrm *out)
{
    void *sfd;
    void *frm;
    int i;
    int skip;

    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error(E1122614_mwPlyGetCurFrm_inv_hn);
        out->bufadr = 0;
        return;
    }
    sfd = mwPlyGetSfdHn(ply);
    SFD_GetFrm(sfd, &frm);
    if (frm != 0) {
        if (ply->frmSync == 0) {
            i = 0;
            skip = ply->cre.nfrmPoolWk;
            do {
                if (i >= skip)
                    break;
                i++;
                if (mwPlyIsNextFrmReady(ply) != 1)
                    break;
                SFD_RelFrm(sfd, frm);
                ply->numSkipDisp++;
                SFD_GetFrm(sfd, &frm);
            } while (1);
        }
        if (frm != 0) {
            ply->limit++;
            ply->curFrm = frm;
            mwply_SetPicInf(ply, frm);
            mwply_SetFrmInf(ply, frm, out);
            mwply_UpdatePicUsrData(ply, frm);
            mwply_UpdateUsrLen(ply, out);
            mwply_ApplyItemType3(ply);
            out->frmType = mwsffrm_DecideFrmType(ply, frm);
            ply->logPos = out->concat_cnt;
            MWSFSFX_SetFxType(ply, mwply_GetCurPicCompoMode(ply));
            return;
        }
    }
    out->bufadr = 0;
}

/* takes the frame's concatenation count, letting mwsfsfx_UpdateAddInf act first when it grows */
void mwply_UpdateUsrLen(MwsfdPly *ply, MwsfdFrm *frm)
{
    if (ply->usrBuf.concatCnt < frm->concat_cnt) {
        mwsfsfx_UpdateAddInf(ply);
    }
    ply->usrBuf.concatCnt = frm->concat_cnt;
}

void mwply_ApplyItemType3(MwsfdPly *ply)
{
    int on = 1; /* matching construct: manual — retail keeps this 1 in a saved register */
    int flag;
    int has;

    flag = mwply_IsCurPicItemTypeThree(ply) == on;
    has = MWSFD_IsEnablePicUsr(ply);
    if (has == on) {
        flag = MWSFSFX_IsFrmCcs(ply) == has;
    }
    MWSFD_SetColAdj(ply, flag);
}

/* converts the SFD frame into the frame handed out: types in MWSFD's form, the frame numbers from the
 * times and the frame rate, the user data and the picture details */
void mwply_SetFrmInf(MwsfdPly *ply, SfdFrameInfo *frm, MwsfdFrm *out)
{
    void *sfd = ply->sfd;
    unsigned char *bufadr = frm->buf;
    int buffmt = mwl_convBufFmtFromSFD(frm->bufFmt);
    int width = frm->width;
    int height = frm->height;
    int x_mb = frm->x_mb;
    int y_mb = frm->y_mb;
    int ptype = mwl_convPtypeFromSFD(frm->picType);
    int tunit = frm->unit;
    int time = frm->cat_time;
    int time_per_file = frm->time_per_file;
    int concat_cnt = frm->concat_cnt;
    int errcnt = frm->errcnt;
    int rcvcnt = frm->rcvcnt;
    int fps;
    int fno;
    int fno_per_file;

    if (SFD_GetFps(sfd, &fps) != 0) {
        MWSFSVM_Error(E201301_mwply_SetFrmInf_GetFps_failed);
    }
    fno = mwply_MulDivMs(time, fps, tunit);
    fno_per_file = mwply_MulDivMs(time_per_file, fps, tunit);
    out->bufadr = bufadr;
    out->buffmt = buffmt;
    out->width = width;
    out->height = height;
    out->x_mb = x_mb;
    out->y_mb = y_mb;
    out->ptype = ptype;
    out->fps = fps;
    out->fno = fno;
    out->time = time;
    out->tunit = tunit;
    out->concat_cnt = concat_cnt;
    out->time_per_file = time_per_file;
    out->fno_per_file = fno_per_file;
    out->errcnt = errcnt;
    out->rcvcnt = rcvcnt;
    mwply_GetFrmUsrData(ply, frm, out);
    out->tail = *(MwsfdFrmTail *)frm->tail.words;
}

/* the frame's user data without its 4-byte header; none while picture user data is off or the
 * player still uses its system buffer */
void mwply_GetFrmUsrData(MwsfdPly *ply, SfdFrameInfo *frm, MwsfdFrm *out)
{
    MwsfdPicUsrBuf *sys = &ply->sysPicUsrBuf;
    MwsfdPicUsrBuf *cur = ply->picUsrBuf;
    char *data = frm->picUsr->data;
    int size = frm->picUsr->len;

    if (MWSFD_GetUsePicUsr() != 1 || cur == sys) {
        out->usrdat = 0;
        out->usrdatlen = 0;
        return;
    }
    if (data != 0 && size >= 5) {
        data += 4;
        size -= 4;
    }
    out->usrdat = data;
    out->usrdatlen = size;
}

/* the frame number at `time` (in `tunit` per second) for `fps`, the frame rate times 1000 */
int mwply_MulDivMs(int time, int fps, int tunit)
{
    return UTY_MulDiv(time, fps, tunit * 1000);
}

int mwl_convBufFmtFromSFD(unsigned int ptype)
{
    int result;

    switch (ptype) {
    case 1:
        result = 1;
        break;
    case 2:
        result = 2;
        break;
    case 3:
        result = 3;
        break;
    default:
        result = 3;
        break;
    }
    return result;
}

int mwl_convPtypeFromSFD(unsigned int ptype)
{
    int result;

    switch (ptype) {
    case 1:
        result = 1;
        break;
    case 2:
        result = 2;
        break;
    case 3:
        result = 3;
        break;
    case 4:
        result = 4;
        break;
    default:
        MWSFSVM_Error(mwl_convPtypeFromSFD_Invalid_Ptype);
        result = 1;
        break;
    }
    return result;
}

int mwsffrm_DecideFrmType(MwsfdPly *ply, SfdFrameInfo *frm)
{
    int ret = 0;

    switch ((unsigned int)frm->tail.detail.picture_structure) {
    case 1:
    case 2:
        ret = 2;
        break;
    case 3:
        if (frm->tail.detail.progressive_frame == 0)
            ret = 2;
        break;
    case 0:
    default:
        MWSFSVM_Error(E301271_mwsffrm_DecideFrmType_Invalid_Pstruct);
        break;
    }
    if (MWSFD_GetUsePicUsr() == 1 && MWSFD_IsFrmDivField(ply) == 1)
        ret = 2;
    return ret;
}

void mwply_SetPicInf(MwsfdPly *ply, SfdFrameInfo *frm)
{
    MwsfdPicInf *pic = &ply->pic;
    int chromaPosH = frm->chromaPosH; /* read first: retail schedules this load ahead of the stores */

    pic->pictureStructure = frm->tail.detail.picture_structure;
    pic->chromaFormat = frm->tail.detail.chroma_format;
    pic->progressiveFrame = frm->tail.detail.progressive_frame;
    pic->topFieldFirst = frm->tail.detail.top_field_first;
    pic->repeatFirstField = frm->tail.detail.repeat_first_field;
    pic->chromaPosH = chromaPosH;
    pic->chromaPosV = frm->chromaPosV;
    pic->rsv = 0;
}

/* copies the frame's user data into the player's buffer and passes it on to MWSFSFX_SetPicUsrDat */
void mwply_UpdatePicUsrData(MwsfdPly *ply, SfdFrameInfo *frm)
{
    SfdSjChunk *usr = frm->picUsr;
    char *addr = usr->data;
    int size = usr->len;
    char *data;
    int len;

    if (MWSFD_GetUsePicUsr() != 1)
        return;
    if (ply->udbuf == 0)
        return;
    if (addr != 0 && size >= 5)
        SUD_SearchSudDat(addr + 4, size - 4, &data, &len);
    else {
        data = 0;
        len = 0;
    }
    if (data != 0 && len > 0) {
        if (ply->udbufsize < len)
            len = ply->udbufsize;
        memset(ply->udbuf, 0, ply->udbufsize);
        memcpy(ply->udbuf, data, len);
        ply->ud = ply->udbuf;
        ply->udsize = len;
    } else {
        ply->ud = 0;
        ply->udsize = 0;
    }
    MWSFSFX_SetPicUsrDat(ply, ply->ud, ply->udsize);
}

void MWSFD_GetPicUsrDat(MwsfdPly *ply, char **ud, int *udsize)
{
    char *data = ply->ud;
    int size = ply->udsize;

    *udsize = size;
    *ud = data;
}

int MWSFD_IsEnablePicUsr(MwsfdPly *ply)
{
    return ply->ud != 0;
}

void mwPlyCalcYccPlane(int a, int b, int c, MwsfdPlanes *out)
{
    SfdPlanes planes;

    SFD_CalcYccPlane(a, b, c, &planes);
    mwl_convYccPlaneFromSFD(&planes, out);
}

/* SFD's frame information as this conversion writes it: every word stored as a pointer (in the
 * order of SfdFrameInfo) */
typedef struct SfdFrmInfWords {
    void *width, *height, *x_mb, *y_mb, *picType, *time, *unit, *bufFmt, *buf, *errcnt, *rcvcnt, *concat_cnt;
} SfdFrmInfWords;

/* the reverse of mwply_SetFrmInf: an MWSFD frame as SFD's frame information */
void mwl_convFrmInfToSFD(MwsfdFrm *src, SfdFrmInfWords *dst)
{
    int bufadr, buffmt, width, height, x_mb, y_mb, ptype;

    bufadr = (int)src->bufadr;
    buffmt = mwl_convBufFmtToSFD(src->buffmt);
    width = src->width;
    height = src->height;
    x_mb = src->x_mb;
    y_mb = src->y_mb;
    ptype = mwl_convPtypeToSFD(src->ptype);
    dst->buf = (void *)bufadr;
    dst->bufFmt = (void *)buffmt;
    dst->width = (void *)width;
    dst->height = (void *)height;
    dst->x_mb = (void *)x_mb;
    dst->y_mb = (void *)y_mb;
    dst->picType = (void *)ptype;
    dst->time = (void *)src->time;
    dst->unit = (void *)src->tunit;
    dst->errcnt = (void *)src->errcnt;
    dst->rcvcnt = (void *)src->rcvcnt;
    dst->concat_cnt = (void *)src->concat_cnt;
}

int mwl_convBufFmtToSFD(unsigned int ptype)
{
    int result;

    switch (ptype) {
    case 1:
        result = 1;
        break;
    case 2:
        result = 2;
        break;
    case 3:
        result = 3;
        break;
    default:
        result = 3;
        break;
    }
    return result;
}

int mwl_convPtypeToSFD(unsigned int ptype)
{
    int result;

    switch (ptype) {
    case 1:
        result = 1;
        break;
    case 2:
        result = 2;
        break;
    case 3:
        result = 3;
        break;
    case 4:
        result = 4;
        break;
    default:
        MWSFSVM_Error(mwl_convPtypeToSFD_Invalid_Ptype);
        result = 1;
        break;
    }
    return result;
}

/* the SFD plane layout in the order the SFX conversion takes: the three plane addresses (base
 * first) and the matching strides (luma, then chroma twice) */
void mwl_convYccPlaneFromSFD(SfdPlanes *src, MwsfdPlanes *dst)
{
    dst->addr0 = src->base;
    dst->addr1 = src->luma;
    dst->stride1 = src->chromaStride;
    dst->stride0 = src->lumaStride;
    dst->addr2 = src->chroma;
    dst->stride2 = src->chromaStride;
}

void mwPlyRelCurFrm(MwsfdPly *ply)
{
    int limit;
    int count;
    void *frm;
    void *sfd;

    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error(E1122615_mwPlyRelCurFrm_inv_hn);
        return;
    }
    limit = ply->limit;
    count = ply->count;
    frm = ply->curFrm;
    sfd = mwPlyGetSfdHn(ply);
    if (count < limit) {
        SFD_RelFrm(sfd, frm);
        ply->limit = ply->count = ply->count + 1;
    }
}

int mwPlyIsNextFrmReady(MwsfdPly *ply)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error(E1122618_mwPlyIsNextFrmReady_inv_hn);
        return 0;
    }
    return SFD_IsNextFrmReady(mwPlyGetSfdHn(ply));
}

/* the next picture's user data, past its 4-byte header */
void mwPlyGetNextPicUsr(MwsfdPly *ply, char **addr, int *size)
{
    int n;
    char *a;

    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error(E3122201_mwPlyGetNextPicUsr_inv_hn);
        *addr = 0;
        *size = 0;
    } else {
        SFD_GetNextPicUsr(mwPlyGetSfdHn(ply), addr, size);
        n = *size;
        if (n >= 4) {
            a = *addr;
            *size = n - 4;
            *addr = a + 4;
        }
    }
}

/* the counter advanced by one while below its limit, the counter at the limit, 0 past it */
int MWSFD_GetLastFrmCnt(MwsfdPly *ply)
{
    int limit = ply->limit;
    int count = ply->count;
    int next;

    if (count < limit)
        next = count + 1;
    else if (limit == count)
        next = count;
    else
        next = 0;
    return next;
}

int mwPlyGetNumSkipDisp(MwsfdPly *ply)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error(E202231_mwPlyGetNumSkipDisp_inv_hn);
        return 0;
    }
    return ply->numSkipDisp;
}

void mwPlyGetCurPicHdrInfo(MwsfdPly *ply)
{
    mwply_GetCurPicHdrInfo(ply);
}

int mwsffrm_AnalyTotalFrm(SfhHn *hdr)
{
    int value;

    if (SFH_AnlyMaxFrmNum(hdr, &value) != 0) {
        return value;
    }
    return -1;
}

/* reads the picture header out of the stream's first sectors, looking in sectors 1 to 3: the header
 * info, composition mode and the two mux kinds, or -1 for the first two when none parses */
void mwply_GetPicInf(char *buf, unsigned int size, MwsfdHdrInf *hdr)
{
    SfhHn *sfh;
    int v[2];
    int off;
    int sector;

    hdr->frmnum = -1;
    if (size < 2048 || buf == 0)
        return;
    for (sector = 2; sector < 4; sector++) {
        off = (sector - 1) * 2048;
        sfh = SFH_Create(buf + off, size - off);
        if (sfh != 0) {
            if (SFH_IsSfdHeader(sfh, v) == 0 || v[0] == 0) {
                hdr->frmnum = -1;
                hdr->compoMode = -1;
                SFH_Destroy(sfh);
            } else {
                hdr->frmnum = mwsffrm_AnalyTotalFrm(sfh);
                hdr->compoMode = mwply_GetPicCompoMode(sfh);
                hdr->muxKind2 = mwply_GetMuxKind2(sfh);
                hdr->muxKind1 = mwply_GetMuxKind1(sfh);
                SFH_Destroy(sfh);
                return;
            }
        }
    }
}

/* the current picture's composition mode, 0x51 and 0x61 reported as 0x41 */
int mwPlyGetCurPicCompoMode(MwsfdPly *ply)
{
    int mode;

    mode = mwply_GetCurPicCompoMode(ply);
    if (mode == 0x51 || mode == 0x61) {
        mode = 0x41;
    }
    return mode;
}

/* the composition mode from the video stream's header info value */
int mwply_GetPicCompoMode(SfhHn *hdr)
{
    int v;
    int ret;

    if (!SFH_AnlyFtrFxType(hdr, SFD_STM_VIDEO, &v))
        return 17;
    switch (v) {
    case 1: ret = 33; break;
    case 3: ret = 81; break;
    case 6: ret = 97; break;
    case 0: case 2: case 4: case 5: case 7: case 8:
    default: ret = 17; break;
    }
    return ret;
}

int mwply_GetMuxKind1(SfhHn *hdr)
{
    int value;

    if (SFH_AnlyNumElemAud(hdr, &value) != 0) {
        return value;
    }
    return -1;
}

int mwply_GetMuxKind2(SfhHn *hdr)
{
    int value;

    if (SFH_AnlyNumElemVid(hdr, &value) != 0) {
        return value;
    }
    return -1;
}

void mwply_ResetPicLog(MwsfdPly *ply)
{
    int i;

    ply->picCount = 0;
    ply->logPos = 0;
    ply->logWrite = 0;
    for (i = 0; i < 8; i++) {
        ply->log[i].valid = 0;
        ply->log[i].picNo = 0;
        ply->log[i].itemTypeThree = 0;
        ply->log[i].hdrInfo = 0;
        ply->log[i].compoMode = 17;
    }
    MWSFSFX_SetColAdj(ply, 0);
}

void mwply_SetPicUsrCb(MwsfdPly *ply)
{
    void *sfd = ply->sfd;

    SFD_SetCond(sfd, SFD_CB_PICUSR, mwply_LogPic);
    SFD_SetCond(sfd, SFD_CB_PICUSR_OBJ, ply);
}

/* the SFD's picture user data callback: counts the picture and, when its user data parses as a
 * header with a video stream, logs the picture in the ring */
void mwply_LogPic(MwsfdPly *ply, char *buf, unsigned int size)
{
    SfhHn *hdr;
    int v[2];
    int itemTypeThree, hdrInfo, compoMode;
    int i;

    ply->picCount++;
    if (size < 2048 || buf == 0)
        return;
    hdr = SFH_Create(buf, size);
    if (hdr == 0)
        return;
    if (SFH_IsSfdHeader(hdr, v) == 0 || v[0] == 0) {
        SFH_Destroy(hdr);
        return;
    }
    itemTypeThree = mwply_IsPicItemType3(hdr);
    hdrInfo = mwsffrm_AnalyTotalFrm(hdr);
    compoMode = mwply_GetPicCompoMode(hdr);
    i = ply->logWrite;
    ply->log[i].picNo = ply->picCount - 1;
    ply->log[i].itemTypeThree = itemTypeThree;
    ply->log[i].hdrInfo = hdrInfo;
    ply->log[i].compoMode = compoMode;
    ply->log[i].valid = 1;
    ply->logWrite = (ply->logWrite + 1) % 8;
    SFH_Destroy(hdr);
}

/* whether the header lists the video stream and its info value is 3 */
int mwply_IsPicItemType3(SfhHn *hdr)
{
    int v[2];

    if (SFH_IsExistStmId(hdr, SFD_STM_VIDEO, v) == 0 || v[0] == 0) {
        return 0;
    }
    if (SFH_AnlyFtrColType(hdr, SFD_STM_VIDEO, &v[1]) == 0) {
        return 0;
    }
    return v[1] == 3;
}

/* the current picture's log entries (ring slot logPos % 8), with defaults before any is logged */
int mwply_IsCurPicItemTypeThree(MwsfdPly *ply)
{
    int slot = ply->logPos % 8;

    if (ply->log[slot].valid == 0)
        return 0;
    return mwply_GetLogItemTypeThree(ply, slot);
}

int mwply_GetLogItemTypeThree(MwsfdPly *ply, int slot)
{
    return ply->log[slot].itemTypeThree;
}

int mwply_GetCurPicHdrInfo(MwsfdPly *ply)
{
    int slot = ply->logPos % 8;

    if (ply->log[slot].valid == 0)
        return 0;
    return mwply_GetLogHdrInfo(ply, slot);
}

int mwply_GetLogHdrInfo(MwsfdPly *ply, int slot)
{
    return ply->log[slot].hdrInfo;
}

int mwply_GetCurPicCompoMode(MwsfdPly *ply)
{
    int slot = ply->logPos % 8;

    if (ply->log[slot].valid == 0)
        return 17;
    return mwply_GetLogCompoMode(ply, slot);
}

int mwply_GetLogCompoMode(MwsfdPly *ply, int slot)
{
    return ply->log[slot].compoMode;
}

int mwply_GetLogPos(MwsfdPly *ply)
{
    return ply->logPos;
}

int mwPlyGetNumRemainFrm(MwsfdPly *ply)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error(E409171_mwPlyGetNumRemainFrm_inv_hn);
        return 0;
    }
    return SFD_GetNumRemainFrm(mwPlyGetSfdHn(ply));
}
