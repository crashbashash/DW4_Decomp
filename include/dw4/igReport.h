#ifndef DW4_IGREPORT_H
#define DW4_IGREPORT_H

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned char g_reportEchoToStdout;

/* Reports an informational message; returns the report handler's answer (2: ignore further ones). */
int igReport_Info(const char *format, ...);
int igReportError(const char *format, ...);
int igReportNotice(const char *format, ...);
int igReport_Warning(const char *format, ...);
void igReport_Printf(const char *format, ...);
void igReport_Flush(void);

#ifdef __cplusplus
}
#endif

#endif
