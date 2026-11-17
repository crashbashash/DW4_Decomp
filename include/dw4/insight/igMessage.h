#ifndef DW4_IGMESSAGE_H
#define DW4_IGMESSAGE_H

struct igMetaObject;
struct CallbackArray;

#ifdef __cplusplus
extern "C" {
#endif

struct CallbackArray *igMessage_Register(void);
struct igMetaObject *igMessage_GetPublishedMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
