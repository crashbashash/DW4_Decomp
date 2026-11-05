#include "dw4/reflected.h"
int StringChunk_ReleaseHeader();
int StringList_Resize();

void StringList_AppendRetained(igStringRefList *arg0, void **arg1) {
    int *temp_a1_2;
    int temp_s0;
    int temp_v1;
    void **temp_s0_2;
    void *temp_a0;
    void *temp_a1;

    temp_s0 = arg0->_count;
    StringList_Resize(arg0, temp_s0 + 1);
    temp_a1 = (void *)(*arg1);
    temp_s0_2 = (void **)(arg0->_data + (temp_s0 * 4));
    if (temp_a1 != 0) {
        *(int *)((char *)(temp_a1) - 4) = (int)((int) (*(int *)((char *)(temp_a1) - 4) + 1));
    }
    temp_a0 = (void *)(*temp_s0_2);
    if (temp_a0 != 0) {
        temp_a1_2 = (int *)((char *)temp_a0 - 8);
        temp_v1 = *(int *)((char *)(temp_a0) - 4) - 1;
        *(int *)((char *)(temp_a0) - 4) = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader(*temp_a1_2, temp_a1_2);
        }
    }
    *temp_s0_2 = *arg1;
}
