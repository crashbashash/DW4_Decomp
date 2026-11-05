/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
struct F { char pad[38]; unsigned char b38; char pad2[17]; int f56; };
extern "C" {
int FUN_00142f70(void);
int FUN_0014a040(void);
int igMetaObject_CreateFields(void *, int *, int);
struct F *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c2890[4];
extern int DAT_004c28a0[4];
extern int DAT_004c28b0[4];
extern int DAT_004c28c0[4];
extern int DAT_00587740[4];
void igCriMovieCodec_InitFields(void);
}
void igCriMovieCodec_InitFields(void) {
    int temp_s2;
    struct F *temp_s1;
    struct F *temp_s1_2;
    void *temp_s0;
    struct F *t0;

    temp_s0 = (void *)DAT_00587740[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c2890[0], 3);
    t0 = (struct F *)igMetaObject_GetFieldAt(temp_s0, temp_s2);
    t0->b38 = 0;
    temp_s1 = (struct F *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    temp_s1->f56 = FUN_0014a040();
    temp_s1->b38 = 0;
    temp_s1_2 = (struct F *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    temp_s1_2->f56 = FUN_00142f70();
    temp_s1_2->b38 = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004c28a0[0], &DAT_004c28b0[0], &DAT_004c28c0[0], temp_s2);
}
