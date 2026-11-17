#ifndef DW4_BENDMWMDLOBJECT_H
#define DW4_BENDMWMDLOBJECT_H

struct beNDMWMdlObject;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWMdlObject_metaObject;
beNDMWMdlObject *beNDMWMdlObject_CreateInstance(int allocator);
}

#endif
