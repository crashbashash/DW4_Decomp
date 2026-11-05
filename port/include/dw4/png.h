/* dw4/png.h — a minimal PNG writer (RGBA8), so the port can show what it decoded.
 *
 * Deliberately dependency-free: the image data is emitted as stored (uncompressed)
 * DEFLATE blocks.  The files are larger than a compressed PNG, which is fine for a
 * decode/verification artifact, and it keeps the asset layer buildable anywhere.
 */
#ifndef DW4_PNG_H
#define DW4_PNG_H

#include <stdint.h>

/* `rgba` is w*h*4 bytes, row-major, 8 bits per channel.  Returns 0 on success. */
int dw4_png_write(const char *path, const uint8_t *rgba, uint32_t w, uint32_t h);

#endif /* DW4_PNG_H */
