typedef struct { char pad[8]; float x, y, z; float dx, dy, dz; float s; } S;
int FUN_001900d0();
void FUN_0018dfc0(void *parg0, S *arg1) {
    int arg0 = (int)parg0;
    float v[3];
    float s;
    FUN_001900d0(arg0, (char *)arg1 + 8);
    s = arg1->s;
    v[0] = arg1->x + s * arg1->dx;
    v[1] = arg1->y + s * arg1->dy;
    v[2] = arg1->z + s * arg1->dz;
    FUN_001900d0(arg0, v);
}
