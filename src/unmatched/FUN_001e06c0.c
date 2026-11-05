int List_Resize();
int FUN_002fe290();
extern int DAT_00561838[4];
struct L { char pad[8]; int n; int cap; int *arr; };
struct X { char pad[8]; int f8; };
void FUN_001e06c0(struct L *arg0, struct X *arg1, int arg2) {
    int a1;
    int v1;
    int s2;

    if (FUN_002fe290(arg1, DAT_00561838[0]) != 0) {
        s2 = arg1->f8;
        if (s2 < 0) {
            s2 = arg0->n;
            arg1->f8 = s2;
        }
        a1 = s2 + 1;
        if (s2 >= arg0->n && a1 >= 0) {
            if (a1 <= arg0->cap) {
                arg0->n = a1;
            } else {
                List_Resize(arg0, a1, 4);
            }
        }
        v1 = arg0->n;
        if (v1 != 0 && s2 >= 0 && s2 < v1) {
            arg0->arr[s2] = arg2;
        }
    }
}
