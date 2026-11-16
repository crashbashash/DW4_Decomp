#ifndef DW4_IGRANDOMNUMBER_H
#define DW4_IGRANDOMNUMBER_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaObject *igRandomNumber_GetOrCreateMetaObject(void);
void igRandomNumber_EnsureRegistered(void);

#ifdef __cplusplus
}
#endif

#endif
