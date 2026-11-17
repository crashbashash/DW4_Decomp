/* CRI SFH: reads the header sector of a Sofdec stream. */
#ifndef SFH_H
#define SFH_H

#define SFH_MAX_HN 32

/* One analysed CRI header: its state, the bytes it was read from and the tool version it names. */
typedef struct SfhHn {
    int stat;
    struct SfhHdr *hdr;
    unsigned int size;
    int version;          /* major * 100 + minor */
} SfhHn;

void SFH_Init(int maxHn, SfhHn *hns);
void SFH_Finish(void);
SfhHn *SFH_Create(void *hdr, unsigned int size);
void SFH_Destroy(SfhHn *hn);
int SFH_IsSfdHeader(SfhHn *hn, int *ok);
int SFH_IsExistStmId(SfhHn *hn, unsigned char id, int *exist);
int SFH_IsEffFtrInf(SfhHn *hn, unsigned char id, int *avail);
int SFH_AnlyHdrToolVer(SfhHn *hn, int *major, int *minor);
int SFH_AnlyHdrSiz(SfhHn *hn, int *value);
int SFH_AnlyPackType(SfhHn *hn, int *value);
int SFH_AnlyPketSizLen(SfhHn *hn, int *value);
int SFH_AnlyPackSiz(SfhHn *hn, int *value);
int SFH_AnlyNumElemTot(SfhHn *hn, int *value);
int SFH_AnlyNumElemAud(SfhHn *hn, int *value);
int SFH_AnlyNumElemVid(SfhHn *hn, int *value);
int SFH_AnlyNumElemPrv(SfhHn *hn, int *value);
int SFH_AnlyByteRate(SfhHn *hn, int *value);
int SFH_AnlyMaxPlyLenAud(SfhHn *hn, int *value);
int SFH_AnlyMaxPlyLenVid(SfhHn *hn, int *value);
int SFH_AnlyMaxFrmNum(SfhHn *hn, int *value);
int SFH_AnlyElemCodecAud(SfhHn *hn, unsigned char id, int *value);
int SFH_AnlyElemLayer(SfhHn *hn, unsigned char id, int *value);
int SFH_AnlyElemChNum(SfhHn *hn, unsigned char id, int *value);
int SFH_AnlyElemSmpHz(SfhHn *hn, unsigned char id, int *value);
int SFH_AnlyElemCodecVid(SfhHn *hn, unsigned char id, int *value);
int SFH_AnlyElemBitRate(SfhHn *hn, unsigned char id, int *value);
int SFH_AnlyElemPicSz(SfhHn *hn, unsigned char id, int *width, int *height);
int SFH_AnlyElemPicRate(SfhHn *hn, unsigned char id, int *value);
int SFH_AnlyFtrColType(SfhHn *hn, unsigned char id, int *value);
int SFH_AnlyFtrPicType(SfhHn *hn, unsigned char id, int *value);
int SFH_AnlyFtrFixFlg(SfhHn *hn, unsigned char id, int *value);
int SFH_AnlyFtrShcFixFlg(SfhHn *hn, unsigned char id, int *value);
int SFH_AnlyFtrExpand(SfhHn *hn, unsigned char id, int *value);
int SFH_AnlyFtrGopN(SfhHn *hn, unsigned char id, int *value);
int SFH_AnlyFtrGopM(SfhHn *hn, unsigned char id, int *value);
int SFH_AnlyFtrFxType(SfhHn *hn, unsigned char id, int *value);

#endif
