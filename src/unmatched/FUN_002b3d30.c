/* Reports the two words of the sub-record at +24 when its state is 1, else zeros. */

struct Sub0018 {
    int state;                            /* 1: the two values are valid */
    int f4;
    int f8;
};

struct Obj0018 {
    char pad[24];
    struct Sub0018 sub;                   /* +24 */
};

void FUN_002b3d30(struct Obj0018 *obj, int *out4, int *out8) {
    struct Sub0018 *sub = &obj->sub;
    int value4, value8;

    if (sub->state != 1) {
        *out4 = 0;
        *out8 = 0;
        return;
    }
    /* Both reads precede the stores: the outputs could alias the record. */
    value4 = sub->f4;
    value8 = sub->f8;
    *out8 = value8;
    *out4 = value4;
}
