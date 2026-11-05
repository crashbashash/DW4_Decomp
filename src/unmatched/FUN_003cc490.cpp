#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int StringChunk_ReleaseHeader(int, int *);

void FUN_003cc490(igDataList *arg0, char **arg1) {
    int *temp_a1;
    int temp_s2;
    int temp_v1;
    char **var_s1;
    int var_s0;
    char *temp_a0;
    char *temp_a0_2;

    temp_s2 = arg0->_count;
    var_s1 = (char **)arg0->_data;
    var_s0 = 0;
    if (0 < temp_s2) {
        do {
            temp_a0 = *arg1;
            if (temp_a0 != 0) {
                *(int *)(temp_a0 - 4) = *(int *)(temp_a0 - 4) + 1;
            }
            temp_a0_2 = *var_s1;
            if (temp_a0_2 != 0) {
                temp_a1 = (int *)(temp_a0_2 - 8);
                temp_v1 = *(int *)(temp_a0_2 - 4) - 1;
                *(int *)(temp_a0_2 - 4) = temp_v1;
                if (temp_v1 == 0) {
                    StringChunk_ReleaseHeader(*temp_a1, temp_a1);
                }
            }
            var_s0 += 1;
            *var_s1 = *arg1;
            var_s1 += 1;
        } while (var_s0 < temp_s2);
    }
}
} /* extern "C" */
