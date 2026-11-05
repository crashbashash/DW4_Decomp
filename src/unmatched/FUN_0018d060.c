typedef struct P { char pad[8]; float a; float b; float c; float d; } P;
int FUN_0018d060(P *p, float *v) {
    int r;
    float d;
    d = p->a * v[0] + p->b * v[1] + p->c * v[2] - p->d;
    r = 0;
    if (d <= 0.0f) r = 2;
    return r;
}
