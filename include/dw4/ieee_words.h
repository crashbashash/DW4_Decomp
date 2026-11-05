/* ieee_words.h -- access to the two 32-bit halves of a double, as fdlibm's EXTRACT_WORDS /
 * INSERT_WORDS do. The EE passes a double in one 64-bit register, so the halves are read and
 * written with register shifts rather than through memory. */
#ifndef IEEE_WORDS_H
#define IEEE_WORDS_H
typedef union {
    double value;
    struct {
        unsigned lo;
        int hi;
    } parts;
} IeeeDoubleWords;

#define EXTRACT_WORDS(ix0, ix1, d) \
    do { \
        IeeeDoubleWords ew_u; \
        ew_u.value = (d); \
        (ix0) = ew_u.parts.hi; \
        (ix1) = ew_u.parts.lo; \
    } while (0)

#define INSERT_WORDS(d, ix0, ix1) \
    do { \
        IeeeDoubleWords iw_u; \
        iw_u.parts.hi = (ix0); \
        iw_u.parts.lo = (ix1); \
        (d) = iw_u.value; \
    } while (0)

#define GET_HIGH_WORD(i, d) \
    do { \
        IeeeDoubleWords gh_u; \
        gh_u.value = (d); \
        (i) = gh_u.parts.hi; \
    } while (0)

#define GET_LOW_WORD(i, d) \
    do { \
        IeeeDoubleWords gl_u; \
        gl_u.value = (d); \
        (i) = gl_u.parts.lo; \
    } while (0)

#define SET_HIGH_WORD(d, v) \
    do { \
        IeeeDoubleWords sh_u; \
        sh_u.value = (d); \
        sh_u.parts.hi = (v); \
        (d) = sh_u.value; \
    } while (0)

#define SET_LOW_WORD(d, v) \
    do { \
        IeeeDoubleWords sl_u; \
        sl_u.value = (d); \
        sl_u.parts.lo = (v); \
        (d) = sl_u.value; \
    } while (0)

/* single-precision counterpart: the float lives in an FPR and is moved to a GPR with mfc1 */
typedef union {
    float value;
    unsigned int word;
} IeeeFloatWord;

#define GET_FLOAT_WORD(i, d) \
    do { \
        IeeeFloatWord gf_u; \
        gf_u.value = (d); \
        (i) = gf_u.word; \
    } while (0)

#define SET_FLOAT_WORD(d, i) \
    do { \
        IeeeFloatWord sf_u; \
        sf_u.word = (i); \
        (d) = sf_u.value; \
    } while (0)
#endif
