#include "dw4/reflected.h"
extern "C" {
extern igMetaObject *DAT_0055efe8[4];
long long FUN_00398e80(...);
int igMatrix44f_SetIdentity(...);
int FUN_001904f0(...);
int FUN_001dca40(...);
int List_Resize(...);
int FUN_001b1490(...);
int FUN_001b12f0(...);
int FUN_001b13d0(...);
int FUN_001e07a0(...);
int FUN_001356b0(...);
int FUN_00130f20(...);
}
class Ctl;
extern "C" int FUN_00398ef0(beModelCtrlNode2 *self, Ctl *ctl);

struct Ls { char p0[8]; volatile int cnt; int cap; int *data; int cur; };
struct Pool { char p0[8]; int cap; char p1[4]; int *data; int cur; };
struct Tb { char p0[16]; Ls **data; };
struct Q { char p0[8]; int n; char p1[4]; int *a; char p2[8]; int (*cb)(int, int); };
struct Mgr { char p0[16]; Tb *tb; char p1[28]; int f48; char p2[16]; int *base; };
struct Mat;
class Ent { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
 virtual void v30(char *m);
 int refc; short idx; short off; char p1[4]; long long clk; };
class Ctl { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
 virtual long long v24();
 virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
 virtual void v30(long long t); virtual void v31();
 char p0[48]; Mgr *mgr; char p1[16]; Pool *pa; Pool *pb; };

/* matching construct: the volatile read re-loads the 4-byte _overrideAttrList reference on every use (retail re-reads it per iteration); the igAttrList cast stands in for the reference field type */
#define OV ((igAttrList *)*(volatile int *)&self->_overrideAttrList)
extern "C" int FUN_00398ef0(beModelCtrlNode2 *self, Ctl *ctl) {
    long long t;
    short *ai;
    short *ao;
    Mgr *mgr;
    Ls *tgt;
    Ent *ea;
    Ent *eb;
    int idx;
    int s6;
    int s7;
    int n;
    int i;
    int j;
    int l;
    int jo;
    int lo;
    short *bi;
    short *bo;
    int r;
    Q *q;
    Q *top;
    int k;
    int *ta;
    int x;
    int (*cb)(int, int);
    char mat[64];
    char tmp[64];
    Ent * volatile sa;
    Ent * volatile sb;

    mgr = ctl->mgr;
    idx = DAT_0055efe8[0]->_id;
    top = (Q *)mgr->tb->data[mgr->base[idx]];
    t = FUN_00398e80(self, ctl->v24());
    self->_time = t;
    igMatrix44f_SetIdentity(mat);
    if (top->n != 0) {
        k = top->n - 1;
        ta = top->a;
        FUN_001904f0(mat, (char *)self->_m, ta[k] + 12);
    } else {
        igMatrix44f_SetIdentity(tmp);
        FUN_001904f0(mat, (char *)self->_m, tmp);
    }
    {
        Pool *p = ctl->pa;
        if (p->cur >= p->cap) FUN_001dca40(p, FUN_001356b0);
        i = p->cur;
        p->cur = i + 1;
        ea = (Ent *)p->data[i];
    }
    ea->v30(mat);
    {
        Pool *p = ctl->pb;
        if (p->cur >= p->cap) FUN_001dca40(p, FUN_00130f20);
        i = p->cur;
        p->cur = i + 1;
        eb = (Ent *)p->data[i];
    }
    eb->clk = t;
    ctl->v30(t);

    ao = &ea->off;
    ai = &ea->idx;
    s6 = ea->off + mgr->base[ea->idx];
    tgt = mgr->tb->data[s6];
    sa = ea;
    n = tgt->cnt;
    if (n < tgt->cap) tgt->cnt = tgt->cnt + 1; else List_Resize(tgt, n + 1, 4);
    tgt->data[n] = (int)sa;
    FUN_001b1490(mgr, tgt, s6);

    bi = &eb->idx;
    bo = &eb->off;
    s7 = eb->off + mgr->base[eb->idx];
    tgt = mgr->tb->data[s7];
    sb = eb;
    n = tgt->cnt;
    if (n < tgt->cap) tgt->cnt = tgt->cnt + 1; else List_Resize(tgt, n + 1, 4);
    tgt->data[n] = (int)sb;
    FUN_001b1490(mgr, tgt, s7);

    j = 0;
    if (j < OV->_count) {
        jo = 0;
        do {
            FUN_001b12f0(mgr, *(int *)(OV->_data + jo));
            j++;
            jo += 4;
        } while (j < OV->_count);
    }
    r = FUN_001e07a0(ctl, self);
    for (l = OV->_count - 1, lo = l * 4; l >= 0; l--) {
        FUN_001b13d0(mgr, *(int *)(OV->_data + lo));
        lo -= 4;
    }
    {
        int pb = *bo + mgr->base[*bi];
        Q *qb = (Q *)mgr->tb->data[pb];
        int kb = qb->n - 1;
        int *tab = qb->a;
        int xb = tab[kb];
        int (*cbb)(int, int) = qb->cb;
        if (cbb != 0) cbb(xb, mgr->f48);
        qb->n = qb->n - 1;
        FUN_001b1490(mgr, qb, pb);
    }
    {
        int pa = *ao + mgr->base[*ai];
        Q *qa = (Q *)mgr->tb->data[pa];
        int ka = qa->n - 1;
        int *taa = qa->a;
        int xa = taa[ka];
        int (*cba)(int, int) = qa->cb;
        if (cba != 0) cba(xa, mgr->f48);
        qa->n = qa->n - 1;
        FUN_001b1490(mgr, qa, pa);
    }
    ctl->v31();
    if (r == 2) return 2;
    return 0;
}
