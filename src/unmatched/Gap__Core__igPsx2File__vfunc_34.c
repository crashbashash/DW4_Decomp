struct F { char p0[44]; unsigned char *buf; int p1; int pos; int p2; int err; };
int Gap__Core__igPsx2File__vfunc_34(struct F *arg0, int arg1) {
    int temp_v0;
    int var_a1;

    var_a1 = arg1;
    if (arg0->err != 0) {
        return -1;
    }
    temp_v0 = arg0->pos;
    if (temp_v0 == 0) {
        return -1;
    }
    arg0->pos = temp_v0 - 1;
    if ((var_a1 & 0xFF) != arg0->buf[arg0->pos]) {
        var_a1 = -1;
    }
    return var_a1;
}
