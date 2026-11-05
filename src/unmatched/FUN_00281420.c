/* 0x00281420 — FUN_00281420 (176 bytes). For a channel whose two table entries are set and which is not on, returns its start (base + sum of the earlier channels' first entries) and 0x20000 + the sum of their second entries. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */

/* Context reached through DAT_004bb114 (only the members used here). */
struct Ctx00281420 {
    char pad0[128];
    unsigned char channelOn[32]; /* +128 */
    int base;             /* +160 */
    char pad164[5028 - 164];
    int first[32];        /* +5028: per-channel table (see FUN_00280f60) */
    int second[32];       /* +5156 */
};

extern struct Ctx00281420 *DAT_004bb114;

int FUN_00281420(unsigned int channel, int *start, int *size) {
    int result = 0;
    int firstSum = 0;
    int secondSum = 0;
    unsigned int i;

    if (channel >= 32) {
        return -1;
    }
    if (DAT_004bb114->first[channel] != 0 && DAT_004bb114->second[channel] != 0) {
        if (DAT_004bb114->channelOn[channel] == 0) {
            for (i = 0; i < channel; i++) {
                firstSum += DAT_004bb114->first[i];
                secondSum += DAT_004bb114->second[i];
            }
            *start = DAT_004bb114->base + firstSum;
            *size = secondSum + 0x20000;
        } else {
            result = -3;
        }
    } else {
        result = -2;
    }
    return result;
}
