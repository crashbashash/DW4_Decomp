/* Textures read from a live EE RAM dump. A stage's world and character textures are not always in
 * a texture pack: the material graph the live engine builds points at `igPsx2Image` objects whose
 * `_pImage`/`_pClut` are ordinary pointers at runtime (in a pack they are load-time ordinals). So
 * the same EE RAM dump that supplies the scene placement (`--scene`) also supplies the pixels. The
 * object walked here is the reflective `igPsx2Image` (the runtime class of `igImage`): _px +0x08,
 * _py +0x0c, _imageSize +0x30, _pImage +0x34, _pClut +0x44, _bitsIdx +0x48, _bytesPerRow +0x4c,
 * _pNameString +0x58; and its `igClut` (`_numEntries` +0x0c, `_stride` +0x10, `_pData` +0x14). The
 * dump's base is auto-detected: a 31 MB image is EE RAM from 0x00100000 (the low 1 MB is kernel),
 * a 32 MB image is the whole RAM from 0. A 32 MB extraction should be trimmed to 0x00100000 first. */
#ifndef DW4_LIVETEX_H
#define DW4_LIVETEX_H

#include <stdint.h>

typedef struct dw4_livetex dw4_livetex;

/* Open a dump.  Returns NULL when the file cannot be read. */
dw4_livetex *dw4_livetex_open(const char *path);
void dw4_livetex_close(dw4_livetex *lt);

/* The number of distinct, decodable `igPsx2Image` names found in the dump. */
int dw4_livetex_count(const dw4_livetex *lt);
const char *dw4_livetex_name(const dw4_livetex *lt, int i);

/* Decode one named texture to RGBA8888 (row-major, `w*h*4`, flipped so it is bottom-up like
 * `dw4_texpack_rgba`).  `*rgba` is malloc'd and owned by the caller.  Returns 0, or -1 when the
 * name is absent or the buffers do not cover the image. */
int dw4_livetex_get(dw4_livetex *lt, const char *name, uint8_t **rgba, int *w, int *h);

#endif /* DW4_LIVETEX_H */
