struct C { char p[56]; struct C *f56; };
int FUN_002fe290(struct C *arg0, struct C *arg1) {
    while (arg0 != 0) {
        if (arg1 == arg0) {
            return 1;
        }
        arg0 = arg0->f56;
    }
    return 0;
}
