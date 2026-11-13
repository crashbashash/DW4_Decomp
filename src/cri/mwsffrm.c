/* MWSFFRM: the MWSFD player's frame side. Frame sync, the frame handed out by mwPlyGetCurFrm and its
 * release, the picture types and plane layout converted between SFD and MWSFD, the picture user
 * data, and the per-picture log ring the SFD's picture callback fills. */
#include "dw4/cri/mwply.h"
#include "dw4/cri/sfmpv.h"

/* a picture's user data chunk as the SFD frame points at it; its first 4 bytes are a header */
typedef struct MwsfdUsrChunk {
    char *addr;
    int size;
} MwsfdUsrChunk;

/* the SFD frame as the player reads it */
typedef struct MwsfdSfdFrm {
    char pad0[44];
    int usrLen;               /* 44 */
    char pad48[8];
    MwsfdUsrChunk *usr;       /* 56 */
} MwsfdSfdFrm;

/* the frame the player hands out */
typedef struct MwsfdFrm {
    char pad0[64];
    char *usrData;            /* 64 */
    int usrSize;              /* 68 */
} MwsfdFrm;

/* the picture header the SFD decoder reports */
typedef struct MwsfdSfdPicHdr {
    char pad0[60];
    int f60;                  /* 60 */
    int f64;                  /* 64 */
    char pad68[20];
    unsigned int pictureStructure; /* 88 */
    unsigned int chromaFormat;     /* 92 */
    char pad96[12];
    signed char f108;         /* 108 */
    signed char f109;         /* 109 */
    signed char f110;         /* 110 */
} MwsfdSfdPicHdr;

/* the frame information SFD returns, and the MWSFD form it is converted to */
typedef struct SfdFrmInf {
    int f0;
    unsigned int ptype;       /* 4 */
    int f8;
    int f12;
    int f16;
    int f20;
    unsigned int pstruct;     /* 24 */
    int f28;
    int f32;
    int f36;
    int f40;
    int f44;
    int f48;
    int f52;
    int f56;
    int f60;
} SfdFrmInf;

typedef struct MwsfdFrmInf {
    void *f0;
    void *f4;
    void *f8;
    void *f12;
    void *pstruct;            /* 16 */
    void *f20;
    void *f24;
    void *ptype;              /* 28 */
    void *f32;
    void *f36;
    void *f40;
    void *f44;
} MwsfdFrmInf;

/* the plane layout in the order the SFX conversion takes it */
typedef struct MwsfdPlanes {
    char *addr0;
    char *addr1;
    char *addr2;
    int stride0;
    int stride1;
    int stride2;
} MwsfdPlanes;

/* the SFD header handle a picture's header is parsed into */
typedef struct SfdHdrHn SfdHdrHn;

#define SFD_STM_VIDEO 224
#define SFD_CB_PICUSR 0x4B    /* the picture user data callback */
#define SFD_CB_PICUSR_OBJ 0x4C

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

void *memset(void *dst, int c, unsigned int n);
void *memcpy(void *dst, const void *src, unsigned int n);
void mwsfd_Error(const char *message, ...);
int MWSFD_GetUsePicUsr(void);
int MWSFD_IsEnableHndl(MwsfdPly *ply);
void *mwPlyGetSfdHn(MwsfdPly *ply);
void mwsfsfx_SetOutMode(MwsfdPly *ply, int flag);
void mwsfsfx_SetOutModeByPic(MwsfdPly *ply, int flag);
void mwsfsfx_UpdateAddInf(MwsfdPly *ply);
void mwsfsfx_SetPicUsr(MwsfdPly *ply, char *ud, int udsize);
int mwsfsfx_GetPicUsrItem3(MwsfdPly *ply);
int mwsfsfx_GetPicUsrFrmType(MwsfdPly *ply);
void UTY_MulDiv(int a, int b, int c);
void sfmpv_GetPlanes(int a, int b, int c, SfdPlanes *planes);
void SFD_GetNextPicUsr(void *sfd, char **addr, int *size);
int SFD_GetNumRemainFrm(void *sfd);
int SFD_IsNextFrmReady(void *sfd);
int SFD_RelFrm(void *sfd, int frm);
void SFD_SetCond(void *sfd, int id, void *value);
SfdHdrHn *SFH_Create(char *buf, unsigned int size);
void SFH_Destroy(SfdHdrHn *hdr);
int SFH_IsExistStmId(SfdHdrHn *hdr, int id, int *present);
int SFH_AnlyNumElemAud(SfdHdrHn *hdr, int *value);
int SFH_AnlyNumElemVid(SfdHdrHn *hdr, int *value);
int SFH_AnlyFtrColType(SfdHdrHn *hdr, int id, int *value);
int SFH_AnlyFtrFxType(SfdHdrHn *hdr, int id, int *value);
int SFH_IsSfdHeader(SfdHdrHn *hdr, int *present);
int SFH_AnlyMaxFrmNum(SfdHdrHn *hdr, int *value);
void SUD_FindTag(char *addr, int size, char **data, int *len);

