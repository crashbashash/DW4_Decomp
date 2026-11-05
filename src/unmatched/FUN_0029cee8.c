/* 0x0029cee8 — FUN_0029cee8 (144 bytes). Validates the handle, then calls the attached interface's slot +4 when option 6 is set. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SfdInterface {
    void (*f0)(void);
    void (*f4)(void *handle, int a, int b);  /* +4 */
} SfdInterface;

typedef struct SfdHandle {
    char pad0[8460];
    SfdInterface *iface;    /* +8460 */
} SfdHandle;

extern int FUN_002a0dd8(SfdHandle *handle);
extern int FUN_002a0bb8(SfdHandle *handle, int code);
extern int FUN_002adc40(SfdHandle *handle, int option);

void FUN_0029cee8(SfdHandle *handle, int a, int b) {
    if (FUN_002a0dd8(handle) != 0) {
        FUN_002a0bb8(0, 0xFF0001A1);
        return;
    }
    if (FUN_002adc40(handle, 6) != 0) {
        handle->iface->f4(handle, a, b);
    }
}
