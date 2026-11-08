typedef struct Mpeg2User {
    char pad0[48];
    int start_code;     /* +48 */
    char pad52[724];
    int ext_state;      /* +776 */
    int expected_ext_id; /* +780 */
    char pad784[392];
    int call_count;     /* +1176 */
    char pad1180[92];
    int error_count;    /* +1272 */
} Mpeg2User;
typedef struct Mpeg2UserCtx { char pad0[352]; Mpeg2User user; } Mpeg2UserCtx;

void FUN_00286b70();

#define READ_WORD(w) \
    { \
        (w) = *p++; \
        (w) <<= 8; (w) |= *p++ & 255; \
        (w) <<= 8; (w) |= *p++ & 255; \
        (w) <<= 8; (w) |= *p++ & 255; \
    }

char *FUN_00286958(Mpeg2UserCtx *ctx, char *buf)
{
    Mpeg2User *h = &ctx->user;
    char *p;
    int cnt;
    unsigned int acc, nxt, v;
    int n;

    h->call_count++;
    if ((h->ext_state != 0 && h->ext_state != 32) || h->expected_ext_id != 0) {
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
    for (n = 0; n <= 0xFFFFF; n++) {
        v = acc >> 8;
        acc <<= 8;
        if (cnt > 8) {
            v |= nxt >> (40 - cnt);
        }
        if (v == 1) break;
        cnt += 8;
        if (cnt >= 32) {
            cnt -= 32;
            acc = nxt << cnt;
            READ_WORD(nxt);
        }
    }
    FUN_00286b70(ctx, buf, n + 4);
    return buf + ((cnt + (p - buf) * 8 - 57) / 8);
}
