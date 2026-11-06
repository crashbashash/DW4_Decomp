extern float GPR_005548d8;
extern float GPR_005548dc;
typedef struct B { char pad[8]; unsigned int *data; } B;
typedef struct A { char pad[8]; B *b; } A;
void Gap__Gfx__igPsx2VertexArray1_1__vfunc_44(A *arg0, int arg1, float *arg2) {
    unsigned int c = arg0->b->data[arg1];
    unsigned int t;
    float f, s;
    t = c >> 24;
    s = (t > 128) ? GPR_005548d8 : 0.0078125f;
    f = (float)(t & 0xFF);
    arg2[3] = f * s;
    t = (c >> 16) & 0xFF;
    f = (float)t;
    arg2[2] = GPR_005548dc * f;
    t = (c >> 8) & 0xFF;
    f = (float)t;
    arg2[1] = GPR_005548dc * f;
    t = c & 0xFF;
    f = (float)t;
    arg2[0] = GPR_005548dc * f;
}
