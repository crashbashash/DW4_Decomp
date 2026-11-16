#ifndef DW4_BENDMWMDLPLAYER2INFOWORK_H
#define DW4_BENDMWMDLPLAYER2INFOWORK_H

struct beNDMWMdlPlayer2InfoWork;
struct igMetaEnum;

extern "C" {
igMetaEnum *PanelCloseSeqList_GetMetaEnum(void);
beNDMWMdlPlayer2InfoWork *beNDMWMdlPlayer2InfoWork_Create(int allocator);
}

#endif
