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
    char pad0[28];
    SfdTimeCode tc;
    SfdTimeStamp state;
    SfdTimeStamp best;
    SfdTimeStamp f148;
    SfdTimeStamp cur;
    SfdTimeStamp latest;
    SfdTimeStamp f280;
    char pad324[12];
    int f336;
    char pad340[12];
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
    char pad52[32];
    unsigned char f84;
    char pad85[2];
    signed char f87;
    signed char f88;
    char pad89[39];
} SfdPicInfo;

typedef struct SfdPicSummary {
    int f0;
    int f4;
    int f8;
    int f12;
    int f16;
    int f20;
    int f24;
    short f28;
    short f30;
} SfdPicSummary;

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

typedef struct SfdSlotInfo {
    int f0;
    int f4;
    int f8;
    int f12;
    int rateIndex;
    int f20;
    int kind;
    int f28;
} SfdSlotInfo;

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
    SfdSlotInfo info;
    char pad120[104];
    int f224;
    int pad228;
} SfdSlot;

typedef struct SfdBufPool {
    char *base;
    int count;
    int size;
    SfdChunk slot[18];
} SfdBufPool;

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

typedef struct SfdIpuCtl {
    int enabled;
    int f4;
    int f8;
    int f12;
    char pad16[4];
    int endRequest; /* 20 */
    int endSent;    /* 24 */
    int stopped;
    int value;
} SfdIpuCtl;

typedef struct SfdMpegCtx {
    int f0;
    int f4;
    int f8;
    char pad12[60];
} SfdMpegCtx;

typedef struct SfdIpuStream {
    int base;
    unsigned int uncached;
    int sectors;
    int f12;
    int queuedSct;
    int restBytes;
    int bytes;
    int r28;
    int r32;
    int r36;
    int r40;
    int r44;
    int r48;
    int r52;
    int r56;
    int r60;
    int sema;
    int f68;
    long f72;
    int f80;
    int f84;
} SfdIpuStream;

typedef struct SfdIpuEvent {
    int f0;
    int f4;
} SfdIpuEvent;

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
    char pad280[72];
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
    int pad4300;
    SfdMpegCtx mpeg;
    SfdIpuStream stream;
    char pad4464[8];
    SfdIpuEvent event;
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
    char pad4[20];
    int f24;
    char pad28[8];
    int f36;
    char pad40[4];
    int f44;
} SfdDecodeFlags;

typedef struct SfdPending {
    char pad0[8];
    int f8;
    int f12;
    int f16;
    char pad20[72];
    int f92;
    char pad96[72];
    int f168;
    int f172;
} SfdPending;

typedef struct SfdPicRecord {
    int f0;
    int f4;
    char body[128];
} SfdPicRecord;

typedef struct SfdStreams {
    int f0;
    int f4;
    void *mpv;
    int f12;
    int f16;
    int f20;
    int pad24[2];
    int f32;
} SfdStreams;

typedef struct SfdLink {
    int f0;
    int id;
    int arg;
} SfdLink;

typedef struct SfdPlayer {
    char pad0[40];
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
    char pad2480[84];
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
    char pad0[20];
    int f20;
    int f24;
} SfdFrameInfo;

#endif
