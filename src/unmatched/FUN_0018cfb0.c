int FUN_0018d060();
struct S { char p[8]; float a[3]; float b[3]; };
int FUN_0018cfb0(void *arg0, struct S *arg1) {
    float v[3];
    int s0, v0;
    v[0] = arg1->a[0] + arg1->b[0];
    v[1] = arg1->a[1] + arg1->b[1];
    v[2] = arg1->a[2] + arg1->b[2];
    s0 = FUN_0018d060(arg0, arg1->a) == 2;
    v0 = FUN_0018d060(arg0, v) == 2;
    if (s0 != 0 && v0 != 0) {
        return 2;
    }
    if (s0 != 0 || v0 != 0) {
        return 1;
    }
    return 0;
}
