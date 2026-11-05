int FUN_004578c0();
extern int DAT_0058c290[4];
struct T { char pad[36]; unsigned char b; };
struct S { char pad[8]; struct T *t; };
void FUN_00457c40(struct S *arg0, unsigned char arg1) {
    int sp[3];
    unsigned char temp_a2;
    struct T *temp_v1;
    unsigned char *pb;

    temp_v1 = arg0->t;
    if (temp_v1 != 0) {
        temp_a2 = temp_v1->b;
        pb = &temp_v1->b;
        if (temp_a2 != arg1) {
            *pb = arg1;
            sp[0] = 2;
            sp[1] = 0;
            sp[2] = DAT_0058c290[0];
            FUN_004578c0(arg0->t, sp, temp_a2, pb);
        }
    }
}
