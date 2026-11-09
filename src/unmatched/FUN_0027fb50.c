typedef struct EnbayaReader {
    signed char *codes;
    signed char *bytes;
    short *shorts;
    int *words;
    signed char shift;
} EnbayaReader;
typedef struct EnbayaKey { char _pad0[64]; float values[7]; char _pad92[4]; } EnbayaKey;
typedef struct EnbayaTrack { char _pad0[16]; EnbayaKey *keys; } EnbayaTrack;
extern int DAT_004bb0e0[4];
static inline int readValue(EnbayaReader *r) {
    signed char code;
    int value;

    if (r->shift == 4) {
        r->shift = 0;
        r->codes++;
    }
    /* matching construct: template sweep — zero code kept as its own branch before the switch */
    code = (*r->codes >> DAT_004bb0e0[r->shift]) & 3;
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
void FUN_0027fb50(EnbayaTrack *track, int count, EnbayaReader *reader) {
    int i;
    int j;
    for (i = 0; i < count; i++) {
        for (j = 0; j < 7; j++) {
            track->keys[i].values[j] = readValue(reader);
        }
    }
}
