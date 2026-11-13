void *SetVTLBRefillHandler(int cause, void *handler);
void *SetVCommonHandler(int cause, void *handler);
void _debugHandlerEntry(void);
extern void *debugHandlerTable[];

#define EXC_FIRST 1
#define EXC_TLB_COUNT 3
#define EXC_COUNT 13

/* Route EE exception `cause` to `handler` through the common debug entry; returns the handler it replaces. */
void *SetDebugHandler(int cause, void *handler)
{
    void *old;
    if ((unsigned int)(cause - EXC_FIRST) >= EXC_COUNT) {
        return (void *)0xffffffff;
    }
    old = debugHandlerTable[cause];
    debugHandlerTable[cause] = handler;
    if ((unsigned int)(cause - EXC_FIRST) < EXC_TLB_COUNT) {
        SetVTLBRefillHandler(cause, _debugHandlerEntry);
    } else {
        SetVCommonHandler(cause, _debugHandlerEntry);
    }
    return old;
}
