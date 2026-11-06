/* Sends request 0x800|channel with one word of data through FUN_00281a00 and marks the channel on
 * when it succeeds. */
int FUN_00281a00();

/* Context reached through DAT_004bb114 (only the members used here). */
struct Ctx00281300 {
    char pad0[128];
    char channelOn[32]; /* +128: per-channel flag, set/cleared once the request succeeds */
};

extern struct Ctx00281300 *DAT_004bb114;

int FUN_00281300(unsigned int channel, int value) {
    int request[1];
    int result;

    if (channel >= 32) {
        return -1;
    }
    request[0] = value;
    result = FUN_00281a00(channel | 0x800, request, 1, 4);
    if (result == 0) {
        DAT_004bb114->channelOn[channel] = 1;
    }
    return result;
}
