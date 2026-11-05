typedef struct O { char pad[355]; unsigned char fmt0; unsigned int col0; char pad2[3]; unsigned char fmt1; unsigned int col1; } O;
extern int DAT_00491478[4];
extern int DAT_00569330[4];
extern O * DAT_0056ad80[4];
extern long long DAT_0056ae48[4];
extern int DAT_0056b058[4];
void FUN_001edcc0(int arg0, int arg1, int arg2, int arg3) {
    int var_a0;
    long long var_v1;
    O *temp_v1;
    int fmt;

    if (DAT_00569330[0] == 0) {
        fmt = DAT_0056ad80[0]->fmt0 & 0x3F;
        switch (fmt) {
        case 0:
        case 1:
            var_a0 = ((!arg3) ? 0xFF000000 : 0) | (((!arg2) ? 0xFF0000 : 0) | (((!arg0) ? 0xFF : 0) | ((!arg1) ? 0xFF00 : 0)));
            DAT_0056ad80[0]->col0 = var_a0;
            break;
        case 10:
        case 2:
            var_a0 = ((!arg3) ? 0x80000000 : 0) | (((!arg2) ? 0xF80000 : 0) | (((!arg0) ? 0xF8 : 0) | ((!arg1) ? 0xF800 : 0)));
            DAT_0056ad80[0]->col0 = var_a0;
            break;
        }
        DAT_00491478[0] |= 0x40;
        DAT_0056ae48[0] |= (long long)0x1000 << 0x20;
        if (DAT_0056b058[0] != 0) {
            DAT_0056ad80[0]->col1 = DAT_0056ad80[0]->col0;
            DAT_00491478[0] |= 0x40;
            var_v1 = DAT_0056ae48[0] | ((long long)0x2000 << 0x20);
            DAT_0056ae48[0] = var_v1;
        }
    } else {
        temp_v1 = DAT_0056ad80[0];
        fmt = temp_v1->fmt1 & 0x3F;
        switch (fmt) {
        case 0:
        case 1:
            var_a0 = ((!arg3) ? 0xFF000000 : 0) | (((!arg2) ? 0xFF0000 : 0) | (((!arg0) ? 0xFF : 0) | ((!arg1) ? 0xFF00 : 0)));
            temp_v1->col1 = var_a0;
            break;
        case 2:
        case 10:
            var_a0 = ((!arg3) ? 0x80000000 : 0) | (((!arg2) ? 0xF80000 : 0) | (((!arg0) ? 0x1F : 0) | ((!arg1) ? 0xF800 : 0)));
            temp_v1->col1 = var_a0;
            break;
        }
        DAT_00491478[0] |= 0x40;
        var_v1 = DAT_0056ae48[0] | ((long long)0x2000 << 0x20);
        DAT_0056ae48[0] = var_v1;
    }
}
