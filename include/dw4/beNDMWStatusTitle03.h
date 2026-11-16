#ifndef DW4_BENDMWSTATUSTITLE03_H
#define DW4_BENDMWSTATUSTITLE03_H

struct beNDMWStatusTitle03;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWStatusTitle03_metaObject;
beNDMWStatusTitle03 *beNDMWStatusTitle03_Create(int allocator);
void beNDMWStatusTitle03_SetCancelPromptEnabled(beNDMWStatusTitle03 *self, int enabled);
}

#endif
