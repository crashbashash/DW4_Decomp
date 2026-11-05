/* Field fetched before the zeroed vector local is filled; float constant typed; verified by tools/verify.py. */
int FUN_0018e470(int, int *);
int FUN_002e3810(int, float);
int igMetaObject_CreateFields();
int igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048ada0[4];
extern int DAT_0048ada8[4];
extern int DAT_0048adb0[4];
extern int DAT_0048adb8[4];
extern int DAT_00560fa0[4];
void igSphere_InitFields(void) {
    int v[3];
    void *temp_s0;
    int temp_s1;
    int temp_a0;

    temp_s0 = (void *)DAT_00560fa0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048ada0[0], 2);
    temp_a0 = igMetaObject_GetFieldAt(temp_s0, temp_s1);
    v[0] = 0;
    v[1] = 0;
    v[2] = 0;
    FUN_0018e470(temp_a0, v);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1), -1.0f);
    igMetaObject_NameFields(temp_s0, &DAT_0048ada8[0], &DAT_0048adb0[0], &DAT_0048adb8[0], temp_s1);
}
