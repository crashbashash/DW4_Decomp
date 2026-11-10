#ifndef SFX_H
#define SFX_H

typedef struct SfxMem {
    char *data;
    int size;
} SfxMem;

typedef struct SfxChunk {
    int valid;
    char *data;
    int size;
} SfxChunk;

typedef struct SfxPlane {
    int addr;
    int pitch;
    int height;
    int f12;
} SfxPlane;

typedef struct SfxFrame {
    unsigned int frmfmt;
    SfxPlane plane[3];
} SfxFrame;

typedef void (*SfxZCbFn)(unsigned int *, unsigned int *, float, float);

typedef struct SfxZHn {
    int used;
    int zbit;
    SfxChunk info;
    int pad20;
    SfxChunk hdr;
    int pad36;
    SfxChunk vfrm;
    int pad52[2];
    float zmin;
    float zmax;
    SfxZCbFn cbfn;
    int cbarg;
} SfxZHn;

typedef struct SfxHn {
    int used;
    int compo;
    int f8;
    int width;
    int height;
    int f20;
    SfxChunk zinf;
    int pad36;
    SfxZHn *zhn;
    int f44;
    int f48;
    void *ahn;
    int f56;
    int f60;
    int tbl[4];
    int pad80[2];
    int work;
    int wksize;
    int sud[2];
    int f104;
    int f108;
    int pad112;
    int f116;
} SfxHn;

void FUN_002b3b38(void *obj, void *info, char *msg);
void FUN_002b4210(void);
void FUN_002b4268(void);
SfxZHn *FUN_002b4270(void);
void FUN_002b4358(SfxZHn *zhn, char *data, int size);
void FUN_002b4498(SfxZHn *zhn, int frame, int *first, int *second);
void FUN_002b4aa8(SfxZHn *zhn, float zmin, float zmax);
void FUN_002b4b40(SfxZHn *zhn, float *zmin, float *zmax);

#endif
