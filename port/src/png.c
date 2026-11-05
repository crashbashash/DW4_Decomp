/* png.c — a minimal PNG writer.  See dw4/png.h. */
#include "dw4/png.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uint32_t crc_table[256];
static int crc_ready;

static void crc_init(void)
{
    uint32_t c;
    int n, k;

    for (n = 0; n < 256; n++) {
        c = (uint32_t)n;
        for (k = 0; k < 8; k++)
            c = (c & 1) ? 0xedb88320u ^ (c >> 1) : c >> 1;
        crc_table[n] = c;
    }
    crc_ready = 1;
}

static uint32_t crc32_of(const uint8_t *p, size_t n, uint32_t crc)
{
    size_t i;

    if (!crc_ready)
        crc_init();
    for (i = 0; i < n; i++)
        crc = crc_table[(crc ^ p[i]) & 0xff] ^ (crc >> 8);
    return crc;
}

static uint32_t adler32_of(const uint8_t *p, size_t n)
{
    uint32_t a = 1, b = 0;
    size_t i;

    for (i = 0; i < n; i++) {
        a = (a + p[i]) % 65521u;
        b = (b + a) % 65521u;
    }
    return (b << 16) | a;
}

static void be32(uint8_t *p, uint32_t v)
{
    p[0] = (uint8_t)(v >> 24);
    p[1] = (uint8_t)(v >> 16);
    p[2] = (uint8_t)(v >> 8);
    p[3] = (uint8_t)v;
}

static int put_chunk(FILE *f, const char *type, const uint8_t *data, size_t n)
{
    uint8_t hdr[8], crcbuf[4];
    uint32_t crc;

    be32(hdr, (uint32_t)n);
    memcpy(hdr + 4, type, 4);
    if (fwrite(hdr, 1, 8, f) != 8)
        return -1;
    if (n && fwrite(data, 1, n, f) != n)
        return -1;
    crc = crc32_of((const uint8_t *)type, 4, 0xffffffffu);
    crc = crc32_of(data, n, crc) ^ 0xffffffffu;
    be32(crcbuf, crc);
    return fwrite(crcbuf, 1, 4, f) == 4 ? 0 : -1;
}

/* DEFLATE with stored blocks: 5 bytes of overhead per 65535-byte block. */
static int put_idat(FILE *f, const uint8_t *raw, size_t n)
{
    size_t maxb = 65535, off = 0, zcap = n + n / maxb * 5 + 16, zlen = 0;
    uint8_t *z = (uint8_t *)malloc(zcap);
    uint32_t adler = adler32_of(raw, n);
    uint8_t *crcdata;
    int rc;

    if (!z)
        return -1;
    z[zlen++] = 0x78;
    z[zlen++] = 0x01;                    /* zlib header, no preset dict */
    while (off < n) {
        size_t blk = n - off < maxb ? n - off : maxb;
        int last = (off + blk >= n);
        z[zlen++] = (uint8_t)(last ? 1 : 0);
        z[zlen++] = (uint8_t)(blk & 0xff);
        z[zlen++] = (uint8_t)(blk >> 8);
        z[zlen++] = (uint8_t)(~blk & 0xff);
        z[zlen++] = (uint8_t)((~blk >> 8) & 0xff);
        memcpy(z + zlen, raw + off, blk);
        zlen += blk;
        off += blk;
    }
    z[zlen++] = (uint8_t)(adler >> 24);
    z[zlen++] = (uint8_t)(adler >> 16);
    z[zlen++] = (uint8_t)(adler >> 8);
    z[zlen++] = (uint8_t)adler;
    crcdata = z;
    rc = put_chunk(f, "IDAT", crcdata, zlen);
    free(z);
    return rc;
}

int dw4_png_write(const char *path, const uint8_t *rgba, uint32_t w, uint32_t h)
{
    FILE *f;
    uint8_t ihdr[13];
    uint8_t *raw;
    size_t stride = (size_t)w * 4, n, i;
    int rc;

    if (!w || !h)
        return -1;
    f = fopen(path, "wb");
    if (!f)
        return -1;
    raw = (uint8_t *)malloc((stride + 1) * h);
    if (!raw) {
        fclose(f);
        return -1;
    }
    /* each scanline is prefixed with its filter byte (0 = none) */
    for (i = 0; i < h; i++) {
        raw[i * (stride + 1)] = 0;
        memcpy(raw + i * (stride + 1) + 1, rgba + i * stride, stride);
    }
    n = (stride + 1) * h;
    be32(ihdr, w);
    be32(ihdr + 4, h);
    ihdr[8] = 8;                          /* bit depth */
    ihdr[9] = 6;                          /* colour type: RGBA */
    ihdr[10] = 0;
    ihdr[11] = 0;
    ihdr[12] = 0;
    rc = 0;
    if (fwrite("\x89PNG\r\n\x1a\n", 1, 8, f) != 8)
        rc = -1;
    if (!rc)
        rc = put_chunk(f, "IHDR", ihdr, sizeof(ihdr));
    if (!rc)
        rc = put_idat(f, raw, n);
    if (!rc)
        rc = put_chunk(f, "IEND", NULL, 0);
    free(raw);
    fclose(f);
    return rc;
}
