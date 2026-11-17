/* CRI SFD: the Sofdec playback library. The SFD handle is passed as `void *sfd`; each SFD file reads
 * it through its own view of the handle object. */
#ifndef DW4_CRI_SFD_H
#define DW4_CRI_SFD_H

struct SfdAdxCfg;
struct SfdAnaInf;
struct SfdBufEnt;
struct SfdBufCrePrm;
struct SfdBufInf;
struct SfdBufStat;
struct SfdSj;
struct SfdInfo64;
struct SfdStatus160;
struct SfdHdrInf;
struct SfdInitPrm;
struct SfdErrInf;
struct SfdRecSlot;
struct SfdRec;
struct SfdItem;
struct SfdTrnModules;
struct SfdTrnSlot;
struct SfdTrnConfig;
struct SfdTst;
struct SfdRatio;
struct SfdMpvCond;
struct SfdPlanes;
struct SfdLib;
struct SfdTim;
struct SfdTimeRec;
struct SfdTcDesc;
struct SfdTimeSpan;

/* A clock source: the time of the handle as a count of units. */
typedef int (*SfdTimeFn)(void *sfd, int *time, int *unit);

/* SFADXT: the ADX audio stream */
int SFADXT_IsHeader(unsigned char *header, int length, int *headerSize);
void SFD_SetAdxtPara(struct SfdAdxCfg *cfg);


/* the user streams of the audio information */
int SFD_SetUsrSj(void *sfd, int index, int kind, void *sj);

/* analysis of a stream head for the creation parameters */
void SFD_AnalyCreInf(unsigned char *buf, int size, struct SfdAnaInf *inf);

/* SFBUF: the stream buffers */
void sfbuf_Init(void *work);
void SFBUF_Finish(void *work);
int SFBUF_InitHn(void *sfd, struct SfdBufEnt *ents, struct SfdBufCrePrm *prm);
void SFBUF_DestroySj(void *sfd);
int SFBUF_SetSupplySj(void *sfd, struct SfdBufInf *inf);
void SFBUF_SetUoch(void *sfd, int index, int slot, void *uoch);
void SFBUF_GetUoch(void *sfd, int index, int slot, void *uoch);
int SFBUF_RingGetWrite(void *sfd, int index, struct SfdBufStat *stat);
int SFBUF_RingGetRead(void *sfd, int index, struct SfdBufStat *stat);
int SFBUF_RingAddWrite(void *sfd, int index, int len, int tail);
int SFBUF_RingAddRead(void *sfd, int index, int len);
void SFBUF_RingGetDlm(void *sfd, int index, int *pos, int *len);
void SFBUF_RingSetDlm(void *sfd, int index, int pos, int len);
int SFBUF_GetRingBufSiz(void *sfd, int index);
int SFBUF_GetRTot(void *sfd, int index);
int SFBUF_GetWTot(void *sfd, int index);
int SFBUF_RingGetSj(void *sfd, int index, struct SfdSj **out);
void SFBUF_AddRtotSj(void *sfd, int index, int len);
int SFBUF_VfrmGetRead(void *sfd, int index, int value);
int SFBUF_VfrmAddRead(void *sfd, int index, int value);
int SFBUF_SetPrepFlg(void *sfd, int index, int value);
int SFBUF_GetPrepFlg(void *sfd, int index);
void SFBUF_SetTermFlg(void *sfd, int index, int value);
int SFBUF_GetTermFlg(void *sfd, int index);
int SFBUF_RingGetDataSiz(void *sfd, int index);
void sfbuf_GetSjPos(struct SfdSj *sj, int *first, int *second);
long sfbuf_MergeTotal(long total, unsigned int low);

/* conditions and status */
int SFD_GetSvrStat(void);
int SFD_GetHnStat(void *sfd);
int SFD_SetCond(void *sfd, int index, int value);
void SFSET_SetCond(void *sfd, int index, int value);
int SFD_GetCond(void *sfd, int index, int *out);
int SFSET_GetCond(void *sfd, int index);
int SFD_GetMvInf(void *sfd, struct SfdInfo64 *out);
int SFD_GetPlyInf(void *sfd, struct SfdStatus160 *out);
int SFD_GetTrHn(void *sfd, int index, int *out);

