#define ADXT_SCT_LEN 0x800

int ADX_DecodeInfoAinf(unsigned char *hdr, int size, int *ainfsiz, char *dataid, short *volume, short *pan);
extern char adxt_hdr_dataid[];

/* The 16-byte data id of an ADX header's AINF block, or 0 when the header has none. */
char *ADXT_GetHdrDataId(unsigned char *hdr)
{
    short pan[8];
    struct {
        short volume;
        int ainfsiz;
    } ainf;

    ADX_DecodeInfoAinf(hdr, ADXT_SCT_LEN, &ainf.ainfsiz, adxt_hdr_dataid, &ainf.volume, pan);
    return (ainf.ainfsiz != 0) ? adxt_hdr_dataid : 0;
}
