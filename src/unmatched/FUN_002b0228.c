/* 0x002b0228 — FUN_002b0228 (60 bytes). Links 0x44-byte entry `from` (output slot `slot`, words at +7996) to 0x74-byte entry `to`, and records `from` at +4948 of entry74[to]. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */

/* Views of the two entry tables as indexed from ctx (see FUN_002b0268, FUN_002ad828). */
struct Entry44 {
    char pad[7996];
    int outputs[3];                       /* +20 within the entry at ctx+7976 */
};

struct Entry74 {
    char pad[4948];
    int from;                             /* +4948: the Entry44 feeding this entry */
};

void FUN_002b0228(char *ctx, int from, int slot, int to) {
    int off44 = from * 0x44;

    ((struct Entry44 *)(ctx + off44))->outputs[slot] = to;
    /* matching construct: manual — advancing ctx in place reproduces retail's register reuse */
    ctx += to * 0x74;
    ((struct Entry74 *)ctx)->from = from;
}
