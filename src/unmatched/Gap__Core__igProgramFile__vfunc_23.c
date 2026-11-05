#include "dw4/reflected.h"
typedef struct T { int word0; int references; } T;
int FUN_002eb010();
int StringChunk_ReleaseHeader();
int StringPool_Construct();
char *StringPool_Intern();
void igObject_Destroy(T *);
extern int DAT_00586f20[4];
void Gap__Core__igProgramFile__vfunc_23(igProgramFile *arg0) {
    int *temp_a1;
    int temp_v1;
    int var_v0;
    char *temp_a0;
    T *temp_a0_2;
    char *temp_s1;

    if (DAT_00586f20[0] == 0) {
        var_v0 = FUN_002eb010(0x10);
        if (var_v0 != 0) {
            var_v0 = StringPool_Construct(var_v0);
        }
        DAT_00586f20[0] = var_v0;
    }
    temp_s1 = StringPool_Intern(DAT_00586f20[0], 0);
    temp_a0 = (char *)arg0->_fileName;
    if (temp_a0 != 0) {
        temp_a1 = (int *)(temp_a0 - 8);
        temp_v1 = *(int *)(temp_a0 - 4) - 1;
        *(int *)(temp_a0 - 4) = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    arg0->_fileName = (int)temp_s1;
    temp_a0_2 = (T *)arg0->_file;
    if (temp_a0_2 != 0) {
        --temp_a0_2->references;
        if (((unsigned long long)(long long)temp_a0_2->references & 0x7fffffULL) == 0) {
            igObject_Destroy(temp_a0_2);
        }
    }
    arg0->_file = 0;
}
