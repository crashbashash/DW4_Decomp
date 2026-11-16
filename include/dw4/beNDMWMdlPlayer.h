#ifndef DW4_BENDMWMDLPLAYER_H
#define DW4_BENDMWMDLPLAYER_H

struct beNDMWMdlPlayer;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWMdlPlayer_metaObject;
beNDMWMdlPlayer *beNDMWMdlPlayer_CreateInstance(int allocator);
}

#endif
