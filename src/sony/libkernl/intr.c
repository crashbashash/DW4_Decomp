/* intr.c - libkernl's INTC and DMAC interrupt-mask calls: the thread versions mask interrupts
 * around the kernel call, the i- versions are for handlers, which already run masked. Each ends
 * with a sync so the mask write is done before the caller goes on. */

#include "dw4/sony/libkernl.h"

typedef unsigned int u_int;

#define STATUS_EIE 0x10000
#define STATUS_IE 0x1

int _EnableIntc(int cause);
int _DisableIntc(int cause);
int _EnableDmac(int channel);
int _DisableDmac(int channel);
int _iEnableIntc(int cause);
int _iDisableIntc(int cause);
int _iEnableDmac(int channel);
int _iDisableDmac(int channel);

int QueryIntrContext(void)
{
    u_int stat;
    __asm__("mfc0 %0, $12" : "=r"(stat));
    return !(stat & STATUS_IE);
}

int DisableIntc(int cause)
{
    u_int stat;
    int ret;
    __asm__ volatile("mfc0 %0, $12" : "=r"(stat));
    stat &= STATUS_EIE;
    if (stat) DIntr();
    ret = _DisableIntc(cause);
    __asm__("sync");
    if (stat) EIntr();
    return ret;
}

int EnableIntc(int cause)
{
    u_int stat;
    int ret;
    __asm__ volatile("mfc0 %0, $12" : "=r"(stat));
    stat &= STATUS_EIE;
    if (stat) DIntr();
    ret = _EnableIntc(cause);
    __asm__("sync");
    if (stat) EIntr();
    return ret;
}

int DisableDmac(int channel)
{
    u_int stat;
    int ret;
    __asm__ volatile("mfc0 %0, $12" : "=r"(stat));
    stat &= STATUS_EIE;
    if (stat) DIntr();
    ret = _DisableDmac(channel);
    __asm__("sync");
    if (stat) EIntr();
    return ret;
}

int EnableDmac(int channel)
{
    u_int stat;
    int ret;
    __asm__ volatile("mfc0 %0, $12" : "=r"(stat));
    stat &= STATUS_EIE;
    if (stat) DIntr();
    ret = _EnableDmac(channel);
    __asm__("sync");
    if (stat) EIntr();
    return ret;
}

void iEnableIntc(int cause)
{
    _iEnableIntc(cause);
    __asm__("sync");
}

void iDisableIntc(int cause)
{
    _iDisableIntc(cause);
    __asm__("sync");
}

void iEnableDmac(int channel)
{
    _iEnableDmac(channel);
    __asm__("sync");
}

void iDisableDmac(int channel)
{
    _iDisableDmac(channel);
    __asm__("sync");
}
