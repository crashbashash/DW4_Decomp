/* Read one GS/frame statistic as a per-frame rate. FUN_001f6f50 snapshots ~50 GS-side counters
 * into a 464-byte block of 58 long long The game keeps the current block at 0x560d20 and the block
 * taken at the last reset at 0x560b50 (0x1d0 apart, which is the block size). The function turns
 * `id` into a number: - elapsed = current[5] - previous[5] (frame-length counter); nothing is
 * computed when it is not positive, - most ids return (current[k] - previous[k]) / elapsed, some
 * scaled to milliseconds (x 1000 / 9216000 ticks per second) or by 16, - ids 44..56 return a
 * small-integer query FUN_00204840(n), - ids 58, 59, 16, 17, 20, 24 consume a free-running
 * accumulator and clear it, - ids 60..186 consume the per-id event counters at 0x5607d0 (unsigned)
 * and clear them, - ids 42 and 43 take a fresh snapshot and return one raw field of it. The result
 * is -1.0f for an unknown id. The meaning of each counter slot is not established, so slots are
 * addressed by index. */
typedef struct GsStatBlock { long long c[58]; } GsStatBlock;

extern GsStatBlock g_gsStatCurrent;
extern GsStatBlock g_gsStatPrevious;
extern unsigned int g_gsEventCount[];
extern long long g_gsAccumulator_005608a0[4];
extern long long g_gsAccumulator_00560660[4];
extern long long g_gsAccumulator_00560668[4];
extern long long g_gsRawCounter[4];
int FUN_001f6f50(GsStatBlock *out);
int FUN_00204840(int index);

#define CUR g_gsStatCurrent.c
#define PREV g_gsStatPrevious.c
#define DELTA(k) ((float)(CUR[k] - PREV[k]))
#define TICKS_PER_SECOND 9216000

float FUN_00177de0(void *unused, int id) {
    float result = -1.0f;
    float elapsed = DELTA(5);
    if (!(elapsed <= 0.0f)) {
        switch (id) {
        case 4: result = elapsed; break;
        case 5: result = DELTA(6); break;
        case 0: result = DELTA(0) / elapsed; break;
        case 1: result = DELTA(1) / elapsed; break;
        case 6: result = (1000.0f * (DELTA(36) / (float)TICKS_PER_SECOND)) / elapsed; break;
        case 7: result = 1000.0f * ((float)CUR[37] / (float)TICKS_PER_SECOND); break;
        case 8: result = 1000.0f * ((float)CUR[38] / (float)TICKS_PER_SECOND); break;
        case 2: result = DELTA(2) / elapsed; break;
        case 36: result = DELTA(26) / elapsed; break;
        case 37: result = DELTA(25) / elapsed; break;
        case 3: result = (float)g_gsRawCounter[0]; break;
        case 30: result = (1000.0f * (DELTA(30) / (float)TICKS_PER_SECOND)) / elapsed; break;
        case 31: result = (16.0f * DELTA(29)) / elapsed; break;
        case 32: result = DELTA(27) / elapsed; break;
        case 33: result = (1000.0f * (DELTA(34) / (float)TICKS_PER_SECOND)) / elapsed; break;
        case 34: result = (16.0f * DELTA(33)) / elapsed; break;
        case 35: result = DELTA(31) / elapsed; break;
        case 39: result = 1000.0f * ((DELTA(43) / elapsed) / (float)TICKS_PER_SECOND); break;
        case 38: {
            float sum = DELTA(39) / elapsed;
            sum = sum + DELTA(40) / elapsed;
            sum = sum + DELTA(41) / elapsed;
            sum = sum + DELTA(42) / elapsed;
            sum = sum + DELTA(44) / elapsed;
            sum = sum + DELTA(45) / elapsed;
            sum = sum + DELTA(46) / elapsed;
            result = 1000.0f * (sum / (float)TICKS_PER_SECOND);
            break;
        }
        case 40: result = DELTA(24) / elapsed; break;
        case 41: result = DELTA(7) / elapsed; break;
        case 44: result = (float)FUN_00204840(3); break;
        case 45: result = (float)FUN_00204840(7); break;
        case 46: result = (float)FUN_00204840(8); break;
        case 47: result = (float)FUN_00204840(9); break;
        case 48: result = (float)FUN_00204840(10); break;
        case 49: result = (float)FUN_00204840(0); break;
        case 50: result = (float)FUN_00204840(1); break;
        case 51: result = (float)FUN_00204840(2); break;
        case 52: result = (float)FUN_00204840(4); break;
        case 53: result = (float)FUN_00204840(5); break;
        case 54: result = (float)FUN_00204840(6); break;
        case 55: result = (float)FUN_00204840(11); break;
        case 56: result = (float)FUN_00204840(12); break;
        case 58: result = (float)g_gsAccumulator_00560668[0] / elapsed; g_gsAccumulator_00560668[0] = 0; break;
        case 59: result = (float)g_gsAccumulator_00560660[0] / elapsed; g_gsAccumulator_00560660[0] = 0; break;
        case 16: result = (float)g_gsAccumulator_005608a0[0] / elapsed; g_gsAccumulator_005608a0[0] = 0; break;
        case 17: result = (float)g_gsAccumulator_005608a0[0] / elapsed; g_gsAccumulator_005608a0[0] = 0; break;
        case 20: result = (float)g_gsAccumulator_005608a0[0] / elapsed; g_gsAccumulator_005608a0[0] = 0; break;
        case 24: result = (float)g_gsAccumulator_005608a0[0] / elapsed; g_gsAccumulator_005608a0[0] = 0; break;
        case 187: result = DELTA(48) / elapsed; break;
        case 188: result = DELTA(49) / elapsed; break;
        case 190: result = DELTA(56) / elapsed; break;
        }
        if (id >= 60 && id < 187) {
            result = (float)g_gsEventCount[id] / elapsed;
            g_gsEventCount[id] = 0;
        }
    }
    if (result == -1.0f) {
        if (id == 42) {
            GsStatBlock snapshot;
            FUN_001f6f50(&snapshot);
            result = (float)snapshot.c[3];
        } else if (id == 43) {
            GsStatBlock snapshot;
            FUN_001f6f50(&snapshot);
            result = (float)snapshot.c[4];
        }
    }
    return result;
}
