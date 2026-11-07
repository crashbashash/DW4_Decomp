int igObject_IsKindOf();
int StringChunk_ReleaseHeader();
int igStringMetaField_AssignRetainedToken();
extern int DAT_00585908[4];
struct M { char pad[8]; int f8; };

static inline void * cast0(void * o) { if (o != 0 && igObject_IsKindOf(o, DAT_00585908[0]) != 0) { return o; } return 0; }
int FUN_0022d8e0(struct M *arg0, int arg1, int arg2, int arg3) {
    char *sp5C;
    char *t;
    int *temp_a1;
    int temp_v0;
    int var_v0;

    arg0 = cast0(arg0);
    arg2 = (int)cast0((void *)arg2);
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
    else { var_v0 = 0; }
    return var_v0;
}
