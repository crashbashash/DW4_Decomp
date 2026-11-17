#ifndef DW4_BENDMWMDLITEM_H
#define DW4_BENDMWMDLITEM_H

struct beNDMWMdlItem;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWMdlItem_metaObject;
beNDMWMdlItem *beNDMWMdlItem_CreateInstance(int allocator);
}

#endif
