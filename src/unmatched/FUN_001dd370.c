extern float DAT_004e1058[4];
extern float DAT_004e105c[4];
extern float DAT_004e1060[4];
int FUN_001dd370(void *arg0) {
    int var_v0;

    var_v0 = 1;
    if (*(float *)((char *)(arg0) + 44) == DAT_004e1058[0]) {
        var_v0 = 0;
    }
    if (var_v0 == 0) {
        var_v0 = 1;
        if (*(float *)((char *)(arg0) + 48) == DAT_004e105c[0]) {
            var_v0 = 0;
        }
    }
    if (var_v0 == 0) {
        var_v0 = 1;
        if (*(float *)((char *)(arg0) + 52) == DAT_004e1060[0]) {
            var_v0 = 0;
        }
    }
    return var_v0 ^ 1;
}
