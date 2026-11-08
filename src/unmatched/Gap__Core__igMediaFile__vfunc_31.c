int memcpy();
int vsprintf();
int FUN_002ec570();
struct F { char pad[44]; unsigned char f44; char pad2[7]; int f52; int f56; int f60; };
int Gap__Core__igMediaFile__vfunc_31(struct F *self, int fmt, ...) {
    char buf[16384];
    int n;
    int off;
    int len;
    int pos;
    if (self->f44 != 0) {
        return -1;
    }
    n = __builtin_args_info(2);
    if (n >= 8) {
        off = 0;
    } else {
        off = (8 - n) * 8;
    }
    len = vsprintf(buf, fmt, (char *)__builtin_next_arg(fmt) - off);
    pos = self->f56 + len;
    if (pos >= self->f52) {
        FUN_002ec570(self, pos);
    }
    memcpy(self->f60 + self->f56, buf, len);
    self->f56 = self->f56 + len;
    return len;
}
