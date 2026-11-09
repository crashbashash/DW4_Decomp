typedef struct EnbayaMaskReader {
    signed char *codes;
    unsigned char *bytes;
    unsigned short *shorts;
    unsigned int *words;
    signed char shift;
} EnbayaMaskReader;
typedef struct EnbayaMaskKey { char _pad0[92]; unsigned char mask; char _pad93[3]; } EnbayaMaskKey;
typedef struct EnbayaMaskRun { int remaining; int consumed; } EnbayaMaskRun;
extern int DAT_004bb0f0[4];
static inline int readRunLength(EnbayaMaskReader *r) {
    signed char code;
    int value;
    if (r->shift == 4) {
        r->shift = 0;
        r->codes++;
    }
    code = (*r->codes >> DAT_004bb0f0[r->shift]) & 3;
    r->shift++;
    if (code == 0) {
        value = code;
    } else {
        switch (code) {
        case 1:
            value = *r->bytes;
            r->bytes++;
            break;
        case 2:
            value = *r->shorts;
            r->shorts++;
            break;
        case 3:
            value = *r->words;
            r->words++;
            break;
        default:
            value = 0;
            break;
        }
    }
    return value;
}
void FUN_00280330(EnbayaMaskRun *run, EnbayaMaskKey *keys, int count, EnbayaMaskReader *reader) {
    int total = count * 7;
    int i = 0;
    while (i < total) {
        if (run->remaining == 0) {
            int key = i / 7;
            switch (i % 7) {
            case 0:
                keys[key].mask ^= 1;
                break;
            case 1:
                keys[key].mask ^= 2;
                break;
            case 2:
                keys[key].mask ^= 4;
                break;
            case 3:
                keys[key].mask ^= 8;
                break;
            case 4:
                keys[key].mask ^= 0x10;
                break;
            case 5:
                keys[key].mask ^= 0x20;
                break;
            case 6:
                keys[key].mask ^= 0x40;
                break;
            case 7:
                break;
            }
            run->remaining = readRunLength(reader);
            i++;
            run->consumed = 0;
        } else {
            int left = total - i;
            int n = run->remaining < left ? run->remaining : left;
            i += n;
            run->remaining -= n;
            run->consumed += n;
        }
    }
}
