#ifndef DW4_BENDMWMDLPBULLET_H
#define DW4_BENDMWMDLPBULLET_H

struct beNDMWMdlPBullet;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWMdlPBullet_metaObject;
beNDMWMdlPBullet *beNDMWMdlPBullet_CreateInstance(int allocator);
}

#endif
