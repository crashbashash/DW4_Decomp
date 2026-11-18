#ifndef DW4_IGMOUSECURSOR_H
#define DW4_IGMOUSECURSOR_H

#ifdef __cplusplus
extern "C" {
#endif

void igMouseCursor_RunStaticInit(void);

struct igMetaObject *igMouseCursor_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
