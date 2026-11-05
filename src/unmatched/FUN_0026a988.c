/* 0x0026a988 — FUN_0026a988 (44 bytes). Stores FUN_0026a160(object) in *out and returns 1. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_0026a160(void *object);

int FUN_0026a988(void *object, int *out) {
    *out = FUN_0026a160(object);
    return 1;
}
