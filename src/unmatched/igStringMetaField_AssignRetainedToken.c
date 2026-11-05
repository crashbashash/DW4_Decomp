#include "dw4/reflected.h"
int StringChunk_ReleaseHeader();

void igStringMetaField_AssignRetainedToken(igStringMetaField *arg0, int arg1, void **arg2) {
    int *temp_a1;
    int temp_v1;
    void **temp_s0;
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = (void *)(*arg2);
    temp_s0 = (void **)(arg1 + arg0->_offset);
    if (temp_a0 != 0) {
        *(int *)((char *)(temp_a0) - 4) = (int)((int) (*(int *)((char *)(temp_a0) - 4) + 1));
    }
    temp_a0_2 = (void *)(*temp_s0);
    if (temp_a0_2 != 0) {
        temp_a1 = (int *)((char *)temp_a0_2 - 8);
        temp_v1 = *(int *)((char *)(temp_a0_2) - 4) - 1;
        *(int *)((char *)(temp_a0_2) - 4) = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    *temp_s0 = *arg2;
}
