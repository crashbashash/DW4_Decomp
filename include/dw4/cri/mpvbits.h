#ifndef DW4_CRI_MPVBITS_H
#define DW4_CRI_MPVBITS_H

/* Big-endian bit reader over a byte stream, expanded in place by the MPEG header parsers: the two words
 * `cur` (bits being consumed, consumed bits shifted out) and `nxt`, the bit position `pos` in cur,
 * and the byte pointer `rp` after nxt. */

#define BITS_LOAD(w, rp) \
    { \
        (w) = *(rp)++; \
        (w) <<= 8; \
        (w) |= (unsigned char)*(rp)++; \
        (w) <<= 8; \
        (w) |= (unsigned char)*(rp)++; \
        (w) <<= 8; \
        (w) |= (unsigned char)*(rp)++; \
    }

/* Opens the reader `skip` bytes into src. */
#define BITS_OPEN(src, skip, cur, nxt, pos, rp) \
    { \
        (rp) = (char *)(((int)(src) + (skip)) & ~3); \
        (pos) = (int)((char *)(src) - (rp)); \
        (pos) += (skip); \
        (pos) *= 8; \
        BITS_LOAD(cur, rp); \
        BITS_LOAD(nxt, rp); \
        (cur) <<= (pos); \
    }

/* Opens the reader on the word-aligned start of src, `skip` bytes in: the first word goes through the
 * refill that every later word does. */
#define BITS_OPEN_REFILL(src, skip, cur, nxt, pos, rp) \
    { \
        (rp) = (char *)((int)(src) & ~3); \
        (pos) = (int)((char *)(src) - (rp)); \
        (rp) += (skip); \
        BITS_LOAD(nxt, rp); \
        (pos) *= 8; \
        (cur) = (pos) != 0 ? (nxt) << (pos) : (nxt); \
        BITS_LOAD(nxt, rp); \
    }

/* Opens the reader on src: cur holds the word containing src, shifted so that src's first bit is bit 31. */
#define BITS_INIT(src, cur, nxt, pos, rp) \
    { \
        (rp) = (char *)((int)(src) & ~3); \
        (pos) = ((char *)(src) - (rp)) << 3; \
        BITS_LOAD(cur, rp); \
        (cur) <<= (pos); \
        BITS_LOAD(nxt, rp); \
    }

#define BITS_SKIP(n, cur, nxt, pos, rp) \
    { \
        (pos) += (n); \
        if ((pos) < 32) { \
            (cur) <<= (n); \
        } else { \
            (pos) -= 32; \
            (cur) = (nxt) << (pos); \
            BITS_LOAD(nxt, rp); \
        } \
    }

/* Skips n bits: the compare is against the remaining bits of cur and the refill keeps cur when pos is 0. */
#define BITS_FLUSH(n, cur, nxt, pos, rp) \
    { \
        if ((pos) < 32 - (n)) { \
            (pos) += (n); \
            (cur) <<= (n); \
        } else { \
            (pos) -= 32 - (n); \
            (cur) = (pos) != 0 ? (nxt) << (pos) : (nxt); \
            BITS_LOAD(nxt, rp); \
        } \
    }

#define BITS_GET(dst, n, cur, nxt, pos, rp) \
    { \
        if ((pos) >= 32 - (n)) { \
            (pos) -= 32 - (n); \
            if ((pos) != 0) { \
                (cur) |= (nxt) >> ((n) - (pos)); \
                (dst) = (cur) >> (32 - (n)); \
                (cur) = (nxt) << (pos); \
            } else { \
                (dst) = (cur) >> (32 - (n)); \
                (cur) = (nxt); \
            } \
            BITS_LOAD(nxt, rp); \
        } else { \
            (dst) = (cur) >> (32 - (n)); \
            (cur) <<= (n); \
            (pos) += (n); \
        } \
    }

#define BITS_GET1(dst, cur, nxt, pos, rp) \
    { \
        (dst) = (cur) >> 31; \
        if ((pos) == 31) { \
            (cur) = (nxt); \
            (pos) = 0; \
            BITS_LOAD(nxt, rp); \
        } else { \
            (pos) += 1; \
            (cur) <<= 1; \
        } \
    }

#define BITS_GET2(dst, cur, nxt, pos, rp) \
    { \
        if ((pos) >= 30) { \
            (pos) -= 30; \
            if ((pos) != 0) { \
                (cur) |= (nxt) >> 1; \
                (dst) = (cur) >> 30; \
                (cur) = (nxt) << 1; \
            } else { \
                (dst) = (cur) >> 30; \
                (cur) = (nxt); \
            } \
            BITS_LOAD(nxt, rp); \
        } else { \
            (dst) = (cur) >> 30; \
            (cur) <<= 2; \
            (pos) += 2; \
        } \
    }

#define BITS_GET32(dst, cur, nxt, pos, rp) \
    { \
        if ((pos) != 0) { \
            (dst) = (cur) | ((nxt) >> (32 - (pos))); \
            (cur) = (nxt) << (pos); \
        } else { \
            (dst) = (cur); \
            (cur) = (nxt); \
        } \
        BITS_LOAD(nxt, rp); \
    }

/* The next n bits without consuming them. */
#define BITS_PEEK(dst, n, cur, nxt, pos) \
    { \
        (dst) = (cur) >> (32 - (n)); \
        if ((pos) > 32 - (n)) { \
            (dst) |= (nxt) >> (64 - (n) - (pos)); \
        } \
    }

#undef BITS_SKIP
#define BITS_SKIP(n, cur, nxt, pos, rp) \
    { \
        (pos) += (n); \
        if ((pos) >= 32) { \
            (pos) -= 32; \
            (cur) = (nxt) << (pos); \
            BITS_LOAD(nxt, rp); \
        } else { \
            (cur) <<= (n); \
        } \
    }
#undef BITS_PEEK
#define BITS_PEEK(dst, n, cur, nxt, pos) \
    do { \
        (dst) = (cur) >> (32 - (n)); \
        if ((pos) > 32 - (n)) { \
            (dst) |= (nxt) >> (64 - (n) - (pos)); \
        } \
    } while (0)
#undef BITS_GET
#define BITS_GET(dst, n, cur, nxt, pos, rp) \
    { \
        if ((pos) >= 32 - (n)) { \
            (pos) -= 32 - (n); \
            if ((pos) != 0) { \
                (cur) |= (nxt) >> ((n) - (pos)); \
                (dst) = (cur) >> (32 - (n)); \
                (cur) = (nxt) << (pos); \
            } else { \
                (dst) = (cur) >> (32 - (n)); \
                (cur) = (nxt); \
            } \
            BITS_LOAD(nxt, rp); \
        } else { \
            (dst) = (cur) >> (32 - (n)); \
            (pos) += (n); \
            (cur) <<= (n); \
        } \
    }

#endif
