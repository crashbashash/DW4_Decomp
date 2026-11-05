typedef struct B { char p[12]; float x, y, z; } B;
typedef struct A { char p[8]; B *b; char q[12]; float dx, dy; } A;
void FUN_00453b90(float *out, A *a) {
    B *b = a->b;
    float z0 = 0.0f, two = 2.0f; float dx = a->dx, dy = a->dy; float x = b->x, y = b->y, z = b->z; x += two * dx; y += two * dy; z += z0; out[0] = x; out[1] = y; out[2] = z;
}
