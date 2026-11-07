struct R { int w0; R() {} R(int v) { w0 = v; } bool operator==(const R &o) const { return w0 == o.w0; } };
class Resolver { public:
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual int IsReady();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual R Lookup(int addr, char *buf, int size, int *base, int *other, char *name, int nameSize, int *line);
};
extern "C" {
int sprintf(char *, const char *, ...);
char *strncpy(char *, const char *, unsigned int);
extern char DAT_004f95a8[];
extern R DAT_004fb410[4];
extern R DAT_004fb418[4];
extern char *DAT_00586dc8[4];
R Gap__Core__igCallStackTracer__vfunc_27(void *self, int addr, char *buf, int size, int *offset, char *name, int nameSize, int *line);
}
R Gap__Core__igCallStackTracer__vfunc_27(void *self, int addr, char *buf, int size, int *offset, char *name, int nameSize, int *line) {
    Resolver *r = *(Resolver **)(DAT_00586dc8[0] + 80);
    if (r != 0 && r->IsReady() != 0) {
        int base = 0;
        int other = 0;
        if (r->Lookup(addr, buf, size, &base, &other, name, nameSize, line) == DAT_004fb410[0]) {
            *offset = addr - base;
            return DAT_004fb410[0];
        }
    }
    if (buf != 0) {
        char tmp[20];
        sprintf(tmp, DAT_004f95a8, addr);
        strncpy(buf, tmp, size);
    }
    *offset = 0;
    if (name != 0) {
        *name = 0;
    }
    *line = 0;
    return DAT_004fb418[0];
}
