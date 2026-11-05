/* dw4/wav.h — a minimal 16-bit PCM WAV writer.
 *
 * The sound layer's verification artifact: ffmpeg reads the same ADPCM, so a WAV on
 * disk is how a decoded bank can be compared against a reference decoder (and heard).
 * Mono, signed 16-bit little-endian, one `data` chunk; no dependency on libsndfile.
 */
#ifndef DW4_WAV_H
#define DW4_WAV_H

#include <stddef.h>
#include <stdint.h>

/* Write `n` samples as a mono 16-bit PCM WAV.  Returns 0 on success. */
int dw4_wav_write(const char *path, const int16_t *samples, size_t n, uint32_t rate);

#endif /* DW4_WAV_H */
