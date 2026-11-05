/* 0x0028da60 — FUN_0028da60 (36 bytes). Makes a stream handle current (0x00573f0c) and validates it:
   returns -1 for a null handle or one whose state word is 1, 0 otherwise. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Stream28d {
    int state;   /* +0: 1 = invalid */
};

extern struct Stream28d *DAT_00573f0c;

int FUN_0028da60(struct Stream28d *stream) {
    DAT_00573f0c = stream;
    if (stream == 0) {
        return -1;
    }
    return stream->state != 1 ? 0 : -1;
}
