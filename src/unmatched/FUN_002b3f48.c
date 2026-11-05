/* 0x002b3f48 — FUN_002b3f48 (136 bytes). Rounds both dimensions down to even and sets up the three planes at +4, +20 and +36 through FUN_002b3fd0: the first at full size, the other two at half size. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Plane16 {
    int words[4];
};

struct Frame {
    int f0;
    struct Plane16 planes[3]; /* +4, +20, +36 */
};

void FUN_002b3fd0(struct Plane16 *plane, int first, int second);

void FUN_002b3f48(struct Frame *frame, int second, int first) {
    first = first / 2 * 2;
    second = second / 2 * 2;
    FUN_002b3fd0(&frame->planes[0], first, second);
    FUN_002b3fd0(&frame->planes[1], first >> 1, second >> 1);
    FUN_002b3fd0(&frame->planes[2], first >> 1, second >> 1);
}
