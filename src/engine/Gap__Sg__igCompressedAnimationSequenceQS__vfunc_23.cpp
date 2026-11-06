struct M { int pad[2]; int count; };
struct O { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32(); virtual int v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44(int,int*); virtual void v45(int*,int,int,float); virtual void v46(int*,int,int,float);
 int p0[3]; M *m; int p1[8]; int idx; unsigned char flags; };
extern "C" {
void FUN_001bf7d0(O*, unsigned char*, unsigned char*, int*, int*, float*, float*, int);
void igMatrix44f_SetIdentity(int);
void FUN_001bf560(O*, int, int*);
void FUN_00192810(int*, int);
void Matrix44_SetTranslation(int, int*);
extern float GPR_00554930;
int Gap__Sg__igCompressedAnimationSequenceQS__vfunc_23(O *a0, int a1, int a2) {
    unsigned char s6f; unsigned char s6e; int s68; int s64; float s60; float s5c; int s50[3]; int s40[4];
    float f;
    FUN_001bf7d0(a0, &s6f, &s6e, &s68, &s64, &s60, &s5c, a2);
    igMatrix44f_SetIdentity(a1);
    if (s6f) {
        if (a0->flags & 2) { FUN_001bf560(a0, 0, s40); FUN_00192810(s40, a1); }
        if (a0->flags & 1) { a0->v44(0, s50); Matrix44_SetTranslation(a1, s50); }
    } else if (s6e) {
        if (a0->flags & 2) { FUN_001bf560(a0, a0->m->count - 1, s40); FUN_00192810(s40, a1); }
        if (a0->flags & 1) { a0->v44(a0->v33() - 1, s50); Matrix44_SetTranslation(a1, s50); }
    } else {
        if (s5c < GPR_00554930) f = 0.0f; else f = s60 / s5c;
        if (a0->flags & 2) { a0->v46(s40, s68, s64, f); FUN_00192810(s40, a1); }
        if (a0->flags & 1) { a0->v45(s50, s68, s64, f); Matrix44_SetTranslation(a1, s50); }
    }
    return 1;
}
}
