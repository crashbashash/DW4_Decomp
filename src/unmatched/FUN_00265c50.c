/* 0x00265c50 — FUN_00265c50 (56 bytes). Calls FUN_0027a8b0(handle, 0), FUN_0027a818(handle, 0) and FUN_0027a688(handle). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_0027a8b0(void *handle, int value);
void FUN_0027a818(void *handle, int value);
void FUN_0027a688(void *handle);

void FUN_00265c50(void *handle) {
    FUN_0027a8b0(handle, 0);
    FUN_0027a818(handle, 0);
    FUN_0027a688(handle);
}
