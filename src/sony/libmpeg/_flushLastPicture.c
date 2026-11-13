typedef struct {
    char pad0[304];
    int frameNo;
    char pad1[4];
    int awaitingSecondField;
    char pad2[80];
    int pictureStructure;
    char pad3[68];
    int *framePicture;
    char pad4[12];
    int *topField;
    char pad5[12];
    int *bottomField;
} MpegDecoder;

#define FRAME_PICTURE 3

extern char secondFieldMissing[]; /* "the second field is missing" */
int _sceMpegMessage(MpegDecoder *dec, char *msg);
void _outputFrame(MpegDecoder *dec, int *picture, int frameNo);
void _outputFieldPair(MpegDecoder *dec, int *top, int *bottom, int frameNo);

void _flushLastPicture(MpegDecoder *dec) {
    int frameNo = dec->frameNo;

    if (dec->awaitingSecondField) {
        _sceMpegMessage(dec, secondFieldMissing);
    } else if (dec->pictureStructure == FRAME_PICTURE) {
        _outputFrame(dec, dec->framePicture, frameNo - 1);
    } else {
        _outputFieldPair(dec, dec->topField, dec->bottomField, frameNo - 1);
    }
    dec->awaitingSecondField = 0;
}
