#ifndef DW4_BENDMWAFSSETUP_H
#define DW4_BENDMWAFSSETUP_H

struct beNDMWAfsSetup;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWAfsSetup_metaObject;
beNDMWAfsSetup *beNDMWAfsSetup_CreateInstance(int allocator);
}

#endif
