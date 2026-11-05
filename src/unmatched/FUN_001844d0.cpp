typedef struct R { int w0; int refs; } R;
class A4 {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); 
    virtual void v27(unsigned int, int *);
    virtual void w28(); virtual void w29(); virtual void w30(); virtual void w31(); virtual void w32(); virtual void w33(); virtual void w34(); virtual void w35(); virtual void w36(); virtual void w37(); virtual void w38(); virtual void w39(); virtual void w40(); virtual void w41(); virtual void w42(); virtual void w43(); virtual void w44(); virtual void w45(); virtual void w46(); virtual void w47(); virtual void w48(); virtual void w49(); virtual void w50(); 
    virtual void v51(unsigned int, float);
    int pad[5]; R *obj;
};
class A5 {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); 
    virtual void v34(unsigned int, int *);
    int pad[5]; R *obj;
};
extern "C" {
int FUN_0015dae0(void *, unsigned int, float);
int FUN_00181840(int); int FUN_00181850(int); int FUN_001818a0(int); int FUN_001818b0(int);
int FUN_00181b30(float *, int, int, int, float, float);
int FUN_00181b50(int);
int FUN_00183f60(int *, int, int, int, float, float);
int FUN_00183fc0(int);
void igObject_Destroy(R *);
void FUN_001844d0(int arg0, unsigned int arg1, int arg2, int arg3, A4 *arg4, A5 *arg5, float fparg0) {
    float spAC;
    int spA0[3];
    float temp_f20 = fparg0 * fparg0;
    unsigned int i = arg1;
    if (arg5 != 0) {
        R *o;
        unsigned int end;
        if (arg4 != 0) {
            ((R *)arg4)->refs += 1;
        }
        o = arg5->obj;
        if (o != 0) {
            o->refs -= 1;
            if (((unsigned long long)(long long)o->refs & 0x7fffffULL) == 0) {
                igObject_Destroy(o);
            }
        }
        arg5->obj = (R *)arg4;
        end = i + arg0;
        for (; i < end; i++) {
            int p; int a; int b;
            p = arg2 + (i * arg3);
            a = FUN_001818b0(p);
            b = FUN_001818a0(p);
            FUN_00183f60(spA0, a, b, FUN_00183fc0(p), fparg0, temp_f20);
            a = FUN_00181850(p);
            b = FUN_00181840(p);
            FUN_00181b30(&spAC, a, b, FUN_00181b50(p), fparg0, temp_f20);
            arg5->v34(i, spA0);
            FUN_0015dae0(arg5, i, spAC);
        }
        o = arg5->obj;
        if (o != 0) {
            o->refs -= 1;
            if (((unsigned long long)(long long)o->refs & 0x7fffffULL) == 0) {
                igObject_Destroy(o);
            }
        }
        arg5->obj = 0;
        return;
    }
    {
    int p; unsigned int end2; int a; int b;
    end2 = i + arg0;
    for (; i < end2; i++) {
        p = arg2 + (i * arg3);
        a = FUN_001818b0(p);
        b = FUN_001818a0(p);
        FUN_00183f60(spA0, a, b, FUN_00183fc0(p), fparg0, temp_f20);
        a = FUN_00181850(p);
        b = FUN_00181840(p);
        FUN_00181b30(&spAC, a, b, FUN_00181b50(p), fparg0, temp_f20);
        arg4->v27(i, spA0);
        arg4->v51(i, spAC);
    }
    }
}
}
