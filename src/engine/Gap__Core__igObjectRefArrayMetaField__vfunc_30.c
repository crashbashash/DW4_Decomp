int FUN_00302780();
struct L { char pad[32]; int *data; char pad2[32]; int count; };
void Gap__Core__igObjectRefArrayMetaField__vfunc_30(struct L *arg0, int arg1) {
    int i;

    for (i = 0; i < arg0->count; i++) {
        FUN_00302780(arg0, arg1, i, arg0->data[i]);
    }
}
