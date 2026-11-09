#define SWAP16(x) ((unsigned short)(((x) << 8) | ((x) >> 8)))

int FUN_0025d540(void *dec, unsigned short *hdr, int size);
int FUN_0025e9f8(unsigned short *hdr);
int FUN_0025e788(void *dec, unsigned short *hdr, int size);
int FUN_0025f200(unsigned short *hdr);
int FUN_0025ec50(void *dec, unsigned short *hdr, int size);
int FUN_0025bfd0(unsigned short *hdr);
int FUN_0025c148(void *dec, unsigned short *hdr, int size);
int FUN_0025c8b8(unsigned short *hdr);
int FUN_0025ca20(void *dec, unsigned short *hdr, int size);
int FUN_0025bac8(unsigned short *hdr);
int FUN_0025ba18(void *dec, unsigned short *hdr, int size);

int FUN_0025d8d8(void *dec, unsigned short *hdr, int size)
{
    if (SWAP16(*hdr) == 0x8000) {
        return FUN_0025d540(dec, hdr, size);
    }
    if (FUN_0025e9f8(hdr) != 0) {
        return FUN_0025e788(dec, hdr, size);
    }
    if (FUN_0025f200(hdr) != 0) {
        return FUN_0025ec50(dec, hdr, size);
    }
    if (FUN_0025bfd0(hdr) != 0) {
        return FUN_0025c148(dec, hdr, size);
    }
    if (FUN_0025c8b8(hdr) != 0) {
        return FUN_0025ca20(dec, hdr, size);
    }
    if (FUN_0025bac8(hdr) != 0) {
        return FUN_0025ba18(dec, hdr, size);
    }
    return -1;
}