/* SFHDS: the stream header */
void SFHDS_InitFhd(struct SfdHdrInf *hdr);
void SFHDS_FinishFhd(struct SfdHdrInf *hdr);
int SFHDS_GetMuxVerNum(void *sfd);
int SFHDS_GetColType(void *sfd);

/* the library, errors and locks */
int SFD_IsHnSize(void *work, int size);
long SFD_Init(struct SfdInitPrm *prm);
int SFD_Finish(void);
void sfd_ClearErr(struct SfdErrInf *err);
int sfd_ReportError(void *sfd, int code);
int SFLIB_CheckHn(void *sfd);
void sfd_Lock(void *guard);
void sfd_Unlock(void *guard);

/* playback */
int SFD_GetPaStat(void *sfd);
int SFD_Pause(void *sfd, int sw);
int SFD_Standby(void *sfd);
int SFD_SetSpeed(void *sfd, int value);
int SFD_SetAudioCh(void *sfd, int value);
int SFD_SetVideoCh(void *sfd, int value);
void sfmpvps2_Init(void);
void SFD_VsyncSvr(void);
int SFD_IsHnSvrWait(void *sfd);
int SFD_IsSvrDone(void);
int SFD_ExecOne(void *sfd);
int SFPLY_DecideSvrStat(void);
void SFPLY_AddSkipPic(void *sfd, int delta, int arg);
int SFD_Destroy(void *sfd);
int SFD_Start(void *sfd);
int SFD_Stop(void *sfd);
int SFPLY_Stop(void *sfd);
int SFPLY_GetResetFlg(void);
int SFD_GetWritePtr(void *sfd, struct SfdBufStat *inf);
int SFD_AddWritePtr(void *sfd, int a, int b);
int SFD_TermSupply(void *sfd);
int SFD_GetFrm(void *sfd, int *out);
int SFD_RelFrm(void *sfd, int value);
int SFD_SetSupplySj(void *sfd, struct SfdBufInf *inf);

/* SFSEE: seeking and the stream record */
void SFSEE_InitHn(struct SfdRecSlot *slot);
int SFD_EntrySeek(void *sfd, struct SfdRec *rec);
void SFSEE_FixAvPlay(void *sfd, int id3512, int id3516);
void SFSEE_ExecServer(void *sfd);
int SFD_SetFileSize(void *sfd, int value);
int SFD_SetTotTime(void *sfd, int divisor, int scale);
int SFD_SetByteRate(void *sfd, int value);
void SFD_SetSeekPos(void *sfd, int offset);

/* the time-stamp rings */
int SFPTS_WritePtsQue(void *sfd, int index, struct SfdItem *item, int *full);
int SFPTS_IsPtsQueFull(void *sfd, int index);

/* SFCON: concatenated playback */
int SFD_SetConcatPlay(void *sfd);
int SFCON_IsEndcodeSkip(void *sfd);
int SFCON_IsSystemEndcodeSkip(void *sfd);
int SFCON_IsVideoEndcodeSkip(void *sfd);
int SFCON_UpdateConcatTime(void *sfd, int amount);
int SFCON_WriteTotSmplQue(void *sfd, int pts, int last);

/* SFTRN: the stream modules */
int SFTRN_Init(struct SfdTrnModules *dst, struct SfdTrnModules *src);
int SFTRN_Finish(struct SfdTrnModules *modules);
void SFTRN_InitHn(void *sfd, struct SfdTrnSlot *s, struct SfdTrnConfig **pconfig, int arg);
int SFTRN_CallTrSetup(void *sfd, int k);
void SFTRN_SetPrepFlg(void *sfd, int index, int value);
int SFTRN_GetPrepFlg(void *sfd, int index);
void SFTRN_SetTermFlg(void *sfd, int index, int value);
int SFTRN_GetTermFlg(void *sfd, int index);

/* SFTST: the time-stamp statistics */
void SFTST_Create(struct SfdTst *p);
void SFTST_SetTstFlg(struct SfdTst *tst, int value);
long SFTST_SetTolerance(struct SfdTst *tst, struct SfdRatio *ratio);
void SFTST_SetExcessErr(struct SfdTst *tst, struct SfdRatio *ratio);
void SFTST_SetAdjStart(struct SfdTst *tst, struct SfdRatio *ratio);
long SFTST_SetAdjPoff(struct SfdTst *tst, struct SfdRatio *ratio);
void SFTST_SetMovaveRange(struct SfdTst *tst, int count);
void SFTST_Pause(struct SfdTst *tst, unsigned int pastat);
void SFTST_SetAdjFlg(struct SfdTst *tst, int paused);
void SFTST_GoNextFrame(struct SfdTst *tst, struct SfdRatio *ratio);
void SFTST_Calc(struct SfdTst *tst, struct SfdRatio *mt, struct SfdRatio *hlp, struct SfdRatio *out);

