/* Unpacks the bit fields of header bytes 1..3 into eleven FrameHeader bytes. */
/* Frame header fields unpacked by FUN_0029fc98 from an 0xFFFx sync word (layout of an MPEG audio
 * header: f0 version, f2 bitrate index with 15 invalid, f3 sample-rate index with 3 reserved). */
struct FrameHeader {
    unsigned char f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10;
};

void FUN_0029fc98(struct FrameHeader *header, unsigned char *bytes) {
    unsigned char b1 = bytes[1];
    unsigned char b2 = bytes[2];
    unsigned char b3 = bytes[3];

    header->f0 = (b1 >> 1) & 3;
    header->f1 = b1 & 1;
    header->f2 = b2 >> 4;
    header->f3 = (b2 >> 2) & 3;
    header->f4 = (b2 >> 1) & 1;
    header->f5 = b2 & 1;
    header->f6 = b3 >> 6;
    header->f7 = (b3 >> 4) & 3;
    header->f8 = (b3 >> 3) & 1;
    header->f9 = (b3 >> 2) & 1;
    header->f10 = b3 & 3;
}
