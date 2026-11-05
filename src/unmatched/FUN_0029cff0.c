/* 0x0029cff0 — FUN_0029cff0 (124 bytes). Validates the handle, then calls the attached interface's slot +12 when option 6 is set. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SfdInterface {
    void (*f0)(void);
    void (*f4)(void);
    void (*f8)(void);
    void (*f12)(void *handle, int a);  /* +12 */
} SfdInterface;

typedef struct SfdHandle {
    char pad0[8460];
    SfdInterface *iface;    /* +8460 */
} SfdHandle;

extern int FUN_002a0dd8(SfdHandle *handle);
extern int FUN_002a0bb8(SfdHandle *handle, int code);
extern int FUN_002adc40(SfdHandle *handle, int option);

void FUN_0029cff0(SfdHandle *handle, int a) {
    if (FUN_002a0dd8(handle) != 0) {
        FUN_002a0bb8(0, 0xFF0001A3);
        return;
    }
    if (FUN_002adc40(handle, 6) != 0) {
        handle->iface->f12(handle, a);
    }
}
