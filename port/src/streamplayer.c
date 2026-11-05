#include "dw4/streamplayer.h"

void dw4_stream_decide(int type, int memory_idx, int slot_state, int fade_running, int start_ok, int skip_pause, int volume, int base,
                       int64_t request, dw4_stream_decision *out)
{
    int n = 0;
    out->seq = 0;
    out->level = 0;
    out->clear_skip = 0;
    out->ops[0] = DW4_STREAM_NONE;
    if (memory_idx != -1) return;               /* only ADX files are handled here */
    if (type != 1 && type != 2) return;         /* types 3 and 4 (and anything else) are not stream requests */
    out->ops[n++] = DW4_STREAM_CHECK;
    if (slot_state == 1) {
        if (!fade_running) out->ops[n++] = DW4_STREAM_FADE;
        out->ops[n] = DW4_STREAM_NONE;
        return;
    }
    out->ops[n++] = DW4_STREAM_PAUSE;
    out->ops[n++] = DW4_STREAM_LEVEL;
    out->level = volume + base;
    out->ops[n++] = DW4_STREAM_START;
    if (start_ok) {
        if (skip_pause) out->clear_skip = 1;
        else out->ops[n++] = DW4_STREAM_UNPAUSE;
        out->seq = request + 1;
        out->ops[n++] = DW4_STREAM_NAME;
    }
    out->ops[n] = DW4_STREAM_NONE;
}
