#ifndef DW4_IGCONTEXT_H
#define DW4_IGCONTEXT_H

/* igContext: class registration. */
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaObject *igContext_GetPublishedMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
