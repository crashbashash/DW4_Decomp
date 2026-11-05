/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int beMessenger_AppendBool(int, int);
int beMessenger_AppendFloat(int, float);
int beMessenger_AppendString(int, int);
int beMessenger_AppendVec3(int, float *);
int beMessenger_EnqueueSelected(int, int *, int);
int beMessenger_PrepareDelayedSelection(int, int *, int, int);
extern int DAT_004cfb40[4];
extern int DAT_004cfb44[4];
extern float DAT_004e1058[4];
extern float DAT_004e105c[4];
extern float DAT_004e1060[4];
extern int DAT_0051ce80[4];
extern int DAT_0051ce88[4];
struct A0 { char pad[20]; int f20; };
void FUN_004412c0(struct A0 *arg0, int arg1, int arg2) {
    float sp30[4];
    int temp_s1;

    beMessenger_PrepareDelayedSelection(arg0->f20, &DAT_0051ce80[0], 0, arg2);
    temp_s1 = (arg1 - 1) * 8;
    beMessenger_AppendString(arg0->f20, *(int *)((char *)DAT_004cfb40 + temp_s1));
    beMessenger_AppendString(arg0->f20, *(int *)((char *)DAT_004cfb44 + temp_s1));
    beMessenger_AppendFloat(arg0->f20, 1.0f);
    sp30[0] = DAT_004e1058[0];
    sp30[1] = DAT_004e105c[0];
    sp30[2] = DAT_004e1060[0];
    beMessenger_AppendVec3(arg0->f20, sp30);
    beMessenger_AppendBool(arg0->f20, 0);
    beMessenger_AppendBool(arg0->f20, 1);
    beMessenger_EnqueueSelected(arg0->f20, &DAT_0051ce88[0], 1);
}
} /* extern "C" */
