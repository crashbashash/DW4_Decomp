#ifndef DW4_BENDMWMDLPLAYERINFOWORK_H
#define DW4_BENDMWMDLPLAYERINFOWORK_H

struct beNDMWMdlPlayerInfoWork;
struct igMetaEnum;

extern "C" {
igMetaEnum *DamageSeq_GetMetaEnum(void);
igMetaEnum *MsgAction_GetMetaEnum(void);
igMetaEnum *StatusName_GetMetaEnum(void);
beNDMWMdlPlayerInfoWork *beNDMWMdlPlayerInfoWork_Create(int allocator);
}

#endif
