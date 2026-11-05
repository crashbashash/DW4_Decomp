struct F { char pad[52]; int f52; };
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048daf0[4];
extern int DAT_0048daf8[4];
extern int DAT_0048db00[4];
extern int DAT_0048db08[4];
extern int DAT_00562b88[4];
void igMersenneTwisterRandomNumber_InitFields(void) {
    int temp_s0;
    int temp_s1;
    struct F *f;

    temp_s0 = DAT_00562b88[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048daf0[0], 2);
    f = (struct F *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1);
    f->f52 = 0x270;
    igMetaObject_NameFields(temp_s0, &DAT_0048daf8[0], &DAT_0048db00[0], &DAT_0048db08[0], temp_s1);
}
