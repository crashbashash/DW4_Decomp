typedef struct CriStream CriStream;
typedef struct {
    void *pad0[5];
    void (*stop)(CriStream *);
} StreamVtbl;
struct CriStream {
    StreamVtbl *vt;
};

typedef struct {
    char pad0[2];
    signed char stat;
    char pad3;
    int f4;
    int f8;
    char pad12[8];
    CriStream *f20;
    char pad24[124];
    int f148;
} CriAdxt;

extern char DAT_004ee5c8[];
extern void (*DAT_004a8e64)(CriAdxt *);
void FUN_002607e8(const char *message);
void FUN_002662c8(int);
void FUN_0026a0a0(int);
void FUN_00277278(int);
void FUN_0026bbc0(CriAdxt *);

void FUN_0026bc60(CriAdxt *adxt)
{
    if (adxt == 0) {
        FUN_002607e8(DAT_004ee5c8);
        return;
    }
    if (DAT_004a8e64 != 0) {
        FUN_002662c8(adxt->f4);
        DAT_004a8e64(adxt);
    }
    if (adxt->f8 != 0) {
        FUN_0026a0a0(adxt->f8);
    }
    if (adxt->stat == 4) {
        FUN_00277278(adxt->f148);
        if (adxt->f20 != 0) {
            adxt->f20->vt->stop(adxt->f20);
        }
    }
    FUN_0026bbc0(adxt);
}
