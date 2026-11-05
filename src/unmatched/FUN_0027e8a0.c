/* 0x0027e8a0 — FUN_0027e8a0 (64 bytes). Registers a callback and its context in the pair at 0x00570bb0 inside
   the FUN_0027e1c0 / FUN_0027e1d8 critical section. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Callback27e {
    void *function;
    void *context;
};

extern void FUN_0027e1c0(void);
extern void FUN_0027e1d8(void);
extern struct Callback27e DAT_00570bb0;

void FUN_0027e8a0(void *function, void *context) {
    FUN_0027e1c0();
    DAT_00570bb0.function = function;
    DAT_00570bb0.context = context;
    FUN_0027e1d8();
}
