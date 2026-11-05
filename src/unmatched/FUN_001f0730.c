int FlushCache(int);
int FUN_00204100(int);
int FUN_00330770();
int FUN_001efe70(int);
typedef struct N { char p0[16]; int f16; char p1[8]; void *f28; char p2[20]; struct N *next; char p3[8]; unsigned char lo : 4; unsigned char flag : 1; unsigned char hi : 3; } N;
extern int DAT_00490cc0[4];
extern int DAT_00569120[4];
extern N *DAT_00568f00[4];
extern long long DAT_00568fe0[4];
extern long long DAT_00568f90[4];
extern long long DAT_00569040[4];
extern char DAT_005690b8[64];
extern int DAT_00568f60[4];
void FUN_001f0730(void) {
    int i;
    int o8;
    N *p;
    N *q;
    N **pp;
    int o;
    N *prev;
    FlushCache(0);
    i = 0;
    do {
        FUN_00204100(i);
        o = i * 4;
        *(int *)((char *)DAT_00490cc0 + o) = -1;
        *(int *)((char *)DAT_00569120 + o) = -1;
        pp = (N **)((char *)DAT_00568f00 + o);
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
            N *t = p;
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
