struct V3 { float x, y, z; };
struct Arr { int pad0; int pad1; int n; int pad3; struct V3 *v; };
struct Mid { int p0, p1, p2, p3; struct Arr *a; int p5; };
struct Top { int p0, p1, p2, p3; struct Arr *arr; int p5; };
extern "C" {
extern struct Top *DAT_0058a570[4];
extern float DAT_004e1058[4], DAT_004e105c[4], DAT_004e1060[4];
extern int DAT_0050ffd0[4], DAT_0050ffd8[4];
int FUN_003a5b40(struct Top *, struct Arr *, int, int *, int *);
int FUN_003a5f60(float *out);
}
int FUN_003a5f60(float *out) {
    int n, i;
    if (DAT_0058a570[0]->arr->n == 0) {
        FUN_003a5b40(DAT_0058a570[0], DAT_0058a570[0]->arr, DAT_0058a570[0]->p5, DAT_0050ffd0, DAT_0050ffd8);
        if (DAT_0058a570[0]->arr->n == 0) return 0;
    }
    out[0] = DAT_004e1058[0];
    out[1] = DAT_004e105c[0];
    out[2] = DAT_004e1060[0];
    n = DAT_0058a570[0]->arr->n;
    for (i = 0; i < n; i++) {
        struct V3 *p = &DAT_0058a570[0]->arr->v[i];
        out[0] += p->x; out[1] += p->y; out[2] += p->z;
    }
    switch (n) {
    case 0: case 1: break;
    case 2: out[0] /= 2.0f; out[1] /= 2.0f; out[2] /= 2.0f; break;
    case 3: out[0] /= 3.0f; out[1] /= 3.0f; out[2] /= 3.0f; break;
    case 4: out[0] /= 4.0f; out[1] /= 4.0f; out[2] /= 4.0f; break;
    }
    return 1;
}
