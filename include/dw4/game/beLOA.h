#ifndef DW4_BELOA_H
#define DW4_BELOA_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaObject *beLOA_GetMetaObject(void);
void beLOA_RegisterTraversalFunction(void);

#ifdef __cplusplus
}
#endif

#endif
