/* Makes a decoder handle current (0x00573f00) and validates it: returns 0 when its state word is
 * 2, -1 otherwise or for a null handle. */
struct Decoder28b {
    int state;   /* +0: 2 = valid */
};

extern struct Decoder28b *DAT_00573f00;

int FUN_0028b098(struct Decoder28b *decoder) {
    DAT_00573f00 = decoder;
    if (decoder == 0) {
        return -1;
    }
    return decoder->state == 2 ? 0 : -1;
}
