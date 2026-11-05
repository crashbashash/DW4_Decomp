/* 0x002929a0 — FUN_002929a0 (332 bytes). Programs the handle's target (+64) with a fixed parameter set through FUN_002ad950, including rate*scale*1000 rounded to nearest for parameters 45, 44 and 42, then finishes with FUN_002a3200(target, 5, 0). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_002ad950(int target, int param, int value);
void FUN_002a3200(int target, int a, int b);

struct Handle002929a0 {
    char pad0[64];
    int target; /* +64 */
};

void FUN_002929a0(struct Handle002929a0 *handle, int unused, int rate, int scale) {
    int target = handle->target;
    int nearest = 1; /* first the step-down flag, then the rounded value */
    float exact;
    int rounded;

    FUN_002ad950(target, 8, 0);
    FUN_002ad950(target, 1, 1);
    FUN_002ad950(target, 0, 0);
    FUN_002ad950(target, 23, 4);
    /* floor(x + 0.5): truncate, then step down when truncation went up */
    exact = (float)(rate * scale * 1000) + 0.5f;
    rounded = (int)exact;
    if (!(exact < (float)rounded)) {
        nearest = 0;
    }
    nearest = rounded - nearest; /* matching construct: manual — one variable for flag and result (retail reuses its register) */
    FUN_002ad950(target, 45, nearest);
    FUN_002ad950(target, 44, nearest);
    FUN_002ad950(target, 42, nearest);
    FUN_002ad950(target, 15, 2);
    FUN_002ad950(target, 51, 0);
    FUN_002ad950(target, 14, 0);
    FUN_002ad950(target, 28, 0);
    FUN_002a3200(target, 5, 0);
}
