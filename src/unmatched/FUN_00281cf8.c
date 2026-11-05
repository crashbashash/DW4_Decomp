/* 0x00281cf8 — FUN_00281cf8 (132 bytes). Polls a channel: a pending error word is consumed and returned (-256 reported as 3); otherwise the state word gives 1 (busy) or 2 (done, consumed), else 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */

/* Context reached through DAT_004bb114 (only the members used here). */
struct Ctx00281cf8 {
    char pad0[2844];
    int state[32];   /* +2844: 1 busy, 2 done */
    char pad2972[3100 - 2972];
    int error[32];   /* +3100: non-zero = pending result */
};

extern struct Ctx00281cf8 *DAT_004bb114;

int FUN_00281cf8(unsigned int channel) {
    int result = 0;
    int error;

    if (channel >= 32) {
        return -1;
    }
    error = DAT_004bb114->error[channel];
    if (error != 0) {
        DAT_004bb114->error[channel] = 0;
        result = (error != -256) ? error : 3;
    } else if (DAT_004bb114->state[channel] == 1) {
        result = 1;
    } else if (DAT_004bb114->state[channel] == 2) {
        DAT_004bb114->state[channel] = 0;
        result = 2;
    }
    return result;
}
