extern char *DAT_004c22f0[4];
typedef struct ShortStr { char pad[8]; char *text; } ShortStr;
typedef struct L { char pad[8]; int count; int cap; ShortStr **data; } L;
static inline char *text(ShortStr *s) { char *t = s->text; if (t == 0) { return DAT_004c22f0[0]; } return t; }
int FUN_0030bfa0(L *self, int key, int (*cmp)(char *, int)) {
    int lo;
    int hi;
    int mid;
    int c;

    lo = 0;
    hi = self->count - 1;
    while (lo < hi) {
        mid = (lo + hi) >> 1;
        c = cmp(text(self->data[mid]), key);
        if (c < 0) {
            lo = mid + 1;
        } else if (c > 0) {
            hi = mid - 1;
        } else {
            return mid;
        }
    }
    if (self->count == 0) {
        return -1;
    }
    if (cmp(text(self->data[lo]), key) == 0) {
        return lo;
    }
    return -1;
}
