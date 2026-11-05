int Gap__Core__igObject__vfunc_07();
int igObject_Destroy();

typedef struct T { int w0; int refs; } T;
typedef struct A { char pad[28]; T *f1c; } A;
extern T *DAT_00562a38[4];
void Gap__Sg__igTraversal__vfunc_09(A *arg0, int arg1) {
    T *temp_a0;
    T *temp_s0;

    Gap__Core__igObject__vfunc_07();
    if (arg1 == 0) {
        temp_s0 = DAT_00562a38[0];
        if (temp_s0 != 0) {
            temp_s0->refs = temp_s0->refs + 1;
        }
        temp_a0 = arg0->f1c;
        if (temp_a0 != 0) {
            temp_a0->refs = temp_a0->refs - 1;
            if (((unsigned long long) ((long long) temp_a0->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        arg0->f1c = temp_s0;
    }
}
