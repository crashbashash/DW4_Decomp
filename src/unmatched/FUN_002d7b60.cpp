struct R { int a; };
class VO { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual R v96(); virtual int v100(); };
struct Lst { int w0; int w4; int count; int w12; int *data; };
struct Obj { int w[6]; Lst *list; int w28; int f32; int w36[8]; VO *vo; };
extern "C" {
void *FUN_002d8370(Obj *, int);
int FUN_002d9120(Obj *);
int FUN_00309750(int, int);
int Gap__Core__igObject__vfunc_10(Obj *);
void FUN_002d7b60(Obj *arg0);
}
void FUN_002d7b60(Obj *arg0) {
    R sp4C;
    int temp_s2;
    int i;
    int *temp_v0;
    Lst *l;

    if (arg0->f32 != 0) {
        for (i = 0; i < arg0->list->count; i++) {
            FUN_00309750(arg0->f32, ((int *)arg0->list->data[i])[5]);
        }
    }
    temp_s2 = FUN_002d9120(arg0);
    for (i = 0; i < temp_s2; i++) {
        temp_v0 = (int *)FUN_002d8370(arg0, i);
        if (temp_v0[3] == (int)arg0) {
            temp_v0[3] = 0;
        }
    }
    Gap__Core__igObject__vfunc_10(arg0);
    if (arg0->vo != 0 && arg0->vo->v100() != 0) {
        sp4C = arg0->vo->v96();
    }
}
