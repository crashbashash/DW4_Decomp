/* Sends request 0x700|channel (no data) through FUN_00281a00 and marks the channel off when it
 * succeeds. */
int FUN_00281a00();

/* Context reached through DAT_004bb114 (only the members used here). */
struct Ctx00281300 {
    char pad0[128];
    char channelOn[32]; /* +128: per-channel flag, set/cleared once the request succeeds */
};

extern struct Ctx00281300 *DAT_004bb114;

int FUN_002813c8(unsigned int channel) {
    int result;

    if (channel >= 32) {
        return -1;
    }
    result = FUN_00281a00(channel | 0x700, 0, 0, 4);
    if (result == 0) {
        DAT_004bb114->channelOn[channel] = 0;
    }
    return result;
}
