typedef struct SjObj SjObj;
typedef struct SjChunk { void *ptr; int len; } SjChunk;
typedef struct SjVT {
    char pad[20];
    void (*f20)(SjObj *);
    void (*f24)(SjObj *, int, int, SjChunk *);
    char pad28[4];
    void (*f32)(SjObj *, int, SjChunk *);
} SjVT;
struct SjObj { SjVT *vt; };

typedef struct Adxt {
    char pad0[2];
    char state;
    char pad3;
    void *rt;           /* 4 */
    char pad8[12];
    SjObj *sj;          /* 20 */
    char pad24[52];
    int w76;
    int reqLen;         /* 80 */
    char pad84[24];
    char b108;
    char pad109[35];
    int w144;
} Adxt;

extern const char D_004eedd0[];
extern int ADXSJD_GetLpStartPos(void *);
extern int FUN_00267300(void *);
extern int ADXSJD_GetLpEndPos(void *);
extern void ADXSJD_SetTrapNumSmpl(void *, int);
extern void ADXSJD_SetTrapCnt(void *, int);
extern void ADXSJD_SetTrapDtLen(void *, int);
extern void FUN_002670e0(void *, int);
extern void FUN_002674d0(void *);
extern void ADXERR_CallErrFunc1(const char *);

void FUN_0026dae0(Adxt *t)
{
    void *rt = t->rt;
    SjObj *sj = t->sj;
    int a, b, c;
    SjChunk ck;

    a = ADXSJD_GetLpStartPos(rt);
    b = FUN_00267300(rt);
    c = ADXSJD_GetLpEndPos(rt);
    if ((unsigned char)(t->state - 2) < 2 && t->b108 == 0) {
        ADXSJD_SetTrapNumSmpl(t->rt, -1);
        return;
    }
    sj->vt->f24(sj, 1, t->reqLen, &ck);
    if (ck.len < t->reqLen)
        ADXERR_CallErrFunc1(D_004eedd0);
    sj->vt->f32(sj, 0, &ck);
    ADXSJD_SetTrapCnt(rt, 0);
    t->w144 = c - a;
    ADXSJD_SetTrapNumSmpl(rt, t->w144);
    ADXSJD_SetTrapDtLen(rt, b);
    FUN_002670e0(rt, a);
    if (t->state == 2) {
        sj->vt->f20(sj);
        sj->vt->f24(sj, 1, b, &ck);
        sj->vt->f32(sj, 0, &ck);
    }
    FUN_002674d0(rt);
    t->w76++;
}
