#ifndef DW4_BENDMWMDLMAPCURSOR_H
#define DW4_BENDMWMDLMAPCURSOR_H

struct beNDMWMdlMapCursor;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWMdlMapCursor_metaObject;
beNDMWMdlMapCursor *beNDMWMdlMapCursor_CreateInstance(int allocator);
}

#endif
