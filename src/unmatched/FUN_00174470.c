int FUN_00174640();
extern int DAT_00560968[4];
struct S174470 { char pad[1100]; int f; };
void FUN_00174470(struct S174470 *arg0, int arg1) {
    if (arg0->f == arg1) {
        DAT_00560968[0] += 1;
    }
    arg0->f = arg1;
    FUN_00174640(arg0, 0);
}
