#ifndef DW4_BENDMWMDLPEBASEINFOWORK_H
#define DW4_BENDMWMDLPEBASEINFOWORK_H

struct beBaseInfoRam;
struct beNDMWMdlPEBaseInfoWork;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWMdlPEBaseInfoWork_metaObject;
void beNDMWMdlPEBaseInfoWork_CurePoison(beNDMWMdlPEBaseInfoWork *self, beBaseInfoRam *ram);
int beNDMWMdlPEBaseInfoWork_IsPoisoned(beNDMWMdlPEBaseInfoWork *self);
}

#endif
