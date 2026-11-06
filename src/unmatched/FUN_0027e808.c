/* Registers the callback and context for an event id in the table at 0x00570b60 inside the
 * FUN_0027e1c0 / FUN_0027e1d8 critical section. */
struct Callback27e {
    void (*function)(int context);
    int context;
};

extern void FUN_0027e1c0(void);
extern void FUN_0027e1d8(void);
extern struct Callback27e DAT_00570b60[];

void FUN_0027e808(int id, void (*function)(int context), int context) {
    FUN_0027e1c0();
    DAT_00570b60[id].function = function;
    DAT_00570b60[id].context = context;
    FUN_0027e1d8();
}
