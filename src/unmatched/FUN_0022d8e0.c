int igObject_IsKindOf();
int StringChunk_ReleaseHeader();
int igStringMetaField_AssignRetainedToken();
extern int DAT_00585908[4];
struct M { char pad[8]; int f8; };

int FUN_0022d8e0(struct M *arg0, int arg1, int arg2, int arg3) {
    char *sp5C;
    char *t;
    int *temp_a1;
    int temp_v0;
    int var_v0;

    if ((arg0 != 0) && (igObject_IsKindOf(arg0, DAT_00585908[0]) != 0)) {
        asm { nop }
    } else {
        arg0 = 0;
    }
    if ((arg2 != 0) && (igObject_IsKindOf(arg2, DAT_00585908[0]) != 0)) {
        asm { nop }
    } else {
        arg2 = 0;
    }
    var_v0 = 0;
    if ((arg0 != 0) && (arg2 != 0)) {
        sp5C = *(char **)(arg1 + arg0->f8);
        t = sp5C;
        if (t != 0) {
            *(int *)(t - 4) = *(int *)(t - 4) + 1;
        }
        igStringMetaField_AssignRetainedToken(arg2, arg3, &sp5C);
        var_v0 = 1;
        t = sp5C;
        if (t != 0) {
            temp_a1 = (int *)(t - 8);
            temp_v0 = *(int *)(t - 4) - 1;
            *(int *)(t - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
            var_v0 = 1;
        }
    }
    return var_v0;
}
