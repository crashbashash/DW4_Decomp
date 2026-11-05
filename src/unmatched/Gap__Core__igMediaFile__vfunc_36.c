struct F { char pad[44]; unsigned char f44; char pad2[7]; int len; int pos; unsigned char *data; };
char *Gap__Core__igMediaFile__vfunc_36(struct F *arg0, char *arg1, int arg2) {
    /* matching construct: variant search — decl order [3, 2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    unsigned char c;
    int pos;
    int len;
    int i;
    if (arg1 == 0) return 0;
    if (arg0->f44 != 0) return 0;
    len = arg0->len;
    pos = arg0->pos;
    if (pos >= len) return 0;
    i = 0;
    arg2 = arg2 - 1;
    if (arg2 + pos >= len) arg2 = len - pos;
    while (i < arg2) {
        c = arg0->data[arg0->pos];
        arg1[i] = c;
        i++;
        arg0->pos = arg0->pos + 1;
        if (c == 10) break;
    }
    arg1[i] = 0;
    return arg1;
}
