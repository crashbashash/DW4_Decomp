#ifndef DW4_IGOBJECTSYSTEM_H
#define DW4_IGOBJECTSYSTEM_H

/* Starting and stopping the Alchemy object system; `headerVersion` is the version of the headers the
 * caller was built with (0xC80). */
#ifdef __cplusplus
extern "C" {
#endif

void igObjectSystem_Acquire(int headerVersion);
void igObjectSystem_Release(void);
void igObjectSystem_SetIniText(const char *text);

#ifdef __cplusplus
}
#endif

#endif
