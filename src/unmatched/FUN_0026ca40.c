typedef struct CriStream CriStream;
typedef struct {
    void *pad0[9];
    int (*get_size)(CriStream *, int);
} StreamVtbl;
struct CriStream {
    StreamVtbl *vt;
};

typedef struct {
    char pad0[20];
    CriStream *sj;
} AdxtTime;

extern char DAT_004ee9a0[];
void FUN_002607e8(const char *message);
int FUN_0026bd20(AdxtTime *adxt);
int FUN_0026c378(AdxtTime *adxt);
int FUN_0026c328(AdxtTime *adxt);

float FUN_0026ca40(AdxtTime *adxt)
{
    float t;
    int n;
    int ch;

    t = 0.0f;
    if (adxt == 0) {
        FUN_002607e8(DAT_004ee9a0);
        return -1.0f;
    }
    if (FUN_0026bd20(adxt) >= 2 && adxt->sj != 0) {
        n = adxt->sj->vt->get_size(adxt->sj, 1);
        ch = FUN_0026c378(adxt);
        t = (float)(n / (ch * 18) * 32) / (float)FUN_0026c328(adxt);
    }
    return t;
}
