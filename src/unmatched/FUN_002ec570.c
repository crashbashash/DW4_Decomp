int FUN_00300e50();
int igObject_AllocateStorage();
struct O { char pad[48]; int f48; int f52; char pad2[4]; int f60; };
void FUN_002ec570(struct O *arg0, int arg1) {
    int temp_a1;
    int var_s0;
    int var_v0;
    if (arg0->f48 < arg1) {
        var_s0 = arg1 * 2;
        if (arg1 > 0x100000) {
            var_s0 = arg1 + 0x100000;
        }
        temp_a1 = arg0->f60;
        if (temp_a1 != 0) {
            var_v0 = FUN_00300e50(arg0, temp_a1, var_s0);
        } else {
            var_v0 = igObject_AllocateStorage(arg0, var_s0);
        }
        arg0->f60 = var_v0;
        arg0->f48 = var_s0;
    }
    arg0->f52 = arg1;
}
