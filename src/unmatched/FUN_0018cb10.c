typedef struct { unsigned int mant : 23; unsigned int exp : 8; unsigned int sign : 1; } FB;
static inline float fabs_(float x) { ((FB *)&x)->sign = 0; return x; }
typedef struct { char pad[8]; float x, y, z, d; } Plane;
typedef struct { float x, y, z; } V3;
int FUN_0018d060(Plane *a, V3 *b);
int FUN_0018cb10(Plane *a, Plane *b) {
    V3 p;
    float d;
    int r;
    float dot = a->x * b->x + a->y * b->y + a->z * b->z;
    if (fabs_(dot - 1.0f) < 5e-7f) { return (b->d > a->d) ? 2 : 0; }
 if (fabs_(1.0f + dot) < 5e-7f) { d = b->d; p.x = d * b->x; p.y = d * b->y; p.z = d * b->z; return FUN_0018d060(a, &p) ? 2 : 0;} else return 1;
}
