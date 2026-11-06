struct P { int a; int b; };
extern struct P DAT_005691d0[16];
void FUN_001f0410(int arg0, int arg1) {
    int i = 0;
    while (i < 10 && DAT_005691d0[i].a != 0) {
        i += 1;
    }
    DAT_005691d0[i].a = arg0;
    DAT_005691d0[i].b = arg1;
}
