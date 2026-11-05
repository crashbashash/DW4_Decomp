struct S { long long a, b, c; };
int CreateSema();
int DeleteSema();
int FUN_0020d270();
int FUN_0020d5f0();
int WaitSema();
extern struct S DAT_004918f0;
extern int DAT_0056c16c[4];
void FUN_0020d360(int arg0) {
    struct S s;
    long long t0;
    long long t1;
    int h;
    s = DAT_004918f0;
    h = CreateSema(&s);
    FUN_0020d5f0(h, arg0);
    FUN_0020d270(&t0);
    WaitSema(h);
    FUN_0020d270(&t1);
    DAT_0056c16c[0] += (int)(t1 - t0);
    DeleteSema(h);
}
