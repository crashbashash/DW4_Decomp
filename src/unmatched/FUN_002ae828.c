typedef struct { int f0; char pad[32]; int a; int b; } T1;
typedef struct { char pad[324]; int f324; int f328; } T3;
extern int FUN_002ae950(void *h, int *a, int *b);
extern int FUN_002916f8(int a, int b, int c);
int FUN_002ae828(char *h, int *acc, int *v) {
    T1 *t1 = (T1 *)(h + 0xE40);
    T3 *t3 = (T3 *)(h + 0xD28);
    int r = FUN_002ae950(h, acc, v);
    int k = *v;
    if (k == 1) return r;
    if (k == t3->f328) {
        *acc += t3->f324;
    } else if (t1->f0 != 0) {
        *acc += FUN_002916f8(t1->a, k, t1->b);
    }
    return r;
}
