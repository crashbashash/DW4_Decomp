/* 0x0027e860 — FUN_0027e860 (60 bytes). Invokes the callback registered for an event id in the table at
   0x00570b60 (function, context pairs), if any, with its context. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Callback27e {
    void (*function)(int context);
    int context;
};

extern struct Callback27e DAT_00570b60[];

void FUN_0027e860(int id) {
    if (DAT_00570b60[id].function != 0) {
        DAT_00570b60[id].function(DAT_00570b60[id].context);
    }
}
