/* src/wav.c — a minimal 16-bit PCM WAV writer.  See dw4/wav.h. */
#include "dw4/wav.h"

#include <stdio.h>

static void put32(uint8_t *p, uint32_t v)
{
    p[0] = (uint8_t)v;
    p[1] = (uint8_t)(v >> 8);
    p[2] = (uint8_t)(v >> 16);
    p[3] = (uint8_t)(v >> 24);
}

static void put16(uint8_t *p, uint16_t v)
{
    p[0] = (uint8_t)v;
    p[1] = (uint8_t)(v >> 8);
}

int dw4_wav_write(const char *path, const int16_t *samples, size_t n, uint32_t rate)
{
    uint8_t hdr[44];
    FILE *f;
    uint32_t data = (uint32_t)(n * 2);

    if (!path || (!samples && n))
        return -1;
    f = fopen(path, "wb");
    if (!f)
        return -1;

    hdr[0] = 'R'; hdr[1] = 'I'; hdr[2] = 'F'; hdr[3] = 'F';
    put32(hdr + 4, 36 + data);
    hdr[8] = 'W'; hdr[9] = 'A'; hdr[10] = 'V'; hdr[11] = 'E';
    hdr[12] = 'f'; hdr[13] = 'm'; hdr[14] = 't'; hdr[15] = ' ';
    put32(hdr + 16, 16);                 /* fmt chunk size */
    put16(hdr + 20, 1);                  /* PCM */
    put16(hdr + 22, 1);                  /* mono */
    put32(hdr + 24, rate);
    put32(hdr + 28, rate * 2);           /* byte rate */
    put16(hdr + 32, 2);                  /* block align */
    put16(hdr + 34, 16);                 /* bits per sample */
    hdr[36] = 'd'; hdr[37] = 'a'; hdr[38] = 't'; hdr[39] = 'a';
    put32(hdr + 40, data);

    if (fwrite(hdr, 1, sizeof(hdr), f) != sizeof(hdr)) {
        fclose(f);
        return -1;
    }
    if (n) {
        /* WAV is little-endian; on a big-endian host this would need a byte swap. */
        const uint8_t *p = (const uint8_t *)samples;
        uint16_t one = 1;
        if (*(const uint8_t *)&one != 1) {
            size_t i;
            for (i = 0; i < n; i++) {
                uint8_t b[2] = { (uint8_t)samples[i], (uint8_t)(samples[i] >> 8) };
                if (fwrite(b, 1, 2, f) != 2) {
                    fclose(f);
                    return -1;
                }
            }
        } else if (fwrite(p, 1, (size_t)data, f) != (size_t)data) {
            fclose(f);
            return -1;
        }
    }
    return fclose(f) == 0 ? 0 : -1;
}
