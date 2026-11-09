typedef struct EnbayaDeltaReader {
    signed char *codes;
    signed char *nibbles;
    signed char *bytes;
    short *shorts;
    int *words;
    signed char shift;
    signed char nibbleShift;
} EnbayaDeltaReader;
typedef struct EnbayaDeltaKey { char _pad0[64]; float values[7]; unsigned char mask; char _pad93[3]; } EnbayaDeltaKey;
typedef struct EnbayaDeltaTrack { char _pad0[16]; EnbayaDeltaKey *keys; } EnbayaDeltaTrack;
extern int DAT_004bb0c0[4];
extern int DAT_004bb0d0[2];
extern int DAT_004f2740[4];
extern int DAT_004f2750[16];
static inline int readDeltaBackward(EnbayaDeltaReader *r) {
    signed char code;
    int value;
    r->shift--;
    if (r->shift == -1) {
        r->shift = 3;
        r->codes--;
    }
    code = (*r->codes >> DAT_004bb0c0[r->shift]) & 3;
    if (code != 2) {
        return DAT_004f2740[code];
    }
    r->nibbleShift--;
    if (r->nibbleShift == -1) {
        r->nibbleShift = 1;
        r->nibbles--;
    }
    code = (*r->nibbles >> DAT_004bb0d0[r->nibbleShift]) & 15;
    if (code != 0) {
        return DAT_004f2750[code];
    }
    r->bytes--;
    value = *r->bytes;
    if (value != 0) {
        if (value > 0 && value < 9) {
            return value + 127;
        }
        if (value > -9 && value < 0) {
            return value - 128;
        }
        return (signed char)value;
    }
    r->shorts--;
    value = *r->shorts;
    if (value != 0) {
        return value;
    }
    r->words--;
    value = *r->words;
    return value;
}
void FUN_0027fe90(EnbayaDeltaTrack *track, int count, EnbayaDeltaReader *reader) {
    int i;
    int j;
    for (i = count - 1; i > 0; i--) {
        if (track->keys[i].mask) {
            for (j = 6; j >= 0; j--) {
                if ((1 << j) & track->keys[i].mask) {
                    track->keys[i].values[j] -= readDeltaBackward(reader);
                }
            }
        }
    }
}
