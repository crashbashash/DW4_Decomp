/* 0x0029d0e0 — FUN_0029d0e0 (84 bytes). When option 6 is set, calls the attached interface's optional slot +20. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SfdInterface {
    void (*f0)(void);
    void (*f4)(void);
    void (*f8)(void);
    void (*f12)(void);
    void (*f16)(void);
    void (*f20)(void *handle, int a);  /* +20 */
} SfdInterface;

typedef struct SfdHandle {
    char pad0[8460];
    SfdInterface *iface;    /* +8460 */
} SfdHandle;

extern int FUN_002adc40(SfdHandle *handle, int option);

void FUN_0029d0e0(SfdHandle *handle, int a) {
    void (*fn)(void *, int);

    if (FUN_002adc40(handle, 6) != 0) {
        fn = handle->iface->f20;
        if (fn != 0) {
            fn(handle, a);
        }
    }
}
