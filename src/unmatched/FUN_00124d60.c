/* Runs the registered exit handlers newest first, then the reent cleanup hook, then terminates
 * through thunk_FUN_001145c8 (newlib exit shape; name is a hypothesis). */
typedef struct ExitHandlerBlock {
    struct ExitHandlerBlock *next;
    int count;
    void (*handlers[32])(void);
} ExitHandlerBlock;

typedef struct Reent {
    char f0[60];
    void (*cleanup)(struct Reent *);
    char f64[264];
    ExitHandlerBlock *exitHandlers;
} Reent;

void thunk_FUN_001145c8(int code);
extern Reent *DAT_004854a0;

void FUN_00124d60(int code) {
    ExitHandlerBlock *block;
    int index;

    for (block = DAT_004854a0->exitHandlers; block; block = block->next) {
        for (index = block->count; --index >= 0;) {
            (*block->handlers[index])();
        }
    }
    if (DAT_004854a0->cleanup) {
        (*DAT_004854a0->cleanup)(DAT_004854a0);
    }
    thunk_FUN_001145c8(code);
}
