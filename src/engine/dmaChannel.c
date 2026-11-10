int FUN_001efec0();
void FUN_001f00e0(int);
int FUN_001f0390(void);
int FUN_00204240();
int FUN_00113f20();
int FUN_00113f78();
int iReferSemaStatus();
int iSignalSema();

typedef struct N { int pad[3]; int f12; int f16; struct N *f20; } N;
struct ProcNode { long long a; int pad; int next; int fn; };
struct ProcList { char pad[16]; struct ProcNode *head; };
typedef struct PoolNode { int pad0; struct PoolNode *next; int pad2[4]; struct PoolNode *head; } PoolNode;
struct S { char pad[64]; unsigned char f64; };
struct S2 { long long f0; char pad[56]; unsigned char b0:1; unsigned char b1:1; unsigned char b2:6; };
struct P { int a; int b; };

extern void *DAT_00568f60[4];
extern int DAT_005691b8[4];
extern void *DAT_005691c0[4];
extern char DAT_005690b8[];
extern char GPR_00554bbc;
extern int DAT_0056bf38[4];
extern void *DAT_00568f04[4];
extern struct P DAT_005691d0[16];
extern long long DAT_00568fe8[4];
extern long long DAT_00568ff0[4];
extern char DAT_00568f00[];
extern long long DAT_00568fe0[4];
extern int DAT_00569030[4];
extern void *DAT_00568f34[4];
extern int DAT_00490cc0[4];
extern int DAT_00569120[4];
extern long long DAT_00569040[4];
extern long long DAT_00568f90[4];
int FlushCache(int);
int FUN_00204100(int);
int FUN_00330770();
typedef struct ChanView { long long v; char pad0[24]; int w32; char pad1[12]; int w48; char pad2[12]; unsigned char b0:1; unsigned char b1:1; unsigned char b2:1; unsigned char b3:1; unsigned char b4:1; unsigned char b5:1; unsigned char b6:1; unsigned char b7:1; } ChanView;
typedef struct Desc { char p0[16]; int f16; char p1[8]; void *f28; char p2[20]; struct Desc *next; char p3[8]; unsigned char lo : 4; unsigned char flag : 1; unsigned char hi : 3; } Desc;

void FUN_001efd90(int channel, int (*callback)(long long), long long data) {
    N *c = ((N **)DAT_00568f00)[channel];
    N *n;
    unsigned int status;
    if (DAT_005691b8[0] == 0) {
        FUN_00204240(7, &DAT_005691b8[0]);
    }
    __asm__ volatile("mfc0 %0, $12\n\tsrl $6, %0, 16\n\tand %0, %0, $6" : "=r"(status) : : "$6");
    if (status & 1) {
        FUN_00113f20();
        n = (N *)DAT_005691b8[0];
        DAT_005691b8[0] = n->f12;
        FUN_00113f78();
    } else {
        n = (N *)DAT_005691b8[0];
        DAT_005691b8[0] = n->f12;
    }
    n->f16 = (int)callback;
    *(long long *)n = data;
    n->f12 = c->f16;
    if (c->f16 == 0) {
        c->f20 = n;
    }
    c->f16 = (int)n;
}

static void FUN_001efe70(int arg0) {
    N *temp_a1;

    temp_a1 = DAT_00568f60[arg0];
    if (temp_a1->f16 != 0) {
        temp_a1->f20->f12 = DAT_005691b8[0];
        DAT_005691b8[0] = temp_a1->f16;
        temp_a1->f16 = 0;
    }
}

int FUN_001efec0(int arg0) {
    int var_s0;
    int var_v0;
    struct ProcNode *var_s1;
    var_s1 = ((struct ProcList *)DAT_00568f60[arg0])->head;
    var_s0 = 1;
    while (var_s1 != 0) { var_v0 = ((int (*)(long long))var_s1->fn)(var_s1->a) != 0 ? 1 : 0; var_s0 &= var_v0; if (var_s0 == 0) break; var_s1 = (struct ProcNode *)var_s1->next; }
    return var_s0;
}

void FUN_001eff40(void) {
    DAT_005691c0[0] = 0;
    FUN_00204240(8, &DAT_005691c0[0]);
}

void FUN_001eff60(int arg0) {
    int i = 0;
    int *n = (int *)DAT_005691c0[0];
    while (i < arg0) {
        if (n == 0) break;
        n = (int *)n[1];
        i++;
    }
    if (i != arg0) {
        FUN_00204240(8, &DAT_005691c0[0], i);
    }
}

typedef struct Slot { int pad0; struct Slot *next; int f8; int f12; } Slot;

void FUN_001effc0(int channel, int value, int data) {
    char *c = ((char **)DAT_00568f00)[channel];
    Slot *n;
    unsigned int status;
    if (DAT_005691c0[0] == 0) {
        FUN_00204240(8, &DAT_005691c0[0]);
    }
    __asm__ volatile("mfc0 %0, $12\n\tsrl $6, %0, 16\n\tand %0, %0, $6" : "=r"(status) : : "$6");
    if (status & 1) {
        FUN_00113f20();
        n = (Slot *)DAT_005691c0[0];
        DAT_005691c0[0] = n->next;
        FUN_00113f78();
    } else {
        n = (Slot *)DAT_005691c0[0];
        DAT_005691c0[0] = n->next;
    }
    n->f8 = value;
    n->f12 = data;
    n->next = *(Slot **)(c + 24);
    *(Slot **)(c + 24) = n;
}

