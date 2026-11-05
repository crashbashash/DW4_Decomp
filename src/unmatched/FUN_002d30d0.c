int igArray_Append(int, int (*)(int));
struct L { char pad[8]; int *data; int count; };
struct S24 { char pad[24]; struct L *f24; char pad2[16]; int f44; };

void FUN_002d30d0(struct S24 *arg0, int (*arg1)(int)) {
    int i;

    for (i = 0; i < arg0->f24->count; i++) {
        arg1(arg0->f24->data[i]);
    }
    igArray_Append(arg0->f44, arg1);
}
