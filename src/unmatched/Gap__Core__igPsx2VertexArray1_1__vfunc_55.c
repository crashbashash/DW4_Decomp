typedef struct A { char p[8]; struct B *b; } A;
typedef struct B { char p[60]; char *data; } B;
void Gap__Core__igPsx2VertexArray1_1__vfunc_55(A *arg0, int arg1, float *arg2) {
    float x = arg2[0];
    float y = arg2[1];
    float *dst;
    x = x * 0.5f;
    y = y * 0.5f;
    dst = (float *)(arg0->b->data + arg1 * 8);
    dst[0] = x;
    dst[1] = y;
}
