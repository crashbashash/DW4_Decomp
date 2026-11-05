struct M { int pad[2]; int count; };
struct O { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39(); virtual long long v40(int);
 int p0[3]; M *m; int p1[8]; int cur; };
extern "C" void FUN_001bfc70(O *o, long long t, int *a2, int *a3, float *a4, float *a5) {
    int i = o->cur;
    if (o->v40(i) < t) {
        do { i++; } while (o->v40(i) < t && i < o->m->count);
    } else if (t < o->v40(i - 1)) {
        do { i--; } while (t < o->v40(i - 1) && i > 0);
    }
    int c = o->m->count;
    if (i >= c) i = c - 1; else if (i <= 0) i = 1;
    o->cur = i;
    *a3 = i;
    *a2 = i - 1;
    if (*a2 < 0) *a2 = 0;
    *a4 = (float)(unsigned int)(int)((t - o->v40(*a2)) >> 18);
    long long s = o->v40(*a2);
    *a5 = (float)(unsigned int)(int)((o->v40(*a3) - s) >> 18);
}
