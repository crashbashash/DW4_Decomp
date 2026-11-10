typedef struct SjObj SjObj;

typedef struct SjVtbl {
    char pad0[36];
    int (*getNumData)(SjObj *sj, int id); /* 36 */
} SjVtbl;

struct SjObj {
    SjVtbl *vtbl;
};

typedef struct SfdCrePrm {
    int f0;
    int f4;
    char pad8[52];
    char *work;            /* 60 */
    unsigned int workSize; /* 64 */
} SfdCrePrm;

typedef struct SfdRec48 {
    int f0;
    int f4;
    int f8;
    int f12;
    int f16;
    int f20;
    int f24;
    int enabled; /* 28 */
    int f32;
    int id36;    /* 36 */
    int id40;    /* 40 */
    int id44;    /* 44 */
} SfdRec48;

typedef struct SfdSub24 {
    long f0;
    long f8;
    long f16;
} SfdSub24;

typedef struct SfdTimer {
    int count;       /* 0 */
    int count2;      /* 4 */
    int f8;
    int f12;
    int f16;
    int f20;
    int f24;
    int active;      /* 28 */
    int activations; /* 32 */
    int f36;
    int f40;
    int f44;
    SfdSub24 sub[4]; /* 48 */
} SfdTimer;

typedef struct SfdErrBlk {
    int f0;
    int f4;
    char pad8[12];
} SfdErrBlk;

typedef struct SfdCond {
    int f0;
    int f4;
    int f8;
    int f12;
    int f16;
    int req1;    /* 20 */
    int req2;    /* 24 */
    int f28;
    int f32;
    char pad36[20];
    int f56;
    int mode;    /* 60 */
    char pad64[16];
    int request; /* 80; -4 = none */
    int value;   /* 84 */
    char pad88[92];
    int f180;
    char pad184[216];
} SfdCond;

typedef struct SfdTriple {
    int f0;
    int f4;
    int f8;
} SfdTriple;

typedef struct SfdD28 {
    char pad0[16];
    int f16;
    char pad20[4];
    int f24;
    char pad28[616];
    int f644;
    int f648;
    char pad652[32];
    int f684;
    int f688;
    char pad692[24];
    int f716;
    char pad720[4];
    int f724;
    char pad728[12];
    int f740;
    int f744;
    char pad748[708];
    SfdTriple f1456;
    char pad1468[36];
} SfdD28;

typedef struct SfdItem {
    long pos;          /* 0; negative = none */
    unsigned int addr; /* 8 */
    unsigned int size; /* 12 */
} SfdItem;

typedef struct SfdRing {
    SfdItem *items; /* 0 */
    int size;       /* 4 */
    int count;      /* 8 */
    int wr;         /* 12 */
    int rd;         /* 16 */
} SfdRing;

typedef struct SfdStmInf {
    int f0;
    SjObj *sj;         /* 4 */
    int base;          /* 8 */
    int size;          /* 12 */
} SfdStmInf;

typedef struct SfdStmEnt {
    char pad0[16];
    SfdStmInf info; /* 16 */
    char pad32[24];
    SfdRing ring;   /* 56 */
    char pad76[40];
} SfdStmEnt;

typedef struct SfdF28 {
    char pad0[20];
    int f20;
    char pad24[128];
    int f152;
    char pad156[64];
    int f220;
    char pad224[5664];
} SfdF28;

typedef struct SfdRec SfdRec;

typedef struct SfdRecSub {
    int f0;
    int f4;
    int f8;
} SfdRecSub;

typedef struct SfdRecSlot {
    SfdRec *rec;   /* 0 */
    SfdRecSub sub; /* 4 */
} SfdRecSlot;

typedef struct SfdRecB2208 {
    int f0;
    int f4;
    int f8;
    int f12;
    int f16;
    int f20;
    long f24;
    long f32;
    int f40;
    int f44;
} SfdRecB2208;

typedef struct SfdRecB2768 {
    int f0;
    int f4;
    int f8;
} SfdRecB2768;

typedef struct SfdRecB3340 {
    int f0;
    int f4;
    int f8;
    int f12;
    int f16;
    int f20;
} SfdRecB3340;

struct SfdRec {
    int state;            /* 0 */
    int f4;
    int f8;
    char blk12[2196];     /* 12 */
    SfdRecB2208 b2208;    /* 2208 */
    char pad2256[512];
    SfdRecB2768 b2768;    /* 2768 */
    char blk2780[560];    /* 2780 */
    SfdRecB3340 b3340;    /* 3340 */
    char pad3364[132];
    int f3496;
    int f3500;
    int f3504;
    int f3508;
    int f3512;
    int f3516;
    int f3520;
    int f3524;
    int f3528;
    int f3532;
    int f3536;
    int f3540;
};

typedef struct SfdTblEnt {
    char pad0[32];
} SfdTblEnt;

typedef struct SfdTable {
    SfdTblEnt ent[5];  /* 0 */
    char trailer[64];  /* 160 */
} SfdTable;

typedef struct SfdPlyInf {
    char pad0[20];
    int f20;
    char pad24[8];
} SfdPlyInf;

typedef struct SfdPly SfdPly;

struct SfdPly {
    SfdCrePrm cre;        /* 0 */
    int pending;          /* 68 */
    int stat;             /* 72 */
    int reqStat;          /* 76 */
    int pause;            /* 80 */
    int pauseCnt;         /* 84 */
    char pad88[32];
    char blk120[2196];    /* 120 */
    SfdRec48 rec2316;     /* 2316 */
    char pad2364[20];
    SfdTimer tmr;         /* 2384 */
    char pad2528[16];
    SfdErrBlk err;        /* 2544 */
    SfdCond cond;         /* 2564 */
    SfdCond cond2;        /* 2964 */
    char pad3364[4];
    SfdD28 d28;           /* 3368 */
    SfdStmEnt ent[8];     /* 4872 */
    char pad5800[2176];
    SfdF28 f28;           /* 7976 */
    SfdRecSlot recSlot;   /* 13864 */
    SfdTable tbl;         /* 13880 */
};