int mwply_GetFrmSync(MwsfdPly *ply);
int mwply_HasPicUsrData(MwsfdPly *ply);
void mwply_CopyPlanes(SfdPlanes *src, MwsfdPlanes *dst);
int mwply_ConvPicType(unsigned int ptype);
int mwl_convPtypeToSFD(unsigned int ptype);
int mwply_GetCurPicHdrInfo(MwsfdPly *ply);
int mwply_GetPicHdrInfo(SfdHdrHn *hdr);
int mwply_GetPicCompoMode(SfdHdrHn *hdr);
int mwply_IsPicItemType3(SfdHdrHn *hdr);
void mwply_LogPic(MwsfdPly *ply, char *buf, unsigned int size);
int mwply_GetLogItemTypeThree(MwsfdPly *ply, int slot);
int mwply_GetLogHdrInfo(MwsfdPly *ply, int slot);
int mwply_GetLogCompoMode(MwsfdPly *ply, int slot);
int mwply_GetCurPicCompoMode(MwsfdPly *ply);

void mwPlySetFrmSync(MwsfdPly *ply, int frmSync)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error(E1122629_mwPlySetFrmSync_inv_hn);
        return;
    }
    ply->frmSync = frmSync;
}

int mwPlyGetFrmSync(MwsfdPly *ply)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error(E2010801_mwPlyGetFrmSync_inv_hn);
        return 0;
    }
    return mwply_GetFrmSync(ply);
}

int mwply_GetFrmSync(MwsfdPly *ply)
{
    return ply->frmSync;
}

/* takes the frame's user data length, letting mwsfsfx_UpdateAddInf act first when it grows */
void mwply_UpdateUsrLen(MwsfdPly *ply, MwsfdSfdFrm *frm)
{
    if (ply->usrBuf.f8 < frm->usrLen) {
        mwsfsfx_UpdateAddInf(ply);
    }
    ply->usrBuf.f8 = frm->usrLen;
}

void mwply_ApplyItemType3(MwsfdPly *ply)
{
    int on = 1; /* matching construct: manual — retail keeps this 1 in a saved register */
    int flag;
    int has;

    flag = mwply_IsCurPicItemTypeThree(ply) == on;
    has = mwply_HasPicUsrData(ply);
    if (has == on) {
        flag = mwsfsfx_GetPicUsrItem3(ply) == has;
    }
    mwsfsfx_SetOutModeByPic(ply, flag);
}

/* the frame's user data without its 4-byte header; none while picture user data is off or the
 * player still uses its system buffer */
void mwply_GetFrmUsrData(MwsfdPly *ply, MwsfdSfdFrm *frm, MwsfdFrm *out)
{
    MwsfdPicUsrBuf *sys = &ply->sysPicUsrBuf;
    MwsfdPicUsrBuf *cur = ply->picUsrBuf;
    char *data = frm->usr->addr;
    int size = frm->usr->size;

    if (MWSFD_GetUsePicUsr() != 1 || cur == sys) {
        out->usrData = 0;
        out->usrSize = 0;
        return;
    }
    if (data != 0 && size >= 5) {
        data += 4;
        size -= 4;
    }
    out->usrData = data;
    out->usrSize = size;
}

void mwply_MulDivMs(int a, int b, int sec)
{
    UTY_MulDiv(a, b, sec * 1000);
}

int mwply_ConvPicTypeFromSFD(unsigned int ptype)
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
        mwsfd_Error(mwl_convPtypeFromSFD_Invalid_Ptype);
        result = 1;
        break;
    }
    return result;
}

typedef struct MwsfdPicStat {
    char pad0[88];
    unsigned int pstruct;     /* 88 */
    char pad92[16];
    signed char topFirst;     /* 108 */
} MwsfdPicStat;

int mwsffrm_DecideFrmType(MwsfdPly *ply, MwsfdPicStat *pic)
{
    int ret = 0;

    switch (pic->pstruct) {
    case 1:
    case 2:
        ret = 2;
        break;
    case 3:
        if (pic->topFirst == 0)
            ret = 2;
        break;
    case 0:
    default:
        mwsfd_Error(E301271_mwsffrm_DecideFrmType_Invalid_Pstruct);
        break;
    }
    if (MWSFD_GetUsePicUsr() == 1 && mwsfsfx_GetPicUsrFrmType(ply) == 1)
        ret = 2;
    return ret;
}

