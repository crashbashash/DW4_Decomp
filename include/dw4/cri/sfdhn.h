#ifndef SFDHN_H
#define SFDHN_H

#include "dw4/cri/sfdsj.h"

/* A stream header's audio stream. */
typedef struct SfdHdrAudio {
    int codec;
    int nch;
    int bps;
    int sfreq;
} SfdHdrAudio;

/* A stream header's multiplexing description. */
typedef struct SfdHdrMux {
    int kind[4];
    int numFrm;
    int totalTime;
    int timeUnit;
} SfdHdrMux;

/* A stream header's video stream. */
typedef struct SfdHdrVideo {
    int codec;      /* 0 */
    int bitRate;    /* 4 */
    int width;      /* 8 */
    int height;     /* 12 */
    int frameRate;  /* 16 */
    int avail;      /* 20: the rest is read only when the stream says it is available */
    int picType;    /* 24 */
    int profile;    /* 28 */
    int flag0;      /* 32 */
    int flag4;      /* 36 */
    int chroma;     /* 40 */
    int zFirst;     /* 44 */
    int zSecond;    /* 48 */
} SfdHdrVideo;

/* What the CRI header in private stream 2 says about a movie, and the header bytes it was read from. */
typedef struct SfdHdrInf {
    int valid;           /* 0 */
    int verMajor;        /* 4 */
    int verMinor;        /* 8 */
    int muxRate;         /* 12: bytes per second; negative before version 1.10 */
    int bitRate;         /* 16 */
    int sysType;         /* 20 */
    int numStm;          /* 24 */
    int totalSize;       /* 28 */
    SfdHdrMux mux;       /* 32 */
    int adxStm;          /* 60: stream id 0xBD when present */
    int prv2Stm;         /* 64: stream id 0xBF when present */
    int audioStm;        /* 68: the first id in 0xC0..0xDF */
    int videoStm;        /* 72: the first id in 0xE0..0xEF */
    SfdHdrAudio audio;   /* 76 */
    SfdHdrVideo video;   /* 92 */
    int size;            /* 144 */
    char data[2048];     /* 148 */
} SfdHdrInf;

/* The picture-user text block of a picture record: two texts and their lengths. */
typedef struct SfdPicTxt {
    char text[2][176];   /* 0 */
    int len[2];          /* 352 */
} SfdPicTxt;

/* The picture record kept in the work record: its times and its user texts. */
typedef struct SfdPicRec {
    int valid;           /* 0 */
    int bps;             /* 4 */
    int f8;
    int videoBound;      /* 12 */
    int audioBound;      /* 16 */
    int f20;
    long baseTime;       /* 24 */
    long startPts;       /* 32 */
    int f40;
    int f44;
    SfdPicTxt txt;       /* 48 */
} SfdPicRec;

/* The work record at handle +13864: a copy of the header and of the last picture record. */
typedef struct SfdWork {
    int state;           /* 0 */
    int f4;
    int f8;
    SfdHdrInf hdr;       /* 12 */
    SfdPicRec pic;       /* 2208 */
} SfdWork;

/* The video settings at handle +2316 the header and the stream fill in; -1 is unset. */
typedef struct SfdVideoInf {
    char pad0[24];
    int muxRate;         /* 24 */
    int f28;
    int f32;
    int audioBound;      /* 36 */
    int videoBound;      /* 40 */
    int f44;
} SfdVideoInf;

/* An error block: the first code recorded and the callback told about each error. */
typedef struct SfdErrInf {
    void (*func)(void *obj, int code);  /* 0 */
    void *obj;                          /* 4 */
    int code;                           /* 8 */
    int f12;
    int f16;
} SfdErrInf;

/* The running total of decoded amounts with the totals of the last 32 additions. */
typedef struct SfdSyncTally {
    int total;           /* 0 */
    int count;           /* 4 */
    int history[32];     /* 8 */
} SfdSyncTally;

/* The 32-entry queue of time stamps the audio handler hands to the video handler. */
typedef struct SfdSyncQueue {
    int last;            /* 0 */
    int f4;
    int wr;              /* 8 */
    int rd;              /* 12 */
    int items[32];       /* 16 */
} SfdSyncQueue;

