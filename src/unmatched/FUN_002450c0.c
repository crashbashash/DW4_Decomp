int memset();
int FUN_00245080();
int Memory_AllocateDefaultBuffer();
int Memory_FreeBufferAlias_002ed4b0();
extern unsigned int DAT_004986b0[4];
extern unsigned int DAT_004986b8[4];
extern unsigned int DAT_0056deb8[4];
extern int DAT_0056dec0[4];
extern int DAT_0056dec8[4];
void FUN_002450c0(void) {
    int temp_s0;
    unsigned int temp_a0;
    unsigned int var_s3;
    unsigned int temp_s2;
    int temp_v0;
    unsigned int var_s0;
    void *temp_s4;
    void *var_a0;

    if (DAT_0056dec0[0] == 0) {
        DAT_0056dec0[0] = Memory_AllocateDefaultBuffer(DAT_004986b8[0] * 4);
        memset(DAT_0056dec0[0], 0, DAT_004986b8[0] * 4);
        return;
    }
    if (DAT_0056dec8[0] == 0) {
        if (DAT_0056deb8[0] == 0) {
            Memory_FreeBufferAlias_002ed4b0(DAT_0056dec0[0], DAT_0056deb8[0]);
            DAT_0056dec0[0] = 0;
            DAT_004986b8[0] = 0x100;
            return;
        }
        temp_a0 = DAT_004986b0[0];
        var_s3 = temp_a0;
        if (DAT_004986b8[0] < DAT_0056deb8[0]) {
            var_s3 = temp_a0 + 1;
        } else {
            if (DAT_0056deb8[0] < (DAT_004986b8[0] >> 1)) {
                if (temp_a0 > 8U) {
                    var_s3 = temp_a0 - 1;
                }
            }
        }
        if (var_s3 != temp_a0) {
            temp_s2 = 1 << var_s3;
            temp_s0 = temp_s2 * 4;
            temp_v0 = Memory_AllocateDefaultBuffer(temp_s0, DAT_0056deb8[0]);
            memset(temp_v0, 0, temp_s0);
            for (var_s0 = 0; var_s0 < DAT_004986b8[0]; var_s0++) {
                var_a0 = (void *)(((int *)DAT_0056dec0[0])[var_s0]);
                while (var_a0 != 0) {
                    temp_s4 = (void *)(*(int *)((char *)(var_a0) + 4));
                    FUN_00245080(var_a0, temp_v0, temp_s2, var_s3);
                    var_a0 = (void *)(temp_s4);
                }
            }
            DAT_004986b8[0] = temp_s2;
            DAT_004986b0[0] = var_s3;
            Memory_FreeBufferAlias_002ed4b0(DAT_0056dec0[0]);
            DAT_0056dec0[0] = temp_v0;
        }
    }
}
