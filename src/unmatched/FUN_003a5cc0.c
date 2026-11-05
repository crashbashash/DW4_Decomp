typedef struct V3 { float x, y, z; } V3;
typedef struct A { char p[8]; int n; char q[4]; V3 *pts; } A;
typedef struct B { char p[16]; int *idx; } B;
void FUN_003a5cc0(void *arg0, A *a, B *b, V3 *q, V3 *outv, float *outd, int *outi) {
    int bi; int n; int i; float dx, dy, dz, d, best, px, py, pz, bx, by, bz;
    bi = 0; n = a->n;
    for (i = 0; i < n; i++) {
        V3 *p = &a->pts[i];
        px = p->x; py = p->y; pz = p->z;
        dy = q->y - py; dx = q->x - px; dz = q->z - pz;
        d = dx*dx + dy*dy + dz*dz;
        if (i == 0 || !(best <= d)) {
            best = d; bx = px; by = py; bz = pz;
            if (b) bi = b->idx[i];
        }
    }
    outv->x = bx; outv->y = by; outv->z = bz;
    *outd = best;
    *outi = bi;
}
