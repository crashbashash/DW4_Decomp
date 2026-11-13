#include "dw4/sony/libmpeg.h"

int scePrintf(const char *format, ...);
int sprintf(char *buf, const char *format, ...);

void _ErrMessage(char *message) {
    scePrintf("[MPEG ERROR]%s\n", message);
}

void _sceMpegError1(_sceMpegDecoder *dec, char *format, int value) {
    char message[256];

    sprintf(message, format, value);
    _sceMpegError(dec, message);
}

/* An error goes to the stream's error callback when one is registered, else to the console. */
void _sceMpegError(_sceMpegDecoder *dec, char *message) {
    sceMpegCbDataError cbdata;

    if (dec->mp != 0 && dec != 0 && dec->callbacks[sceMpegCbError].func != 0) {
        cbdata.type = sceMpegCbError;
        cbdata.errMessage = message;
        _sceMpegDispatchMpegCallback(dec->mp, (sceMpegCbData *)&cbdata);
    } else {
        _ErrMessage(message);
    }
}
