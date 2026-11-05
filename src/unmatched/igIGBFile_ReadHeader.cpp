extern "C" {
void *igShortMetaField_GetDefaultDescriptor();
int igIGBFile_GetSectionBuffer(int *, void *, int);
void *igIntMetaField_GetDefaultDescriptor();
int igObject_Destroy(void *);
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
extern int D_004fb418[4];
}
struct H { int f0, f4, f8, f12, f16, f20, f24, f28, f32, f36, f40, f44; };
class Dev { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int v27(void *, int, int); };
class Obj { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual int v52(H *, int); int rc; };
struct S {
    char p0[96]; int f96; int f100; Dev *f104; char p1[4];
    int f112; char p2[8]; int f124; int f128; int f132; int f136; int f140; int f144; int f148; int f152; int f156;
    char p3[8]; char f168; char p4[35]; Obj *f204; Obj *f208;
    char f212, f213, f214; unsigned char f215; int f216; char p5[44]; H *f264; char p6[24]; char f292;
};
extern "C" void igIGBFile_ReadHeader(int *arg0, S *arg1) {
    int sp5C;
    int *pp;
    int a;
    H *h;
    Obj *o;
    Obj *t;

    igIGBFile_GetSectionBuffer(&sp5C, arg1, 0xC0);
    pp = (int *)((int)&sp5C + 0);
    a = D_004fb418[0];
    if (*pp == DAT_004fb418[0]) {
        *arg0 = a;
        return;
    }
    h = arg1->f264;
    arg1->f104->v27(h, 4, 0xC);
    o = (Obj *)igIntMetaField_GetDefaultDescriptor();
    if (o != 0) {
        o->rc = o->rc + 1;
    }
    t = arg1->f204;
    if (t != 0) {
        t->rc = t->rc - 1;
        if (((unsigned long long) ((long long) t->rc << 0x29) >> 0x29) == 0) {
            igObject_Destroy(t);
        }
    }
    arg1->f204 = o;
    o = (Obj *)igShortMetaField_GetDefaultDescriptor();
    if (o != 0) {
        o->rc = o->rc + 1;
    }
    t = arg1->f208;
    if (t != 0) {
        t->rc = t->rc - 1;
        if (((unsigned long long) ((long long) t->rc << 0x29) >> 0x29) == 0) {
            igObject_Destroy(t);
        }
    }
    arg1->f208 = o;
    if (h->f40 != arg1->f96) {
        arg1->f204->v52(h, 0xC);
        if (h->f40 == arg1->f96) {
            arg1->f168 = 1;
        }
    } else {
        arg1->f168 = 0;
    }
    if (h->f40 != arg1->f96) {
        *arg0 = DAT_004fb418[0];
    } else {
        arg1->f100 = (int)*(unsigned short *)&h->f44;
        if ((int)arg1->f100 > 7) {
            *arg0 = DAT_004fb418[0];
        } else {
            arg1->f212 = (h->f44 & 0x80000000) != 0;
            arg1->f213 = (h->f44 & 0x40000000) > 0;
            arg1->f214 = (h->f44 & 0x20000000) > 0;
            arg1->f215 = h->f44 == 1;
            arg1->f292 = (h->f44 & 0x10000000) > 0;
            if (arg1->f215 != 0) {
                arg1->f216 = 1;
            } else {
                arg1->f216 = 0;
            }
            arg1->f124 = h->f0;
            arg1->f112 = h->f4;
            arg1->f132 = h->f8;
            arg1->f128 = h->f12;
            arg1->f148 = h->f16;
            arg1->f144 = h->f20;
            arg1->f156 = h->f24;
            arg1->f152 = h->f28;
            arg1->f140 = h->f32;
            arg1->f136 = h->f36;
            *arg0 = DAT_004fb410[0];
        }
    }
}
