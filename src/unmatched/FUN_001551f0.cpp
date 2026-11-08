class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(char *); };
struct S { char pad0[32]; char *f32; char pad1[4]; char *f40; };
extern "C" {
int strcat(char *, char *);
int strcpy(char *, char *);
int strlen(char *);
int FUN_00300f50(void *, char *);
char *igObject_AllocateStorage(void *, int);
extern int DAT_004de6c8[4];
int FUN_001551f0(S *arg0, V *arg1) {
    char *s1;
    char *buf;
    int n;
    int n2;
    int tot;

    if (arg1->vX(arg0->f32) == 0) {
        s1 = arg0->f32;
        n = strlen(arg0->f40);
        n2 = n + strlen((char *)&DAT_004de6c8[0]);
        tot = strlen(s1);
        tot = tot + n2;
        buf = igObject_AllocateStorage(arg0, tot + 1);
        strcpy(buf, arg0->f40);
        strcat(buf, (char *)&DAT_004de6c8[0]);
        strcat(buf, arg0->f32);
        if (arg1->vX(buf) == 0) {
            FUN_00300f50(arg0, buf);
            return 0;
        }
        FUN_00300f50(arg0, buf);
    }
    return 1;
}
}