/* the user audio output */
void SFD_SetOutPan(void *sfd, int a, int b);
int SFD_GetOutPan(void *sfd, int a);
void SFD_SetOutVol(void *sfd, int a);
int SFD_GetOutVol(void *sfd);
void SFAOAP_SetSpeed(void *sfd, int a);

/* SFMPS: the system stream */
int SFD_GetVideoCh(void *sfd);
int SFD_GetAudioCh(void *sfd);
int SFMPS_GetConcatCnt(void *sfd);

/* SFMPV: the video stream */
void SFD_SetMpvParaTbl(struct SfdMpvCond *cond, int *work, int *bufs);
void SFD_CalcYccPlane(char *base, int width, int height, struct SfdPlanes *planes);
void SFD_SetMpvCond(void *sfd, int mode, int value);
int SFD_GetNumFrm(void *sfd, int *out);
void SFD_SetPicUsrBuf(void *sfd, char *base, int count, int size);
void SFD_GetNextPicUsr(void *sfd, char **data, int *size);
int SFD_GetNumRemainFrm(void *sfd);
int SFD_IsNextFrmReady(void *sfd);

/* SFMPVP: the PS2 MPEG decoder */
void SFD_SetSceMpeg(int enable);
int SFMPVP_IsSceMpegUsed(void *sfd);
void SFMPVP_Init(void);
int SFD_GetSceErrMessage(void *sfd);
int SFMPVP_Put(void *sfd, char *src, int pos);
int SFMPVP_Unput(void *sfd, int count);
void sfmpvps2_StopIpu(void *sfd, int value);
int SFMPVP_GetFrameCount(void *sfd);
int SFMPVP_IsPscEnough(void *sfd);
void SFMPVP_Create(void *sfd);

/* SFTIM: playback time */
void SFTIM_Init(struct SfdLib *lib, int rate);
void SFTIM_Finish(struct SfdLib *lib);
void SFTIM_InitHn(void *sfd, struct SfdTim *tim);
void SFTIM_InitTtu(struct SfdTimeRec *rec, int time);
void SFTIM_UpdateItime(struct SfdTim *tim, int now);
int SFTIM_GetNextItime(struct SfdTim *tim, int now);
void SFTIM_VbIn(void);
int SFTIM_IsStagnant(void *sfd);
int SFTIM_GetVideoStartSample(struct SfdTim *tim, int scale, int *valid);
void SFTIM_SetStartTime(struct SfdTim *tim, int a, int b);
int SFD_GetTime(void *sfd, int *time, int *unit);
int SFTIM_GetTimeSub(void *sfd, int *time, int *unit);
int SFTIM_GetTime(void *sfd, int *time, int *unit);
int SFTIM_ChkRegularTime(void *sfd, int *time, int *unit);
int SFD_CmpTime(int num0, int den0, int num1, int den1);
int SFD_SetExtClockFn(void *sfd, int (*get)(int ctx, int *time, int *unit), int wrap, int ctx);
int SFD_SetUsrTimeFn(void *sfd, SfdTimeFn fn);
int SFD_UpdateTime(void *sfd);
void SFTIM_SetTimeFn(void *sfd, SfdTimeFn fn, int index);
void SFTIM_Tc2Time(struct SfdTcDesc *desc, int *time, int *unit);
void SFTIM_GetTimeOneFrmVideo(void *sfd, int *scale, int *rate);
int SFD_GetFps(void *sfd, int *rate);
int SFTIM_IsGetFrmTime(void *sfd, struct SfdTimeSpan *span);
int SFTIM_IsGetFrmTimeTunit(void *sfd, int time, int unit);
int SFTIM_IsVideoTerm(void *sfd);
void SFTIM_SetSpeed(void *sfd, int value);
int SFTIM_GetSpeed(void *sfd);

#endif
