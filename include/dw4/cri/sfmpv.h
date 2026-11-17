#ifndef SFMPV_H
#define SFMPV_H

#include "dw4/cri/m2v.h"
#include "dw4/cri/sfd.h"
#include "dw4/sony/libmpeg.h"

typedef struct SfdPlanes {
    char *luma;
    char *chroma;
    char *base;
    short chromaStride;
    short lumaStride;
} SfdPlanes;

typedef struct SfdChunk {
    char *addr;
    int size;
} SfdChunk;

typedef struct SfdRingInfo {
    char *addr0;
    int len0;
    char *addr1;
    int len1;
    int f16;
    int f20;
    int f24;
    int f28;
} SfdRingInfo;

/* what one picture decode writes and predicts from (SDK SFMPV_MPVFRM) */
typedef struct SfdFrmPara {
    SfdPlanes ref[2];
    char *dst;
    M2vPicAtr *pic;
    int nfrm;
    int nbyte;
} SfdFrmPara;

typedef struct SfdUserData {
    char data[512];
    int size;
} SfdUserData;

typedef struct SfdPicture {
    int valid;
    int pts;
    int hasPts;
    SfdTimeRec stamp;
    SfdUserData user;
} SfdPicture;

typedef struct SfdSlot {
    int state;
    int refs;
    void *buf;               /* the frame's picture buffer */
    SfdTimeRec stamp;
    int f56;
    int f60;
    int f64;
    int f68;
    int f72;
    int f76;
    int f80;
    SfdChunk *blob;
    M2vPicAtr info;
    long long f216;
    int f224;
    int pad228;
} SfdSlot;

typedef struct SfdBufPool {
    char *base;
    int count;
    int size;
    SfdChunk slot[18];
} SfdBufPool;

typedef struct SfdPlaneSet {
    SfdPlanes planes[2];
    int id;
    M2vPicAtr *pic;
    int f40;
    int f44;
} SfdPlaneSet;

typedef struct SfdMpvCond {
    int f0;
    int f4;
    int f8;
    int f12;
    int f16;
    int f20;
    int f24;
    int count;
    int f32;
} SfdMpvCond;

typedef struct SfdMpvWorkBufs {
    int w[2];
} SfdMpvWorkBufs;

typedef struct SfdMpvFrameBufs {
    int w[16];
} SfdMpvFrameBufs;

typedef struct SfdIpuEntry {
    long long f0;
    long long f8;
    int f16;
    int f20;
} SfdIpuEntry;

/* One DMA tag quadword of the IPU input chain. */
typedef struct SfdDmaTag {
    long long tag;
    long long pad;
} SfdDmaTag;

typedef struct SfdIpuStream {
    void *base;
    SfdDmaTag *uncached;
    int sectors;
    int f12;
    int queuedSct;
    int restBytes;
    int bytes;
    unsigned int r28;
    unsigned int r32;
    unsigned int r36;
    unsigned int r40;
    unsigned int r44;
    unsigned int r48;
    unsigned int r52;
    unsigned int r56;
    unsigned int r60;
    int sema;
    int f68;
    long long f72;
    SfdIpuEntry *entries;
    int entryCount;
    int f88;
    int f92;
} SfdIpuStream;

typedef struct SfdIpuEvent {
    int f0;
    int f4;
} SfdIpuEvent;

/* The sceMpeg/IPU decoder's work (SDK sfd_mpvp.c), inside the video work. */
typedef struct SfdIpuCtl {
    int enabled;
    int f4;
    int f8;
    int f12;
    char f16;
    char f17;
    char f18;
    char f19;
    int endRequest; /* 20 */
    int endSent;    /* 24 */
    int stopped;
    int value;
    int pad36;
    sceMpeg mpeg;        /* 40 */
    SfdIpuStream stream; /* 112 */
    SfdIpuEvent event;   /* 208 */
} SfdIpuCtl;


typedef struct SfdPicTrack {
    int number;
    int base;
    int count;
    int pad12;
    long long pos;
    long long timeSum;
} SfdPicTrack;

typedef struct SfdMpv {
    void *handle;
    SfdMpvCond cond;
    SfdMpvWorkBufs work;
    SfdMpvFrameBufs bufs;
    SfdSlot *current;
    unsigned int f116;
    int state;
    int f124;
    int f128;
    int f132;
    int f136;
    M2vPicAtr pic;
    int f268;
    int f272;
    int limit;
    SfdPicTrack track;
    int f312;
    int f316;
    SfdPlanes planes[2];
    SfdSlot *first;
    SfdSlot *second;
    SfdSlot *f360;
    int f364;
    int f368;
    int f372;
    int slotCount;
    int pad380;
    SfdSlot slots[16];
    SfdBufPool pool;
    int pad4252;
    long long f4256;
    SfdIpuCtl ipu;
} SfdMpv;

typedef struct SfdPicWait {
    int busy;
    char pad4[120];
    int f124;
} SfdPicWait;

typedef struct SfdPicGeom {
    int width;
    int height;
    int f8;
    int f12;
    int f16;
    int f20;
    int pad24[2];
    int f32;
} SfdPicGeom;

typedef struct SfdDecodeFlags {
    int f0;
    int f4;
    int f8;
    int f12;
    int f16;
    int f20;
    int f24;
    char pad28[8];
    int f36;
    int f40;
    int f44;
} SfdDecodeFlags;

