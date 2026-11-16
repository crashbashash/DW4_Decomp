#ifndef DW4_BENDMWLOGO_H
#define DW4_BENDMWLOGO_H

struct beNDMWLogo;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWLogo_metaObject;
beNDMWLogo *beNDMWLogo_CreateInstance(int allocator);
}

#endif
