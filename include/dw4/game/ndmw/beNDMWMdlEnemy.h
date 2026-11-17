#ifndef DW4_BENDMWMDLENEMY_H
#define DW4_BENDMWMDLENEMY_H

struct beNDMWMdlEnemy;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWMdlEnemy_metaObject;
beNDMWMdlEnemy *beNDMWMdlEnemy_CreateInstance(int allocator);
}

#endif
