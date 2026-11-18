#ifndef DW4_IGTEXTELEMENT_H
#define DW4_IGTEXTELEMENT_H

#ifdef __cplusplus
extern "C" {
#endif

void igTextElement_EnsureRegistered(void);

struct igMetaObject *igTextElement_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
