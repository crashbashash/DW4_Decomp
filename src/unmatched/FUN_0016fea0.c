typedef struct A { char p[24]; unsigned int f24; unsigned char f28; char p1[3]; int f32; int f36; int f40; int f44; unsigned char f48; } A;
typedef struct It { char p[448]; } It;
int FUN_001e81f0();
extern int DAT_00569330[4];
extern It DAT_00569340[4];
extern It *DAT_0056ad80[4];
void FUN_0016fea0(A *arg0, int arg1) {
    int var_a0;
    unsigned int temp_v1;

    if (arg1 > 1) {
        var_a0 = arg1 - 1;
    } else {
        var_a0 = 0;
    }
    DAT_00569330[0] = arg1;
    DAT_0056ad80[0] = &DAT_00569340[0] + var_a0;
    if (arg0->f28 != 0) {
        FUN_001e81f0(arg0->f32, arg0->f36, arg0->f40, arg0->f44, arg0->f48);
    } else {
        temp_v1 = arg0->f24;
        switch (temp_v1) {
        case 0:
            FUN_001e81f0(0, 2, 2, 2, 0x80U);
            break;
        case 2:
            FUN_001e81f0(0, 2, 2, 1, 0x80U);
            break;
        case 3:
            FUN_001e81f0(0, 1, 2, 2, 0x80U);
            break;
        case 4:
            FUN_001e81f0(1, 0, 2, 2, 0x80U);
            break;
        case 1:
            FUN_001e81f0(0, 2, 0, 2, 0x80U);
            break;
        case 5:
            FUN_001e81f0(0, 2, 0, 1, 0x80U);
            break;
        case 6:
            FUN_001e81f0(0, 1, 0, 2, 0x80U);
            break;
        case 7:
            FUN_001e81f0(1, 0, 0, 2, 0x80U);
            break;
        case 8:
            FUN_001e81f0(0, 2, 1, 2, 0x80U);
            break;
        case 9:
            FUN_001e81f0(0, 2, 1, 1, 0x80U);
            break;
        case 10:
            FUN_001e81f0(0, 1, 1, 2, 0x80U);
            break;
        case 11:
            FUN_001e81f0(1, 0, 1, 2, 0x80U);
            break;
        }
    }
    DAT_00569330[0] = 0;
    DAT_0056ad80[0] = &DAT_00569340[0];
}
