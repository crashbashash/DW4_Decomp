#include "dw4/cri/mpv.h"
#include "dw4/cri/mpvbits.h"

extern short mpvsc_mbaddr_incr_vlc[]; /* macroblock_address_increment codes: (length | code << 8) per increment */

int MPV_CheckDelim(const unsigned char *p) {
    unsigned int code = p[0];
    int type;
    code <<= 8;
    code |= p[1];
    code <<= 8;
    code |= p[2];
    code <<= 8;
    code |= p[3];
    if (code == 0x100) {
        type = 4;
    } else if (code == 0x101) {
        type = 3;
    } else if (code - 0x102 < 0xAE) {
        type = 1;
    } else if (code == 0x1B2) {
        type = 32;
    } else if (code == 0x1B3) {
        type = 64;
    } else if (code == 0x1B5) {
        type = 16;
    } else if (code == 0x1B7) {
        type = 128;
    } else if (code == 0x1B8) {
        type = 8;
    } else {
        type = 0;
    }
    return type;
}

char *MPV_BsearchDelim(char *end, int len, int mask)
{
    char c;
    unsigned int state = 0;
    char *p = end;
    char *start = end - len;
    while (start < p) {
        p--;
        c = *p;
        switch (state) {
        case 0:
            state = 1;
            break;
        case 1:
            if (c == 1)
                state = 2;
            break;
        case 2:
            if (c == 0)
                state = 3;
            else if (c != 1)
                state = 1;
            break;
        case 3:
            if (c == 0) {
                if (mask & MPV_CheckDelim((const unsigned char *)p))
                    return p;
                state = 0;
            } else
                state = c != 1 ? 1 : 2;
            break;
        }
    }
    return 0;
}

char *MPV_SearchDelim(char *buf, int len, int mask)
{
    char *p = buf;
    char *end = buf + len;
    unsigned int state = 0;
    char c;
    char *hit;
    while (p < end) {
        c = *p++;
        switch (state) {
        case 0:
            if (c == 0)
                state = 1;
            break;
        case 1:
            state = c != 0 ? 0 : 2;
            break;
        case 2:
            if (c == 1)
                state = 3;
            else if (c != 0)
                state = 0;
            break;
        case 3:
            hit = p - 4;
            if (mask & MPV_CheckDelim((const unsigned char *)hit))
                return hit;
            state = 0;
            break;
        }
    }
    return 0;
}

char *MPV_CopyStm(char *dst, char *src, int len, int mask)
{
    char *p = src;
    char *end = src + len;
    unsigned int state = 0;
    char c;
    while (p < end) {
        c = *p++;
        *dst++ = c;
        switch (state) {
        case 0:
            if (c == 0)
                state = 1;
            break;
        case 1:
            state = c != 0 ? 0 : 2;
            break;
        case 2:
            if (c == 1)
                state = 3;
            else if (c != 0)
                state = 0;
            break;
        case 3:
            if (mask & MPV_CheckDelim((const unsigned char *)(p - 4)))
                return p;
            state = 0;
            break;
        }
    }
    return p;
}

/* Whether the B picture whose first slice is at buf (nbyte bytes, nmb macroblocks) codes nothing: one slice
 * whose first and last macroblocks are skipped-style interpolated blocks with no coded data. */