/* The part of the time block at handle +3368 these files use. */
typedef struct SfdTimView {
    char pad0[320];
    int rate;            /* 320 */
    char pad324[12];
    long baseTime;       /* 336 */
    long ofsTime;        /* 344 */
    int f352;
    SfdSyncTally tally;  /* 356 */
    SfdSyncQueue queue;  /* 492 */
} SfdTimView;

/* A buffer channel's area description (sfdbuf.c). */
typedef struct SfdChanInf {
    char *data;          /* 0 */
    SfdSj *sj;           /* 4 */
    unsigned char *buf;  /* 8 */
    int size;            /* 12 */
    int xsize;           /* 16 */
    int f20;
} SfdChanInf;

/* A buffer channel at handle +4872 (sfdbuf.c). */
typedef struct SfdChan {
    int state;           /* 0 */
    int valid;           /* 4 */
    int f8;
    int f12;
    SfdChanInf inf;      /* 16 */
    char pad40[76];
} SfdChan;

/* The stream table of the MPS handler: an object per stream id 0xBC..0xFF and the callback run on its data. */
typedef struct SfdMpsPrm {
    void *mps;                              /* 0: the MPS demultiplexer */
    int videoBound;                         /* 4: the most video streams a system header announced */
    int audioBound;                         /* 8: the most audio streams a system header announced */
    int pad12;
    long startPts;                          /* 16 */
    long firstPts;                          /* 24; LONG_MAX when unset */
    int nPics;                              /* 32 */
    int f36;
    int f40;
    int f44;
    int f48;
    int videoCh;                            /* 52 */
    int audioCh;                            /* 56 */
    int f60;
    void *object[68];                       /* 64: indexed by stream id - 0xBC */
    int (*stmCb)(void *obj, int arg);       /* 336 */
    void *stmCbObj;                         /* 340 */
    int f344;
} SfdMpsPrm;

/* A module's place in the per-handle stream graph at +7976: its work and the channels it reads and writes. */
typedef struct SfdTrnSlot {
    int f0;
    int f4;
    void *work;          /* 8 */
    void *fns;           /* 12 */
    int from;            /* 16 */
    int outputs[3];      /* 20 */
    int f32;
    char pad36[32];
} SfdTrnSlot;

/* The MPS module's place in the stream graph: the same slot with its work typed. */
typedef struct SfdMpsSlot {
    int f0;
    int f4;
    SfdMpsPrm *prm;      /* 8 */
    void *fns;           /* 12 */
    int from;            /* 16: the channel it demultiplexes */
    int outputs[3];      /* 20: video, audio and user-data channels */
    int f32;
    char pad36[32];
} SfdMpsSlot;

/* A user-data output of a channel: the ring it goes into and the callbacks run around each put. */
typedef struct SfdUoch {
    SfdSj *sj;
    void (*begin)(void *hn, int id);
    void (*end)(void *arg, int id);
    void *arg;
} SfdUoch;

/* The SFD handle as the core, header, supply and MPS files see it. */
typedef struct SfdHandle {
    char pad0[40];
    int zeroPad;             /* 40: the zero padding the demultiplexer skips */
    char pad44[28];
    int stat;                /* 72; made non-positive by an error */
    char pad76[44];
    SfdHdrInf hdr;           /* 120 */
    SfdVideoInf video;       /* 2316 */
    char pad2364[68];
    long readBytes;          /* 2432 */
    long demuxBytes;         /* 2440 */
    long demuxPacks;         /* 2448 */
    char pad2456[88];
    SfdErrInf err;           /* 2544 */
    int cond[100];           /* 2564 */
    char pad2964[404];
    SfdTimView tim;          /* 3368 */
    char pad4008[816];
    char audioFnObj[48];     /* 4824: handed to the application's audio-data callback */
    SfdChan chan[8];         /* 4872 */
    char pad5800[2176];
    SfdTrnSlot sup;          /* 7976: the supply module */
    SfdMpsSlot mps;          /* 8044: the MPS module */
    char pad8112[480];
    SfdMpsPrm mpsPrm;        /* 8592 */
    char pad8944[4920];
    SfdWork *work;           /* 13864 */
} SfdHandle;

#endif
