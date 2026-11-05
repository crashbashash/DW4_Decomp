struct S { long long a, b, c; };
int CreateSema();
int igObject_AllocateStorage();
extern struct S DAT_004c2630[1];
void FUN_0032d5a0(int *arg0) {
    struct S s;
    arg0[2] = igObject_AllocateStorage(arg0, 0x28);
    s = DAT_004c2630[0];
    arg0[4] = CreateSema(&s);
}