int MPV_IsEmptyBpic(unsigned char *buf, int nbyte, int nmb) {
    int bit;
    char *rp;
    unsigned int cur, nxt;
    int cnt;
    unsigned int val;
    int code;
    int len;
    int pos;
    char *q;

    BITS_INIT(buf, cur, nxt, bit, rp);
    BITS_GET32(val, cur, nxt, bit, rp);
    if (val != 0x101) {
        return 0;
    }
    BITS_GET(val, 5, cur, nxt, bit, rp);
    BITS_GET1(val, cur, nxt, bit, rp);
    if (val != 0) {
        return 0;
    }
    BITS_GET1(val, cur, nxt, bit, rp);
    if (val == 0) {
        return 0;
    }
    BITS_PEEK(val, 6, cur, nxt, bit);
    switch (val) {
    case 0x16:
    case 0x17:
        BITS_SKIP(5, cur, nxt, bit, rp);
        break;
    case 0x0B:
        BITS_SKIP(6, cur, nxt, bit, rp);
        break;
    default:
        return 0;
    }
    cnt = nmb - 1;
    for (;;) {
        BITS_PEEK(val, 11, cur, nxt, bit);
        if (val != 8) {
            break;
        }
        BITS_SKIP(11, cur, nxt, bit, rp);
        cnt -= 33;
        if (cnt <= 33) {
            break;
        }
    }
    if (cnt <= 0 || cnt > 33) {
        return 0;
    }
    code = mpvsc_mbaddr_incr_vlc[cnt];
    len = code & 0xFF;
    BITS_GET(val, len, cur, nxt, bit, rp);
    if (val != code >> 8) {
        return 0;
    }
    BITS_PEEK(val, 6, cur, nxt, bit);
    switch (val) {
    case 0x16:
    case 0x17:
        BITS_SKIP(5, cur, nxt, bit, rp);
        break;
    case 0x0B:
        BITS_SKIP(6, cur, nxt, bit, rp);
        break;
    default:
        return 0;
    }
    q = rp;
    q += (bit + 7) >> 3;
    q -= 8;
    pos = q - (char *)buf;
    if (pos > nbyte) {
        return 0;
    }
    return 1;
}


/* Whether the P picture whose first slice is at buf (nbyte bytes, nmb macroblocks) codes nothing: one slice
 * whose first and last macroblocks are forward-predicted with no coded data and zero vectors, followed within
 * the buffer by a B picture, a sequence end or a closed group. */
int MPV_IsEmptyPpic(unsigned char *buf, int nbyte, int nmb) {
    int bit;
    char *rp;
    unsigned int cur, nxt;
    int cnt;
    unsigned int val;
    int code;
    int len;
    int pos;
    char *q;
    char *p;
    int flg;

    BITS_INIT(buf, cur, nxt, bit, rp);
    BITS_GET32(val, cur, nxt, bit, rp);
    if (val != 0x101) {
        return 0;
    }
    BITS_GET(val, 5, cur, nxt, bit, rp);
    BITS_GET1(val, cur, nxt, bit, rp);
    if (val != 0) {
        return 0;
    }
    BITS_GET1(val, cur, nxt, bit, rp);
    if (val == 0) {
        return 0;
    }
    BITS_PEEK(val, 5, cur, nxt, bit);
    if (val != 7) {
        return 0;
    }
    BITS_SKIP(5, cur, nxt, bit, rp);
    cnt = nmb - 1;
    for (;;) {
        BITS_PEEK(val, 11, cur, nxt, bit);
        if (val != 8) {
            break;
        }
        BITS_SKIP(11, cur, nxt, bit, rp);
        cnt -= 33;
        if (cnt <= 33) {
            break;
        }
    }
    if (cnt <= 0 || cnt > 33) {
        return 0;
    }
    code = mpvsc_mbaddr_incr_vlc[cnt];
    len = code & 0xFF;
    BITS_GET(val, len, cur, nxt, bit, rp);
    if (val != code >> 8) {
        return 0;
    }
    BITS_PEEK(val, 5, cur, nxt, bit);
    if (val != 7) {
        return 0;
    }
    BITS_SKIP(5, cur, nxt, bit, rp);
    q = rp + ((bit + 7) >> 3) - 8;
    pos = q - (char *)buf;
    if (pos > nbyte) {
        return 0;
    }
    for (;;) {
        p = MPV_SearchDelim(q, nbyte - pos, 0xCC);
        if (p == 0) {
            return 0;
        }
        flg = MPV_CheckDelim((unsigned char *)p);
        if (flg & 0x04) {
            if ((((p[5] & 3) << 1) | ((unsigned int)p[6] >> 31)) != 3) {
                return 0;
            }
            q = p + 1;
            pos = p + 1 - (char *)buf;
            continue;
        }
        if (flg & 0x40) {
            q = p + 1;
            pos = p + 1 - (char *)buf;
            continue;
        }
        if (flg & 0x80) {
            pos = p + 4 - (char *)buf;
            if (pos > nbyte) {
                return 0;
            }
            break;
        }
        if (flg & 0x08) {
            if (p[7] & 0x40) {
                pos = p + 7 - (char *)buf;
                if (pos > nbyte) {
                    return 0;
                }
                break;
            }
            return 0;
        }
        return 0;
    }
    return 1;
}
