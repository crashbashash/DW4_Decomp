/* Behavioral reference for the complete beSeCtl runtime group 0x0039c900..0x0039cb6c.
 * Engine calls and float conversion remain explicit boundaries. */
#ifndef DW4_RECOVERED_SECTL_H
#define DW4_RECOVERED_SECTL_H
#include "loadintf2.h"
void se_attach(const Dw4LoadIntf2Api *, int32_t);
void se_register(const Dw4LoadIntf2Api *, int32_t, int32_t);
int32_t se_meta(const Dw4LoadIntf2Api *);
void se_tick(const Dw4LoadIntf2Api *);
int32_t se_action(const Dw4LoadIntf2Api *, int32_t, int32_t, int32_t);
int32_t se_data_meta(const Dw4LoadIntf2Api *);
#endif
