#ifndef DW4_BEWEAPON_H
#define DW4_BEWEAPON_H

struct beWeapon;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beWeapon *beWeapon_CreateInstance(int allocator);

extern struct igMetaObject *g_beWeapon_metaObject;

#ifdef __cplusplus
}
#endif

#endif
