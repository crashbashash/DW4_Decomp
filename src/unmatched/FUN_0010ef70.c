typedef void (*PowerOffHandler)(void *data);
typedef struct {
    PowerOffHandler func;
    void *data;
} PowerOffEntry;
extern int DAT_00481efc;
extern PowerOffEntry DAT_00559200;
extern void *DAT_00559240;
void FUN_0010ef30(int command);
void FUN_0010ef60(void);
int FUN_0010f060(void);
int DIntr(void);
int EIntr(void);
PowerOffHandler FUN_0010ef70(PowerOffHandler func, void *data) {
    PowerOffEntry *entry = &DAT_00559200;
    PowerOffHandler old;
    int interrupts;
    FUN_0010ef30(27);
    if (DAT_00481efc == 0) FUN_0010f060();
    interrupts = DIntr();
    old = DAT_00559200.func;
    entry->data = data;
    DAT_00559200.func = func;
    __asm__("sw $28,%0" : : "m"(DAT_00559240));
    if (interrupts) EIntr();
    FUN_0010ef60();
    return old;
}
