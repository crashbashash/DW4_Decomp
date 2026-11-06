/* Classifies a handle from three flags: +4 set gives 1 (with +12) or 3; otherwise +8 set without
 * +12 gives 2; else 0. */

struct Flags002933f8 {
    int f0;
    int f4;  /* +4 */
    int f8;  /* +8 */
    int f12; /* +12 */
};

int FUN_002933f8(struct Flags002933f8 *flags) {
    int kind = 0;

    if (flags->f4 == 0) {
        if (flags->f8 != 0) {
            if (flags->f12 == 0) {
                kind = 2;
            }
        }
    } else {
        kind = (flags->f12 == 0) ? 3 : 1;
    }
    return kind;
}
