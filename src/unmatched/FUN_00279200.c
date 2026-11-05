/* 0x00279200 — FUN_00279200 (24 bytes). Forwards its second argument to FUN_002607e8 (the ADX error
   reporter); the first is ignored. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void FUN_002607e8(const char *message);

void FUN_00279200(int unused, const char *message) {
    FUN_002607e8(message);
}
