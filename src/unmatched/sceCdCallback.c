typedef void (*CdCallback)(int reason);
extern CdCallback DAT_0055cf80;
extern void *DAT_0055cf84;
int sceCdSync(int mode);
int FUN_00113f20(void);
int FUN_00113f78(void);
CdCallback sceCdCallback(CdCallback func) {
    CdCallback old;
    int interrupts;
    if (sceCdSync(1)) return 0;
    interrupts = FUN_00113f20();
    old = DAT_0055cf80;
    DAT_0055cf80 = func;
    __asm__("sw $28,%0" : : "m"(DAT_0055cf84));
    if (interrupts) FUN_00113f78();
    return old;
}
