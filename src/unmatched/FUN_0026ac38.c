/* 0x0026ac38 — FUN_0026ac38 (24 bytes). Ignores its first argument and passes the second, a message, to FUN_002607e8. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_002607e8(const char *message);

void FUN_0026ac38(void *unused, const char *message) {
    FUN_002607e8(message);
}