typedef struct SfdPending {
    char pad0[8];
    int f8;
    int f12;
    int f16;
    char pad20[72];
    int f92;
    char pad96[56];
    int f152;
    char pad156[12];
    int f168;
    int f172;
} SfdPending;

typedef struct SfdPicRecord {
    int f0;
    int f4;
    char body[128];
} SfdPicRecord;

/* An SFBUF ring id; SFD_BUF_NONE marks a transfer slot with no ring connected. */
typedef enum SfdBufId {
    SFD_BUF_NONE = 8
} SfdBufId;

/* The video driver's transfer slot: its work, a union of the drivers' work types, and the ring it reads. */
typedef struct SfdStreams {
    int f0;
    int f4;
    union {
        void *obj;
        SfdMpv *mpv;
    } hn;
    int f12;
    SfdBufId f16;
    int f20;
    int pad24[2];
    int f32;
} SfdStreams;

typedef struct SfdLink {
    int f0;
    int id;
    int arg;
} SfdLink;

typedef struct SfdAudioMod {
    char pad0[12];
    void *handler;
} SfdAudioMod;

typedef struct SfdDecStat {
    int f0;
    int f4;
    int f8;
    int f12;
    int f16;
} SfdDecStat;

typedef struct SfdTblEnt {
    char pad0[32];
} SfdTblEnt;

/* The frame buffer format the player was created with (MWSFD converts it with
 * mwl_convBufFmtFromSFD); an enum in CRI's header. */
typedef enum SfdBufFmt {
    SFD_BUFFMT_0 = 0
} SfdBufFmt;

typedef struct SfdPlayer {
    SfdAudioMod *audio;
    char pad4[36];
    int f40;
    int f44;
    char pad48[8];
    SfdBufFmt bufFmt;
    char pad60[12];
    int f72;
    char pad76[44];
    SfdPicWait picWait;
    char pad248[2068];
    SfdPicGeom geom;
    char pad2352[32];
    SfdDecodeFlags decode;
    char pad2432[24];
    long long f2456;
    long long f2464;
    long long f2472;
    char pad2480[64];
    SfdDecStat stat;
    SfdPending pending;
    char pad2740[628];
    SfdTim tim;
    char pad4872[928];
    SfdPicRecord records[16];
    char pad7976[136];
    SfdStreams streams;
    char pad8148[972];
    SfdMpv mpvBody;
    char pad13600[264];
    char *userWork;
    SfdLink link;
    SfdTblEnt tbl[5];
    char trailer[64];
} SfdPlayer;

typedef struct SfdStream SfdStream;

typedef struct SfdStreamOps {
    char pad0[24];
    void (*read)(SfdStream *, int, int, int *);
    void (*end)(SfdStream *, int, int *);
    void (*skip)(SfdStream *, int, int *);
} SfdStreamOps;

struct SfdStream {
    SfdStreamOps *ops;
};

typedef struct SfdRecordTail {
    long long f0;
    int f8;
    int f12;
} SfdRecordTail;

typedef struct SfdRecord {
    int f0;
    int f4;
    int f8;
    int f12;
    SfdRecordTail tail;
} SfdRecord;

/* The MPEG picture type of a frame handed out (MWSFD converts it with mwl_convPtypeFromSFD). */
typedef enum SfdPicType {
    SFD_PICTYPE_I = 1,
    SFD_PICTYPE_P = 2,
    SFD_PICTYPE_B = 3
} SfdPicType;

/* SfdFrameInfo.f60, a copy of the picture attributes' f64; SfdFrmInfF60 is a placeholder for an
 * unknown enum of its own. */
typedef enum SfdFrmInfF60 {
    SFD_FRMINF_F60_0 = 0
} SfdFrmInfF60;

typedef struct SfdFrameDetail {
    int f72;
    char pad76[4];
    long long f80;
    int f88;
    int f92;
    int f96;
    int f100;
    unsigned short f104;
    unsigned short f106;
    unsigned char f108;
    unsigned char f109;
    unsigned char f110;
    unsigned char f111;
    unsigned char f112;
    unsigned char f113;
    unsigned char f114;
    unsigned char f115;
    unsigned char f116;
    unsigned char f117;
    unsigned char f118;
    unsigned char f119;
    unsigned char f120;
    unsigned char f121;
    unsigned char f122;
    char pad123[5];
} SfdFrameDetail;

/* The frame information handed to the application. Its fields are enums, pointers and a union as
 * in CRI's header: the details from 72 on are also the seven words MWSFD hands on unchanged, and
 * a store through the union conflicts with every load. */
typedef struct SfdFrameInfo {
    int f0;
    int f4;
    int f8;
    int f12;
    SfdPicType picType;      /* 16 */
    int f20;
    int f24;
    SfdBufFmt bufFmt;        /* 28 */
    void *buf;               /* 32 */
    int f36;
    int f40;
    int f44;
    int f48;
    int f52;
    SfdChunk *picUsr;        /* 56 */
    SfdFrmInfF60 f60;
    int f64;
    char pad68[4];
    union {
        SfdFrameDetail detail;
        long long words[7];
    } tail;                  /* 72 */
} SfdFrameInfo;

#endif
