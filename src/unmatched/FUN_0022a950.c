struct S22 { int a0, a1, b, c; };
int FUN_002fe300();
int igMetaObject_CountTree();
int FUN_0022a950(struct S22 *arg0) {
    int temp_s0;
    temp_s0 = arg0->c;
    if ((temp_s0 >= igMetaObject_CountTree(arg0->b)) || (temp_s0 < 0)) {
        return 0;
    }
    return FUN_002fe300(arg0->b, temp_s0);
}