void mwply_SetPicInf(MwsfdPly *ply, MwsfdSfdPicHdr *hdr)
{
    MwsfdPicInf *pic = &ply->pic;
    int f60 = hdr->f60; /* read first: retail schedules this load ahead of the stores */

    pic->pictureStructure = hdr->pictureStructure;
    pic->chromaFormat = hdr->chromaFormat;
    pic->f8 = hdr->f108;
    pic->f12 = hdr->f109;
    pic->f16 = hdr->f110;
    pic->chromaPosH = f60;
    pic->chromaPosV = hdr->f64;
    pic->f28 = 0;
}

/* copies the frame's user data into the player's buffer and passes it on to mwsfsfx_SetPicUsr */
void mwply_UpdatePicUsrData(MwsfdPly *ply, MwsfdSfdFrm *frm)
{
    MwsfdUsrChunk *usr = frm->usr;
    char *addr = usr->addr;
    int size = usr->size;
    char *data;
    int len;

    if (MWSFD_GetUsePicUsr() != 1)
        return;
    if (ply->udbuf == 0)
        return;
    if (addr != 0 && size >= 5)
        SUD_FindTag(addr + 4, size - 4, &data, &len);
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
    mwsfsfx_SetPicUsr(ply, ply->ud, ply->udsize);
}

void mwPlyGetPicUsrData(MwsfdPly *ply, char **ud, int *udsize)
{
    char *data = ply->ud;
    int size = ply->udsize;

    *udsize = size;
    *ud = data;
}

int mwply_HasPicUsrData(MwsfdPly *ply)
{
    return ply->ud != 0;
}

void mwply_GetPlanes(int a, int b, int c, MwsfdPlanes *out)
{
    SfdPlanes planes;

    sfmpv_GetPlanes(a, b, c, &planes);
    mwply_CopyPlanes(&planes, out);
}

void mwply_ConvFrmInf(SfdFrmInf *src, MwsfdFrmInf *dst)
{
    int f0, ptype, f8, f12, f16, f20, pstruct;

    f0 = src->f0;
    ptype = mwply_ConvPicType(src->ptype);
    f8 = src->f8;
    f12 = src->f12;
    f16 = src->f16;
    f20 = src->f20;
    pstruct = mwl_convPtypeToSFD(src->pstruct);
    dst->f32 = (void *)f0;
    dst->ptype = (void *)ptype;
    dst->f0 = (void *)f8;
    dst->f4 = (void *)f12;
    dst->f8 = (void *)f16;
    dst->f12 = (void *)f20;
    dst->pstruct = (void *)pstruct;
    dst->f20 = (void *)src->f36;
    dst->f24 = (void *)src->f40;
    dst->f36 = (void *)src->f56;
    dst->f40 = (void *)src->f60;
    dst->f44 = (void *)src->f44;
}

int mwply_ConvPicType(unsigned int ptype)
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
        mwsfd_Error(mwl_convPtypeToSFD_Invalid_Ptype);
        result = 1;
        break;
    }
    return result;
}

/* the SFD plane layout in the order the SFX conversion takes: the three plane addresses (base
 * first) and the matching strides (luma, then chroma twice) */
void mwply_CopyPlanes(SfdPlanes *src, MwsfdPlanes *dst)
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
    int frm;
    void *sfd;

    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error(E1122615_mwPlyRelCurFrm_inv_hn);
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
        mwsfd_Error(E1122618_mwPlyIsNextFrmReady_inv_hn);
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
        mwsfd_Error(E3122201_mwPlyGetNextPicUsr_inv_hn);
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
int mwply_NextCount(MwsfdPly *ply)
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
        mwsfd_Error(E202231_mwPlyGetNumSkipDisp_inv_hn);
        return 0;
    }
    return ply->numSkipDisp;
}

void mwPlyGetCurPicHdrInfo(MwsfdPly *ply)
{
    mwply_GetCurPicHdrInfo(ply);
}

int mwply_GetPicHdrInfo(SfdHdrHn *hdr)
{
    int value;

    if (SFH_AnlyMaxFrmNum(hdr, &value) != 0) {
        return value;
    }
    return -1;
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
int mwply_GetPicCompoMode(SfdHdrHn *hdr)
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

int mwply_GetMuxKind1(SfdHdrHn *hdr)
{
    int value;

    if (SFH_AnlyNumElemAud(hdr, &value) != 0) {
        return value;
    }
    return -1;
}

int mwply_GetMuxKind2(SfdHdrHn *hdr)
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
    mwsfsfx_SetOutMode(ply, 0);
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
    SfdHdrHn *hdr;
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
    hdrInfo = mwply_GetPicHdrInfo(hdr);
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
int mwply_IsPicItemType3(SfdHdrHn *hdr)
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
        mwsfd_Error(E409171_mwPlyGetNumRemainFrm_inv_hn);
        return 0;
    }
    return SFD_GetNumRemainFrm(mwPlyGetSfdHn(ply));
}
