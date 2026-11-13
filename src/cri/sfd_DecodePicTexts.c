/* Decodes the two element texts of a picture record's text block (+48) with the decoder in *dst;
 * reports error 0xFF000D0D on the handle when either decode fails. */
typedef struct {
    char text0[176];        /* +0 */
    char text1[176];        /* +176 */
    int length0;            /* +352 */
    int length1;            /* +356 */
} SfdTextBlock;

typedef struct {
    char pad0[48];
    SfdTextBlock block;     /* +48 */
} SfdPicRecord;

typedef struct {
    void *decoder;          /* +0 */
} SfdPicDst;

extern int MPS_DecodeChunk(void *decoder, char *text, int length, int *consumed, int *flags);
extern int sfd_ReportError(void *handle, int code);

int sfd_DecodePicTexts(void *handle, SfdPicDst *dst, SfdPicRecord *rec) {
    int consumed;
    int flags;
    SfdTextBlock *block = &rec->block;
    void *decoder = dst->decoder;
    int r0 = MPS_DecodeChunk(decoder, block->text0, block->length0, &consumed, &flags);
    int r1 = MPS_DecodeChunk(decoder, block->text1, block->length1, &consumed, &flags);

    if (r0 != 0 || r1 != 0) {
        return sfd_ReportError(handle, 0xFF000D0D);
    }
    return r1;
}
