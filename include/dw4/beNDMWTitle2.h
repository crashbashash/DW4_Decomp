#ifndef DW4_BENDMWTITLE2_H
#define DW4_BENDMWTITLE2_H

struct beNDMWTitle2;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWTitle2_metaObject;
extern unsigned char g_commonSettingsValid;
beNDMWTitle2 *beNDMWTitle2_CreateInstance(int allocator);
}

#endif
