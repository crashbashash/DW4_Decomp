/* 0x00330990
 * Stub that stores the engine's failure result code through `result`.  Global
 * 0x4fb418 holds 1 (set in the engine init, finding #504); FUN_0032fba0 stores
 * it when WakeupThread() fails and the sibling 0x4fb410 (0) on success. */
extern int g_igFailureResult_004fb418[4];
void Gap__Core__igPsx2Thread__vfunc_53(int *result) {
    *result = g_igFailureResult_004fb418[0];
}
