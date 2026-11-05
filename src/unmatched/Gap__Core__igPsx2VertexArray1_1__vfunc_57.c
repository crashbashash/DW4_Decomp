typedef struct B { char pad[76]; float *data; } B;
typedef struct A { char pad[8]; B *b; } A;
float FUN_00123658(float, float);
int FUN_001002f0(int, int);
int FUN_00230298(float);
extern float GPR_005548cc;
extern float GPR_005548d0;
extern float GPR_005548d4;
void Gap__Core__igPsx2VertexArray1_1__vfunc_57(A *arg0, int arg1, float x) {
    float t = FUN_00123658(x, GPR_005548d4);
    if (FUN_001002f0(FUN_00230298(t), 0) != 0) {
        t += GPR_005548d4;
    }
    if (!(x < 0.0f) && x <= GPR_005548cc) {
        arg0->b->data[arg1] = t;
    } else if (!(x <= GPR_005548cc) && x <= GPR_005548d0) {
        arg0->b->data[arg1] = GPR_005548d0 - (t - GPR_005548cc);
    } else {
        arg0->b->data[arg1] = t - GPR_005548d4;
    }
}
