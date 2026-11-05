struct S { char pad[1304]; float f1304; int i1308; char pad2[16]; float f1328; float f1332; };
int FUN_001e8a90(int, int, float, float, float, float, float, float);
extern int DAT_0048a560[4];
extern int DAT_005609dc[4];
void FUN_00175310(struct S *arg0, float fparg0) {
    int temp_a1;

    if (arg0->f1328 == fparg0) {
        DAT_005609dc[0] += 1;
    }
    arg0->f1328 = fparg0;
    temp_a1 = arg0->i1308;
    FUN_001e8a90(*(int *)((char *)&DAT_0048a560[0] + (temp_a1 * 4)), temp_a1, arg0->f1328, arg0->f1332, arg0->f1304, 1.0f, 0.0f, 0.0f);
}
