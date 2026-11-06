/* Flag byte set/clear via typed |= and &= ~ (lbu/sb). */
typedef struct { char pad[64]; unsigned char flags; } T;
void FUN_001b4090(T *arg0, int arg1, int arg2) {
    if (arg1 < 8) {
        if (arg2 != 0) {
            arg0->flags |= (1 << arg1);
        } else {
            arg0->flags &= ~(1 << arg1);
        }
    }
}
