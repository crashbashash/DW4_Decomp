extern char DAT_0056e430[];
int FUN_0026fba8();
int FUN_002712c8();
int sprintf();
int strcpy();
extern int DAT_004efb38[4];
void FUN_00271318(int arg0, int arg1) {
    int var_s0;

    var_s0 = arg0;
    if (var_s0 == 0) {
        var_s0 = FUN_0026fba8();
    }
    if (FUN_002712c8(var_s0) == 1) {
        strcpy(DAT_0056e430, arg1);
        sprintf(arg1, &DAT_004efb38[0], var_s0, DAT_0056e430);
    }
}
