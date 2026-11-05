int FUN_004578c0();
extern int DAT_0058cb08[4];
struct Y { char p[20]; struct YT *t; };
struct YT { char p[244]; int f244; };
void FUN_00462d80(struct Y *arg0) {
    int buf[3];

    arg0->t->f244 = 0;
    buf[0] = 2;
    buf[1] = 0;
    buf[2] = DAT_0058cb08[0];
    FUN_004578c0(arg0->t, buf);
}
