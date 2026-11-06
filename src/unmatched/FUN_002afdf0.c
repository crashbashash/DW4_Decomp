/* Initialises a small record: clears +0/+4, stores the argument at +12, 8 into +16 and the three
 * words at +20..+28, and -1 into +32. */

struct Rec24 {
    int f0, f4, f8;
    int f12;
    int f16;
    int f20[3];
    int f32;
};

void FUN_002afdf0(struct Rec24 *rec, int value) {
    int i;

    rec->f4 = 0;
    rec->f0 = 0;
    rec->f12 = value;
    rec->f16 = 8;
    /* The three nops in the retail loop are the EE short-loop padding the toolchain inserts, not source. */
    for (i = 2; i >= 0; i--) {
        rec->f20[i] = 8;
    }
    rec->f32 = -1;
}
