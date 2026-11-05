typedef struct B { int pad[2]; float v[3]; } B;
typedef struct G { char pad[16]; int nx, ny, nz; char pad2[28]; B *box; float sx, sy, sz; } G;
void FUN_0023b720(G *g, float *p, int *ox, int *oy, int *oz) {
    float x = p[0], y = p[1], z = p[2];
    B *b = g->box;
    volatile float *v = b->v;
    float *nv = b->v;
    float t;
    t = b->v[0]; if (x < t) x = t;
    t = v[1]; if (y < t) y = t;
    t = v[2]; if (z < t) z = t;
    {
    float a0 = nv[0], a1 = nv[1], a2 = nv[2];
    x = x - a0; y = y - a1; z = z - a2;
    x = x / g->sx; y = y / g->sy; z = z / g->sz;
    }
    *ox = (int)x;
    if (g->nx <= *ox) *ox = g->nx - 1;
    *oy = (int)y;
    if (g->ny <= *oy) *oy = g->ny - 1;
    *oz = (int)z;
    if (g->nz <= *oz) *oz = g->nz - 1;
}
