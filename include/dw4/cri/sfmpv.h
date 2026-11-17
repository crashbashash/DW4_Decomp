#ifndef SFMPV_H
#define SFMPV_H

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

typedef struct SfdTimeCode {
    int rate;
    int drop;
    int hour;
    int minute;
    int second;
    int frame;
    int add;
    short field0;
    short field;
} SfdTimeCode;

typedef struct SfdTimeStamp {
    int done;
    SfdTimeCode tc;
    int a;
    int b;
} SfdTimeStamp;

typedef struct SfdFieldEntry {
    short f0;
    unsigned short f2;
} SfdFieldEntry;

typedef struct SfdTimer {
    char pad0[24];
    int (*hook)(void *player, int kind, int offset, int extra);

    SfdTimeCode tc;
    SfdTimeStamp state;
    SfdTimeStamp best;
    SfdTimeStamp f148;
    SfdTimeStamp cur;
    SfdTimeStamp latest;
    SfdTimeStamp f280;
    char pad324[12];
    long f336;
    char pad344[8];
    int f352;
    int base;
    char pad360[136];
    int pos;
    char pad500[136];
    int f636;
    int f640;
    int f644;
    int f648;
    char pad652[548];
    SfdFieldEntry fields[64];
} SfdTimer;

typedef struct SfdPicInfo {
    int width;
    int height;
    int f8;
    int f12;
    int rateIndex;
    int number;
    unsigned int type;
    int f28;
    int f32;
    int f36;
    int f40;
    int f44;
    int f48;
    int f52;
    int f56;
    int f60;
    int f64;
    int f68;
    int f72;
    int f76;
    unsigned short f80;
    unsigned short f82;
    unsigned char f84;
    unsigned char f85;
    unsigned char f86;
    signed char f87;
    signed char f88;
    unsigned char f89;
    unsigned char f90;
    unsigned char f91;
    unsigned char f92;
    unsigned char f93;
    unsigned char f94;
    unsigned char f95;
    unsigned char f96;
    unsigned char f97;
    unsigned char f98;
    unsigned char f99;
    unsigned char f100;
    char pad101[27];
} SfdPicInfo;

/* what one picture decode writes and predicts from (SDK SFMPV_MPVFRM) */
typedef struct SfdFrmPara {
    SfdPlanes ref[2];
    char *dst;
    SfdPicInfo *pic;
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
    SfdTimeStamp stamp;
    SfdUserData user;
} SfdPicture;

typedef struct SfdSlot {
    int state;
    int refs;
    int id;
    SfdTimeStamp stamp;
    int f56;
    int f60;
    int f64;
    int f68;
    int f72;
    int f76;
    int f80;
    SfdChunk *blob;
    SfdPicInfo info;
    long f216;
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
    struct SfdPicInfo *pic;
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

typedef struct SfdMpegCtx {
    int f0;
    int f4;
    int f8;
    char pad12[60];
} SfdMpegCtx;

typedef struct SfdIpuEntry {
    long f0;
    long f8;
    int f16;
    int f20;
} SfdIpuEntry;

/* One DMA tag quadword of the IPU input chain. */
typedef struct SfdDmaTag {
    long tag;
    long pad;
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
    long f72;
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
    SfdMpegCtx mpeg;     /* 40 */
    SfdIpuStream stream; /* 112 */
    SfdIpuEvent event;   /* 208 */
} SfdIpuCtl;


typedef struct SfdPicTrack {
    int number;
    int base;
    int count;
    int pad12;
    long pos;
    long timeSum;
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
    SfdPicInfo pic;
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
    long f4256;
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

typedef struct SfdPlayer {
    SfdAudioMod *audio;
    char pad4[36];
    int f40;
    int f44;
    char pad48[8];
    int f56;
    char pad60[12];
    int f72;
    char pad76[44];
    SfdPicWait picWait;
    char pad248[2068];
    SfdPicGeom geom;
    char pad2352[32];
    SfdDecodeFlags decode;
    char pad2432[24];
    long f2456;
    long f2464;
    long f2472;
    char pad2480[64];
    SfdDecStat stat;
    SfdPending pending;
    char pad2740[628];
    SfdTimer timer;
    char pad4824[976];
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
    long f0;
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

typedef struct SfdFrameInfo {
    int f0;
    int f4;
    int f8;
    int f12;
    int f16;
    int f20;
    int f24;
    int f28;
    int f32;
    int f36;
    int f40;
    int f44;
    int f48;
    int f52;
    int f56;
    int f60;
    int f64;
    char pad68[4];
    int f72;
    char pad76[4];
    long f80;
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
} SfdFrameInfo;

#endif
