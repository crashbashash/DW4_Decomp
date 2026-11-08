extern char DAT_004a92c4[];
int sceCdSeek();
int sceCdGetError();
int FUN_002725a0();
int FUN_0027eca8();

int FUN_002726f8(int arg0) {
    int temp_s0;
    int var_s1;
    int var_v0;

    var_v0 = FUN_0027eca8(DAT_004a92c4);
    var_s1 = 0;
    if (var_v0 != 0) {
        FUN_002725a0(0x9600);
        temp_s0 = sceCdSeek(arg0);
        FUN_002725a0(0x9601);
        if (temp_s0 == 0) {
            var_s1 = sceCdGetError();
        }
        *(int *)DAT_004a92c4 = 0;
        var_v0 = var_s1;
    }
    return var_v0;
}
