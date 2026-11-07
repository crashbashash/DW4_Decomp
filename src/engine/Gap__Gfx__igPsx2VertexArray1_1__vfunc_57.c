typedef struct VertexDataView { char pad[76]; float *data; } VertexDataView;
typedef struct VertexArrayView { char pad[8]; VertexDataView *b; } VertexArrayView;
float FUN_00123658(float, float);
int FUN_001002f0(int, int);
int FUN_00230298(float);
void Gap__Gfx__igPsx2VertexArray1_1__vfunc_57(VertexArrayView *arg0, int arg1, float x) {
    float t = FUN_00123658(x, 6.2831855f);
    if (FUN_001002f0(FUN_00230298(t), 0) != 0) {
        t += 6.2831855f;
    }
    if (!(x < 0.0f) && x <= 1.5707964f) {
        arg0->b->data[arg1] = t;
    } else if (!(x <= 1.5707964f) && x <= 4.712389f) {
        arg0->b->data[arg1] = 4.712389f - (t - 1.5707964f);
    } else {
        arg0->b->data[arg1] = t - 6.2831855f;
    }
}
