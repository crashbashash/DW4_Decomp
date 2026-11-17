/* libcdvd_calls.h - the libcdvd calls the game makes at start-up (Sony libcdvd.h): drive initialisation and
 * the media mode. The library's own shared state stays in dw4/sony/libcdvd.h. */
#ifndef DW4_SONY_LIBCDVD_CALLS_H
#define DW4_SONY_LIBCDVD_CALLS_H

#ifdef __cplusplus
extern "C" {
#endif

int sceCdInit(int init_mode);
int sceCdMmode(int media);

#ifdef __cplusplus
}
#endif

#endif
