int FUN_001906d0();
int List_Resize();
int Matrix44_Copy();
typedef struct Mat { int w[16]; } Mat;
typedef struct Lst { int w0; int w4; int count; int cap; Mat *data; } Lst;
int FUN_001e68e0(Lst *arg0, int arg1) {
    int var_s0;
    int temp_v1;
    Mat *d;

    var_s0 = arg0->count;
    if (var_s0 == 0) {
        if (var_s0 < arg0->cap) {
            arg0->count = *(const int *)&arg0->count + 1;
        } else {
            List_Resize(arg0, var_s0 + 1, 0x40);
        }
        Matrix44_Copy(arg0->data + var_s0, arg1);
    } else {
        temp_v1 = *(const int *)&arg0->count;
        if (temp_v1 == 0) {
            var_s0 = 0;
        } else {
            if (var_s0 < arg0->cap) {
                arg0->count = temp_v1 + 1;
            } else {
                List_Resize(arg0, var_s0 + 1, 0x40);
            }
            d = arg0->data;
            Matrix44_Copy(d + var_s0, d + (var_s0 - 1));
        }
        FUN_001906d0(arg0->data + (arg0->count - 1), arg1);
    }
    return var_s0;
}