void FUN_001f0090(int arg0) {
    PoolNode *temp_a2;
    PoolNode *var_a1;
    PoolNode *temp_a0;

    temp_a2 = DAT_00568f60[arg0];
    var_a1 = temp_a2->head;
    while (var_a1 != 0) {
        temp_a0 = var_a1->next;
        var_a1->next = DAT_005691c0[0];
        DAT_005691c0[0] = var_a1;
        var_a1 = temp_a0;
    }
    temp_a2->head = 0;
}

void FUN_001f0310(int arg0) {
    struct S *temp_a1;
    temp_a1 = (struct S *)DAT_00568f60[arg0];
    if (DAT_005690b8[arg0] != 0 && (temp_a1->f64 & 1) && FUN_001efec0(arg0) != 0 && GPR_00554bbc == 0) {
        FUN_001f00e0(arg0);
    }
}

int FUN_001f0390(void) {
    return DAT_0056bf38[0];
}

static inline int b1_of(const struct S2 *s) { return s->b1; }
long long FUN_001f03a0(void) {
    struct S2 *s = DAT_00568f04[0];
    unsigned char t;
    if (b1_of(s) != 1) {
        t = *(unsigned char *)((char *)s + 64);
        s->b1 = 1;
        FUN_001efd90(1, (int (*)(long long))FUN_001f0390, 0);
    }
    return s->f0;
}

void FUN_001f0410(int arg0, int arg1) {
    int i = 0;
    while (i < 10 && DAT_005691d0[i].a != 0) {
        i += 1;
    }
    DAT_005691d0[i].a = arg0;
    DAT_005691d0[i].b = arg1;
}

int FUN_001f0470(long long arg0) {
    return DAT_00568fe8[0] >= arg0;
}

int FUN_001f0490(long long arg0) {
    return DAT_00568ff0[0] >= arg0;
}

#define DAT_00568f60 ((char *)DAT_00568f60)
int FUN_001f04b0(int arg0, int arg1) {
    int temp_a2;
    int temp_a0;
    int var_v0;

    temp_a0 = arg0 * 4;
    temp_a2 = *(int *)(DAT_00568f60 + temp_a0);
    var_v0 = 0;
    if ((temp_a2 != 0) && (arg1 != 0) && (*(int *)(DAT_00568f00 + temp_a0) != temp_a2) && (arg1 != temp_a2)) {
        var_v0 = 1;
    }
    return var_v0;
}
#undef DAT_00568f60

int FUN_001f0500(int arg0, long long arg1) {
    return arg1 == DAT_00568fe0[arg0];
}

void FUN_001f0520(void) {
    int buf[8];

    iReferSemaStatus(DAT_00569030[0], buf);
    if (buf[0] != buf[1]) {
        iSignalSema(DAT_00569030[0]);
    }
}

long long FUN_001f0560(void) {
    ChanView *p;
    long long r;
    p = DAT_00568f04[0];
    r = p->v;
    if (p->w48 == p->w32) {
        p = DAT_00568f34[0];
        r = p->v;
    }
    p->b2 = 1;
    return r;
}

int FUN_001f0710(int arg0, long long arg1) {
    return DAT_00568fe0[arg0] >= arg1;
}

void FUN_001f0730(void) {
    int i;
    int o8;
    Desc *p;
    Desc *q;
    Desc **pp;
    int o;
    Desc *prev;
    FlushCache(0);
    i = 0;
    do {
        FUN_00204100(i);
        o = i * 4;
        *(int *)((char *)DAT_00490cc0 + o) = -1;
        *(int *)((char *)DAT_00569120 + o) = -1;
        pp = (Desc **)((char *)DAT_00568f00 + o);
        p = *pp;
        do {
            FUN_00330770(p->f28, 22);
            p->f28 = 0;
            if (p->f16 == 0 && i == 2) FUN_001efe70(i);
            p = p->next;
            q = *pp;
        } while (p != q);
        while (!q->flag) q = q->next;
        p = q->next;
        prev = q;
        do {
            if (prev != 0 && prev->flag && !p->flag) prev->next = p->next;
            else if (prev != 0 && prev->flag && p->flag) prev = p;
            p = p->next;
        } while (p != q);
        do {
            Desc *t = p;
            p = p->next;
            FUN_00330770(t, 22);
        } while (p != q);
        o8 = i * 8;
        *pp = 0;
        *(long long *)((char *)DAT_00568fe0 + o8) = -1;
        *(long long *)((char *)DAT_00568f90 + o8) = -1;
        *(long long *)((char *)DAT_00569040 + o8) = 0;
        *(DAT_005690b8 + i) = 1;
        i++;
        *(int *)((char *)DAT_00568f60 + o) = 0;
    } while (i <= 2);
}

static asm void FUN_001f0930(void)
{
wait:
    nop
    nop
    nop
    nop
    nop
    bc0f    wait
    nop
    jr      ra
    nop
}
