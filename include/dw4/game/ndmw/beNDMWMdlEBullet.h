#ifndef DW4_BENDMWMDLEBULLET_H
#define DW4_BENDMWMDLEBULLET_H

struct beNDMWMdlEBullet;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWMdlEBullet_metaObject;
beNDMWMdlEBullet *beNDMWMdlEBullet_CreateInstance(int allocator);
}

#endif
