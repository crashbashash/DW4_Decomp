/* adxt_trap_entry (hypothesis): the only string in the body is
 * "E8101201 adxt_trap_entry: not enough data" (D_004eedd0). Pulls the next
 * block from the stream joint, re-primes the ring and bumps the entry counter. */
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
extern int FUN_002672e8(void *);
extern int FUN_00267300(void *);
extern int FUN_00267330(void *);
extern void FUN_002671c8(void *, int);
extern void FUN_002671d8(void *, int);
extern void FUN_002671e8(void *, int);
extern void FUN_002670e0(void *, int);
extern void FUN_002674d0(void *);
extern void FUN_002607e8(const char *);

void FUN_0026dae0(Adxt *t)
{
    void *rt = t->rt;
    SjObj *sj = t->sj;
    int a, b, c;
    SjChunk ck;

    a = FUN_002672e8(rt);
    b = FUN_00267300(rt);
    c = FUN_00267330(rt);
    if ((unsigned char)(t->state - 2) < 2 && t->b108 == 0) {
        FUN_002671c8(t->rt, -1);
        return;
    }
    sj->vt->f24(sj, 1, t->reqLen, &ck);
    if (ck.len < t->reqLen)
        FUN_002607e8(D_004eedd0);
    sj->vt->f32(sj, 0, &ck);
    FUN_002671d8(rt, 0);
    t->w144 = c - a;
    FUN_002671c8(rt, t->w144);
    FUN_002671e8(rt, b);
    FUN_002670e0(rt, a);
    if (t->state == 2) {
        sj->vt->f20(sj);
        sj->vt->f24(sj, 1, b, &ck);
        sj->vt->f32(sj, 0, &ck);
    }
    FUN_002674d0(rt);
    t->w76++;
}
