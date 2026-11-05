/* 0x0029f9f0 — FUN_0029f9f0 (120 bytes). Returns the bit rate (table DAT_004f4bf0 x 1000) of the first frame header in data, or -1. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
unsigned char *FUN_0029fbc8();
extern int DAT_004f4bf0[];

/* Frame header fields unpacked by FUN_0029fc98 from an 0xFFFx sync word (layout of an MPEG audio
 * header: f0 version, f2 bitrate index with 15 invalid, f3 sample-rate index with 3 reserved). */
struct FrameHeader {
    unsigned char f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10;
};

/* Bit rate in bits per second of the first frame in data, or -1. */
int FUN_0029f9f0(unsigned char *data, int length) {
    struct FrameHeader header;
    int rate;

    if (FUN_0029fbc8(&header, data, length) == 0) {
        return -1;
    }
    rate = DAT_004f4bf0[header.f0 * 16 + header.f2];
    if (rate == -1) {
        return -1;
    }
    return rate * 1000;
}
