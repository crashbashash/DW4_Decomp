typedef void (*CdPowerOffCallback)(void *data);
extern int DAT_00483580;
extern CdPowerOffCallback DAT_0055cf88;
extern void *DAT_0055cf8c;
extern void *DAT_0055cf90;
int PowerOffCB(void);
int FUN_00113f20(void);
int FUN_00113f78(void);
CdPowerOffCallback sceCdPOffCallback(CdPowerOffCallback func, void *data) {
    CdPowerOffCallback old;
    int interrupts;
    if (DAT_00483580 < 0) PowerOffCB();
    interrupts = FUN_00113f20();
    old = DAT_0055cf88;
    DAT_0055cf90 = data;
    DAT_0055cf88 = func;
    __asm__("sw $28,%0" : : "m"(DAT_0055cf8c));
    if (interrupts) FUN_00113f78();
    return old;
}
