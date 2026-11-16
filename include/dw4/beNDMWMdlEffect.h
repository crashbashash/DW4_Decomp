#ifndef DW4_BENDMWMDLEFFECT_H
#define DW4_BENDMWMDLEFFECT_H

struct beNDMWMdlEffect;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWMdlEffect_metaObject;
beNDMWMdlEffect *beNDMWMdlEffect_CreateInstance(int allocator);
}

#endif
