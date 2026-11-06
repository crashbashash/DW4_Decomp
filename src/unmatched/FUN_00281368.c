/* Sends request 0xA00|channel (no data) through FUN_00281a00 and marks the channel on when it
 * succeeds. */
int FUN_00281a00();

/* Context reached through DAT_004bb114 (only the members used here). */
struct Ctx00281300 {
    char pad0[128];
    char channelOn[32]; /* +128: per-channel flag, set/cleared once the request succeeds */
};

extern struct Ctx00281300 *DAT_004bb114;

int FUN_00281368(unsigned int channel) {
    int result;

    if (channel >= 32) {
        return -1;
    }
    result = FUN_00281a00(channel | 0xA00, 0, 0, 4);
    if (result == 0) {
        DAT_004bb114->channelOn[channel] = 1;
    }
    return result;
}
