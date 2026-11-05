typedef struct V3 { float x, y, z; } V3;
typedef struct B { char pad[16]; char *data; } B;
typedef struct A { char pad[8]; B *b8; B *b12; B *b16; char pad2[24]; float f44; float f48; float f52; } A;
int FUN_00190cb0();
int FUN_00192810();
int FUN_00192f50();
void FUN_001dd250(A *arg0, int arg1, char *arg2) {
    V3 sp50;
    float f22, f21, f20;
    int idx;
    V3 *v;
    FUN_00192810(arg0->b12->data + arg1 * 16, arg2);
    idx = arg1 * 12;
    v = (V3 *)(arg0->b8->data + idx);
    f22 = v->x;
    f21 = v->y;
    f20 = v->z;
    if (arg0->f44 == 0.0f && arg0->f48 == 0.0f && arg0->f52 == 0.0f) {
    } else {
        FUN_00192f50(&sp50, &arg0->f44, arg2);
        f22 = f22 - sp50.x;
        f21 = f21 - sp50.y;
        f20 = f20 - sp50.z;
        f22 = f22 + arg0->f44;
        f21 = f21 + arg0->f48;
        f20 = f20 + arg0->f52;
    }
    *(float *)(arg2 + 48) = f22;
    *(float *)(arg2 + 52) = f21;
    *(float *)(arg2 + 56) = f20;
    FUN_00190cb0(arg2, arg0->b16->data + idx);
}
