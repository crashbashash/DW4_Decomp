typedef struct B {
    signed char type;
    signed char s0:2;
    unsigned char c:1;
    unsigned char u3:2;
    unsigned char d:1;
    unsigned char e:1;
    unsigned char f:1;
    short flags;
} B;
void FUN_0023cb40(B *b) {
    int v;
    v = b->c != 0;
    if (v != 0) {
        v = b->s0 > 0;
        if (v == 0) {
            v = b->type != 14;
        }
    }
    b->d = v;
    v = b->s0 == 1;
    if (v != 0) {
        v = b->type == 14;
    }
    b->e = v;
    b->flags = 0;
    if (b->s0 > 0) {
        if (b->type == 17 && b->s0 == 1) {
            b->flags |= 0xA;
        } else {
            b->flags |= 3;
        }
    } else {
        if (b->type == 14) {
            b->flags |= 1;
        } else if (b->type == 10) {
            b->flags |= 0xC;
        } else if (b->type == 13) {
            b->flags |= 0xA;
        } else if ((unsigned int)(b->type - 15) <= 1U || b->type == 0) {
            b->flags = 0;
        } else {
            b->flags |= 4;
        }
    }
    if (b->c != 0) b->flags &= ~2;
    if (b->d != 0 || b->e != 0) b->flags |= 0x10;
}
