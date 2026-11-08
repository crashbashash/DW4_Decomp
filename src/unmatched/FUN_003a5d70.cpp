extern "C" {
float atan2f(float, float);
float FUN_003a6850(void *);
}
typedef struct V3 { float x, y, z; } V3;
typedef struct A { char p[8]; int n; char q[4]; V3 *pts; } A;
typedef struct B { char p[16]; int *idx; } B;
extern "C" {
void FUN_003a5d70(void *arg0, A *a, B *b, V3 *q, V3 *outv, float *outd, int *outi);
}
void FUN_003a5d70(void *arg0, A *a, B *b, V3 *q, V3 *outv, float *outd, int *outi) {
    int bi; int n; int i;
    float ref, best, px, py, pz, bx, by, bz, ang, dx, dy, dz;
    ref = FUN_003a6850(arg0);
    n = a->n;
    for (i = 0; i < n; i++) {
        V3 *p = &a->pts[i];
        px = p->x; py = p->y; pz = p->z;
        ang = atan2f(px - q->x, pz - q->z) - ref;
        if (ang < 0.0f) ang = -ang;
        while (ang > 6.2831855f) ang -= 6.2831855f;
        if (i == 0 || !(best <= ang)) {
            best = ang; bx = px; by = py; bz = pz;
            bi = b->idx[i];
        }
    }
    outv->x = bx; outv->y = by; outv->z = bz;
    dy = q->y - by; dx = q->x - bx; dz = q->z - bz;
    *outd = dx*dx + dy*dy + dz*dz;
    *outi = bi;
}
