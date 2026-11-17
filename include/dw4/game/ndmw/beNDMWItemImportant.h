#ifndef DW4_BENDMWITEMIMPORTANT_H
#define DW4_BENDMWITEMIMPORTANT_H

struct beNDMWItemImportant;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWItemImportant_metaObject;
beNDMWItemImportant *beNDMWItemImportant_Create(int allocator);
void beNDMWItemImportant_Set(beNDMWItemImportant *self, int recNo);
}

#endif
