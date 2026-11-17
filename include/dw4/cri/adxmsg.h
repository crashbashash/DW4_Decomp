/* CRI ADXMSG: the ADX libraries' console messages, filtered by a debug level; src/cri/adxmsg.c. */
#ifndef DW4_CRI_ADXMSG_H
#define DW4_CRI_ADXMSG_H

#ifdef __cplusplus
extern "C" {
#endif

int ADXPS2_GetOutputDebugLevel(void);
void ADXPS2_SetOutputDebugLevel(int level);
void ADXPS2_PrintfErr(const char *format, ...);
void ADXPS2_PrintfWarn(const char *format, ...);
void ADXMSG_PrintErr(const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif
