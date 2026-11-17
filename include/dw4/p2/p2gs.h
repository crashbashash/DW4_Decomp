#ifndef DW4_P2GS_H
#define DW4_P2GS_H

#ifdef __cplusplus
extern "C" {
#endif

void p2FlushGsRegisters(void);
void p2SendGsRegister(int arg0);
void p2SetColour(unsigned int colour);
long long p2readGSPrivRegister(int registerIndex);

#ifdef __cplusplus
}
#endif

#endif
