#include "dw4/reflected.h"
extern "C" {
int FUN_002eb010(int);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
void *StringPool_Intern(int, int);
extern int DAT_00586f20[4];
void FUN_0041d2c0(igStringRefList *arg0, int arg1, int arg2) {
    int *temp_a1;
    int temp_v1;
    int var_v0;
    int temp_s4;
    int var_s3;
    void **temp_s2;
    void *temp_s1;
    int var_s0;
    void *temp_a0;

    temp_s4 = arg1 + arg2;
    var_s3 = arg1;
    if (arg1 < temp_s4) {
        var_s0 = arg1 * 4;
        do {
            temp_s2 = (void **)(arg0->_data + var_s0);
            if (DAT_00586f20[0] == 0) {
                var_v0 = FUN_002eb010(0x10);
                if (var_v0 != 0) {
                    var_v0 = StringPool_Construct(var_v0);
                }
                DAT_00586f20[0] = var_v0;
            }
            temp_s1 = (void *)(StringPool_Intern(DAT_00586f20[0], 0));
            temp_a0 = (void *)(*temp_s2);
            if (temp_a0 != 0) {
                temp_a1 = (int *)((char *)temp_a0 - 8);
                temp_v1 = *(int *)((char *)(temp_a0) - 4) - 1;
                *(int *)((char *)(temp_a0) - 4) = temp_v1;
                if (temp_v1 == 0) {
                    StringChunk_ReleaseHeader(*temp_a1, temp_a1);
                }
            }
            var_s3 += 1;
            *temp_s2 = temp_s1;
            var_s0 += 4;
        } while (var_s3 < temp_s4);
    }
}
}
