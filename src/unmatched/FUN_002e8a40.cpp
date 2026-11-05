extern "C" void igObject_Destroy(void *);
struct R { int vt; int rc; };
struct Al { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59(); virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63(); virtual void v64(int); };
struct T {
  char p0[40]; R *f40; char p1[16]; R *f60; char p2[28]; R *f92; char p3[24]; int f120; char p4[48]; int f172; int f176; int f180; int f184; R *f188; R *f192; char p5[68]; int f264; char p6[12]; Al *f280; char p7[12]; int f296; int f300; R *f304;
};
#define REL(p) do { R *t_ = (p); if (t_ != 0) { t_->rc = t_->rc - 1; if (((unsigned long long)((long long)t_->rc << 0x29) >> 0x29) == 0) { igObject_Destroy(t_); } } } while (0)
extern "C" void FUN_002e8a40(T *a) {
    REL(a->f188);
    REL(a->f188);
    a->f188 = 0;
    REL(a->f192);
    a->f192 = 0;
    REL(a->f60);
    a->f60 = 0;
    a->f172 = 0;
    a->f176 = 0;
    a->f184 = 0;
    a->f180 = 0;
    REL(a->f92);
    a->f92 = 0;
    a->f120 = 0;
    REL(a->f40);
    a->f40 = 0;
    a->f280->v64(a->f264);
    a->f264 = 0;
    a->f296 = 0;
    int t = a->f300;
    if (t != 0) {
        a->f280->v64(t);
        a->f300 = 0;
    }
    REL(a->f304);
    a->f304 = 0;
}
