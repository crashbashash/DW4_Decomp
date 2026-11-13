typedef struct {
    char pad0[308];
    int error;
    char pad1[1832];
    int mpeg1;
} MpegDecoder;

extern char invalidMacroblockAddressIncrement[]; /* "Invalid macroblock_address_increment code(0x%08x)" */

unsigned int _ipuVdec(MpegDecoder *dec, int table);
unsigned int _ipuShowBits(MpegDecoder *dec, int n);
void _ipuFlushBits(MpegDecoder *dec, int n);
int _sceMpegErrorf(MpegDecoder *dec, char *fmt, ...);

#define VDEC_MACROBLOCK_ADDRESS_INCREMENT 0
#define MBAI_STUFFING 34
#define MBAI_ESCAPE 35
#define MPEG1_STUFFING_CODE 15

int _getMacroblockAddressIncrement(MpegDecoder *dec) {
    int increment = 0;
    unsigned int code;
    int more;
    unsigned int bits;

    do {
        code = _ipuVdec(dec, VDEC_MACROBLOCK_ADDRESS_INCREMENT);
        switch (code) {
        case MBAI_STUFFING:
            more = 1;
            break;
        case MBAI_ESCAPE:
            more = 1;
            increment += 33;
            break;
        case 0:
            bits = _ipuShowBits(dec, 11);
            if (dec->mpeg1 && bits == MPEG1_STUFFING_CODE) {
                _ipuFlushBits(dec, 11);
                more = 1;
                break;
            }
            _sceMpegErrorf(dec, invalidMacroblockAddressIncrement, code);
            dec->error = 1;
            return 1;
        default:
            increment += code;
            more = 0;
            break;
        }
    } while (more);
    return increment;
}
