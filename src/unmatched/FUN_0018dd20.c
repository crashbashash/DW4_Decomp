typedef struct S { int pad[2]; float x, y, z, r, ax, ay, az; } S;
float sqrtf(float);
void FUN_0018aaa0(S *a, float *b);
void FUN_00190120(S *a, float *b, int n);
void FUN_0018dd20(S *p, S *q) {
    float box[24];
    float dx, dy, dz;
    if (q->x <= q->r) {
        if (p->r < 0.0f) {
            p->x = 0.5f * q->x + 0.5f * q->r;
            p->y = 0.5f * q->y + 0.5f * q->ax;
            p->z = 0.5f * q->z + 0.5f * q->ay;
            dy = p->y - q->ax;
            dx = p->x - q->r;
            dz = p->z - q->ay;
            p->r = sqrtf(dx * dx + dy * dy + dz * dz);
        } else {
            FUN_0018aaa0(q, box);
            FUN_00190120(p, box, 8);
        }
    }
}
