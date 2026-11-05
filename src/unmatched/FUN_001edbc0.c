int FUN_001ebc00();
extern short DAT_00568e22[8];
extern short DAT_00568e08[8];
extern short DAT_00568e24[8];
extern short DAT_00568e0a[8];
extern short DAT_00568e0e[8];
extern short DAT_00568e0c[8];
typedef struct Obj { char pad[355]; unsigned char b355; char pad2[15]; unsigned char b371; } Obj;
extern Obj *DAT_0056ad80[4];
void FUN_001edbc0(int *arg0, int *arg1, int *arg2, int *arg3) {
    short var_v1;
    short var_v1_2;
    int temp_a0;

    temp_a0 = (FUN_001ebc00() & 2) != 0;
    if (temp_a0 != 0) {
        var_v1 = DAT_00568e22[0];
    } else {
        var_v1 = DAT_00568e08[0];
    }
    *arg0 = var_v1;
    if (temp_a0 != 0) {
        var_v1_2 = DAT_00568e24[0];
    } else {
        var_v1_2 = DAT_00568e0a[0];
    }
    *arg1 = var_v1_2;
    if ((DAT_00568e0e[0] == 0) && (DAT_00568e0c[0] > 0)) {
        *arg1 *= 2;
    }
    if (arg2 != 0) {
        *arg2 = DAT_0056ad80[0]->b355 & 0x3F;
    }
    if (arg3 != 0) {
        *arg3 = DAT_0056ad80[0]->b371 & 0xF;
    }
}
