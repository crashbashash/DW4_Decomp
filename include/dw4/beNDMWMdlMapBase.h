#ifndef DW4_BENDMWMDLMAPBASE_H
#define DW4_BENDMWMDLMAPBASE_H

struct beNDMWMdlMapBase;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWMdlMapBase_metaObject;
beNDMWMdlMapBase *beNDMWMdlMapBase_CreateInstance(int allocator);
}

#endif
