#ifndef DW4_IGREPORT_H
#define DW4_IGREPORT_H

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned char g_reportEchoToStdout;

/* Reports an informational message; returns the report handler's answer (2: ignore further ones). */
int igReport_Info(const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif
