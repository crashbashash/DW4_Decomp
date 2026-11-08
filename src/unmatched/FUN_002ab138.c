typedef struct { char pad[644]; int f644; int f648; } S;
extern int FUN_002ab218(void *h);
extern int FUN_002adc40(void *h, int k);
extern int FUN_002ab2b8(void *h);
extern int FUN_002ab370(void *h);
extern int FUN_002ae968(void *h, int *a, int *b);
extern int FUN_002916f8(int a, int b, int c);
extern int FUN_002aed60(int a, int b, int c, int d);
int FUN_002ab138(char *h) {
    int v[2];
    S *s;
    int a, b;
    if (FUN_002ab218(h) != 0) return 1;
    if (FUN_002adc40(h, 5) == 1 && FUN_002ab2b8(h) != 0) return 1;
    if (FUN_002adc40(h, 6) == 1 && FUN_002ab370(h) != 0) return 1;
    FUN_002ae968(h, &v[0], &v[1]);
    s = (S *)(h + 0xD28);
    a = s->f648;
    b = s->f644;
    return FUN_002aed60(v[0], v[1], b - FUN_002916f8(FUN_002adc40(h, 69), a, 1000000), a) != 0;
}
