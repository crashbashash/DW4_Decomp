#ifndef DW4_BENDMWSTATUSCTRLD0_H
#define DW4_BENDMWSTATUSCTRLD0_H

struct beNDMWStatusCtrlD0;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWStatusCtrlD0_metaObject;
beNDMWStatusCtrlD0 *beNDMWStatusCtrlD0_Create(int allocator);
void beNDMWStatusCtrlD0_RefreshText(beNDMWStatusCtrlD0 *self, int refreshRows, int refreshDescription);
}

#endif
