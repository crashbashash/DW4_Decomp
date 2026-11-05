/* 0x0026d7a0 — FUN_0026d7a0 (32 bytes). Calls FUN_0026d6e8 with its handle and name, 0 and 0xFFFFF. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_0026d6e8(void *handle, const char *name, int f188, int f192);

void FUN_0026d7a0(void *handle, const char *name) {
    FUN_0026d6e8(handle, name, 0, 0xFFFFF);
}
