#ifndef DW4_BENDMWMDLPEBASE_H
#define DW4_BENDMWMDLPEBASE_H

struct beBaseInfoRam;
struct beNDMWMdlPEBase;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWMdlPEBase_metaObject;
void beNDMWMdlPEBase_OnSequenceChange(beNDMWMdlPEBase *self, beBaseInfoRam *ram);
}

#endif
