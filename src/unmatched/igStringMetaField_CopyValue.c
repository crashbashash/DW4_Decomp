#include "dw4/reflected.h"
int StringChunk_ReleaseHeader();
int igStringMetaField_AssignRetainedToken();

void igStringMetaField_CopyValue(igStringMetaField *arg0, int arg1, int arg2) {
    void *sp1C;
    int *temp_a1;
    int temp_v1;

    sp1C = (void *)(*(int *)(arg2 + arg0->_offset));
    if (sp1C != 0) {
        *(int *)((char *)(sp1C) - 4) = (int)((int) (*(int *)((char *)(sp1C) - 4) + 1));
    }
    igStringMetaField_AssignRetainedToken(arg0, arg1, &sp1C);
    if (sp1C != 0) {
        temp_a1 = (int *)((char *)sp1C - 8);
        temp_v1 = *(int *)((char *)(sp1C) - 4) - 1;
        *(int *)((char *)(sp1C) - 4) = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
}
