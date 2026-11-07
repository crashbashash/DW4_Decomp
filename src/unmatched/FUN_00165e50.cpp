extern "C" float sqrtf(float);
struct Mat;struct Self;struct V;
struct Fl { int b; };
struct Obj {
 virtual void v8();
 virtual void v12();
 virtual void v16();
 virtual void v20();
 virtual void v24();
 virtual void v28();
 virtual void v32();
 virtual void v36();
 virtual void v40();
 virtual void v44();
 virtual void v48();
 virtual void v52();
 virtual void v56();
 virtual void v60();
 virtual void v64();
 virtual void v68();
 virtual void v72();
 virtual void v76();
 virtual void v80();
 virtual void v84();
 virtual void v88();
 virtual void v92();
 virtual void v96(int *, int, int, Self *);
 virtual struct Fl *v100();
 virtual void v104();
 virtual void v108();
 virtual void v112();
 virtual void v116(int, V *);
 virtual void v120();
 virtual V *v124(int);
 virtual void v128(int, V *);
 virtual void v132();
 virtual V *v136(int);
 virtual void v140();
 virtual void v144();
 virtual void v148();
 virtual void v152();
 virtual void v156();
 virtual void v160();
 virtual void v164(int, int);
 virtual void v168();
 virtual int v172(int);
 virtual void v176();
 virtual void v180();
 virtual float v184(int, int);
 virtual void v188();
 virtual void v192();
 virtual unsigned char v196(int, int);
 virtual void v200(int, int, int);
 virtual void v204();
 virtual int v208(int, int);
 virtual void v212();
 virtual Mat *v216(int);
 virtual void v220();
 int pad[2]; int count; int pad2; int count2;
};
struct V { float x, y, z;
 void operator=(const V &o) { (&x)[0] = (&o.x)[0]; (&x)[1] = (&o.x)[1]; (&x)[2] = (&o.x)[2]; }
 void operator-=(const V &o) { (&x)[0] -= (&o.x)[0]; (&x)[1] -= (&o.x)[1]; (&x)[2] -= (&o.x)[2]; }
 void operator+=(const V &o) { (&x)[0] += (&o.x)[0]; (&x)[1] += (&o.x)[1]; (&x)[2] += (&o.x)[2]; }
 void operator*=(float s) { (&x)[0] *= s; (&x)[1] *= s; (&x)[2] *= s; }
 float dot(V &o) { return (&x)[0] * (&o.x)[0] + (&x)[1] * (&o.x)[1] + (&x)[2] * (&o.x)[2]; }
 void normalize() { float inv = 1.0f / sqrtf(dot(*this)); *this *= inv; }
};
struct Mat { float m[16]; };
struct Self { char pad[72]; int matCount; char pad2[8]; Mat *mats; };
extern "C" {
void *FUN_00165cd0(void);
void *FUN_0014b940(void *);
void FUN_00192fc0(V *, V *, Mat *);
void FUN_00192f50(V *, V *, Mat *);
void FUN_00191f30(int *, Mat *, Mat *);
void FUN_001903d0(Mat *);
void *igObject_GetAllocator(void *);
void *Memory_GetAllocatorBySelector(int);
void Memory_FreeBuffer(void *);
extern int DAT_00587060[4];
extern unsigned char GPR_00554c14;
}
static inline Obj *getAlloc(void *o) {
    Obj *a = (Obj *)igObject_GetAllocator(o);
    if (GPR_00554c14 != 0) return a;
    return (Obj *)Memory_GetAllocatorBySelector(DAT_00587060[0]);
}
extern "C" void *FUN_00165e50(Self *self, Obj *src) {
    /* matching construct: random sweep — the order of the local declarations */
    int k; int nb; Obj *dst; Mat *buf; V *q; int m; int i; int n; int j; Fl flags; int scratch; V acc, t, nacc, nt; Obj *al;
    if (src != 0) {
    dst = (Obj *)FUN_0014b940(FUN_00165cd0());
    flags = *src->v100();
    flags.b &= ~0xF0;
    flags.b &= ~0xF00;
    n = src->count;
    dst->v96((int *)&flags, n, src->count2, self);
    if (flags.b & 4) {
        for (i = 0; i < n; i++) {
            dst->v164(i, src->v172(i));
        }
    }
    for (j = 0; j < (int)(((unsigned)(flags.b & 0xF0000) >> 16) & 0xFF); j++) {
        for (i = 0; i < n; i++) {
            dst->v200(j, i, src->v208(j, i));
        }
    }
    nb = ((unsigned)(src->v100()->b & 0xF0) >> 4) & 0xFF;
    for (i = 0; i < n; i++) {
        V *p = src->v124(i);
        acc = *p;
        for (j = 0; j < nb; j++) {
            float w = src->v184(j, i);
            if (!(w <= 0.0f)) {
                FUN_00192fc0(&t, p, self->mats + (src->v196(j, i)));
                t -= *p;
                t *= w;
                acc += t;
            }
        }
        dst->v116(i, &acc);
    }
    if (flags.b & 2) {
        buf = getAlloc(self)->v216(self->matCount << 6);
        for (i = 0; i < self->matCount; i++) {
            Mat *b = buf + i;
            FUN_00191f30(&scratch, b, self->mats + i);
            FUN_001903d0(b);
        }
        for (k = 0; k < n; k++) {
            q = src->v136(k);
            nacc = *q;
            for (m = 0; m < nb; m++) {
                float w = src->v184(m, k);
                if (!(w <= 0.0f)) {
                    FUN_00192f50(&nt, q, buf + (src->v196(m, k)));
                    nt -= *q;
                    nt *= w;
                    nacc += nt;
                }
            }
            nacc.normalize();
            dst->v128(k, &nacc);
        }
        Memory_FreeBuffer(buf);
    }
    return dst;
    }
    return 0;
}
