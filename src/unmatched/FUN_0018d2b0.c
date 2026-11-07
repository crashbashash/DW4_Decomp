extern float sqrtf(float);
typedef struct { float x, y, z; } V3;
typedef struct { int pad0, pad1; V3 p; V3 d; float len; } S;
void FUN_0018d2b0(S *s, V3 *a, V3 *b) {
    float len, inv;
    s->p.x = a->x;
    s->p.y = a->y;
    s->p.z = a->z;
    s->d.x = b->x - a->x;
    s->d.y = b->y - a->y;
    s->d.z = b->z - a->z;
    len = sqrtf(s->d.x * s->d.x + s->d.y * s->d.y + s->d.z * s->d.z);
    s->len = len;
    if (4.99999999e-07f < len) {
        inv = 1.0f / len;
        s->d.x = s->d.x * inv;
        s->d.y = s->d.y * inv;
        s->d.z = s->d.z * inv;
    }
}
