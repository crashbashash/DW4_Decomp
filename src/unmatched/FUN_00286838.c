typedef struct Mpeg2Seq {
    char pad0[44];
    int start_code;     /* +44 */
    char pad48[728];
    int ext_state;      /* +776 */
    int expected_ext_id; /* +780 */
    char pad784[372];
    int header_level;   /* +1156 */
    char pad1160[12];
    int call_count;     /* +1172 */
    char pad1176[96];
    int error_count;    /* +1272 */
} Mpeg2Seq;
typedef struct Mpeg2SeqCtx { char pad0[352]; Mpeg2Seq seq; } Mpeg2SeqCtx;

#define READ_WORD(w) \
    { \
        (w) = *p++; \
        (w) <<= 8; (w) |= *p++ & 255; \
        (w) <<= 8; (w) |= *p++ & 255; \
        (w) <<= 8; (w) |= *p++ & 255; \
    }

char *FUN_00286838(Mpeg2SeqCtx *ctx, char *buf)
{
    Mpeg2Seq *h = &ctx->seq;
    char *p;
    int cnt;
    unsigned int acc, nxt;

    h->header_level = 1;
    h->call_count++;
    if ((h->ext_state != 0 && h->ext_state != 128) || h->expected_ext_id != 0) {
        h->error_count++;
    }
    p = (char *)((unsigned int)buf & ~3);
    cnt = (buf - p) << 3;
    READ_WORD(acc);
    READ_WORD(nxt);
    acc <<= cnt;
    if (cnt != 0) {
        h->start_code = acc | (nxt >> (32 - cnt));
        acc = nxt << cnt;
    } else {
        h->start_code = acc;
        acc = nxt;
    }
    READ_WORD(nxt);
    h->ext_state = 0;
    h->expected_ext_id = 0;
    return buf + ((cnt + (p - buf) * 8 - 57) / 8);
}
