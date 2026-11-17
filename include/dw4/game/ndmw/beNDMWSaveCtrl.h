#ifndef DW4_BENDMWSAVECTRL_H
#define DW4_BENDMWSAVECTRL_H

struct beNDMWSaveCtrl;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWSaveCtrl_metaObject;
beNDMWSaveCtrl *beNDMWSaveCtrl_CreateInstance(int allocator);
}

#endif
