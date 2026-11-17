#ifndef DW4_BENDMWSTATUSSUBMENU_H
#define DW4_BENDMWSTATUSSUBMENU_H

struct beNDMWStatusSubMenu;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWStatusSubMenu_metaObject;
beNDMWStatusSubMenu *beNDMWStatusSubMenu_Create(int allocator);
}

#endif
