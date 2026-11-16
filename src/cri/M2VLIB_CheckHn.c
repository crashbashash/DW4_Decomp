/* Makes a decoder handle current (0x00573f00) and validates it: returns 0 when its state word is
 * 2, -1 otherwise or for a null handle. */
struct Decoder28b {
    int state;   /* +0: 2 = valid */
};

extern struct Decoder28b *m2vlib_m2vobj;

int M2VLIB_CheckHn(struct Decoder28b *decoder) {
    m2vlib_m2vobj = decoder;
    if (decoder == 0) {
        return -1;
    }
    return decoder->state == 2 ? 0 : -1;
}
