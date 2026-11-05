int FUN_00302780();
struct L { char pad[32]; int *data; char pad2[32]; int count; };
void FUN_00302bc0(struct L *arg0, int arg1) {
    int i;

    for (i = 0; i < arg0->count; i++) {
        FUN_00302780(arg0, arg1, i, arg0->data[i]);
    }
}
