int FUN_0028de10(int data, int size, int code);
int FUN_0028dc78(int p);

struct Buf0028f400 {
    int data;
    int size;
};

struct Obj0028f400 {
    char pad0[856];
    int kind; /* +856 */
};

int FUN_0028f400(struct Obj0028f400 *obj, struct Buf0028f400 *buf) {
    int r;
    int state;
    int n;

    r = obj->kind;
    if (r != 0) {
        return r;
    }
    r = FUN_0028de10(buf->data, buf->size, 64);
    if (r == 0) {
        return obj->kind;
    }
    r += 4;
    r = FUN_0028de10(r, buf->size - (r - buf->data), -1);
    if (r == 0) {
        return obj->kind;
    }
    r = FUN_0028dc78(r);
    if (r & 0x10) {
        obj->kind = 2;
    } else if (r != 0) {
        obj->kind = 1;
    }
    return obj->kind;
}
