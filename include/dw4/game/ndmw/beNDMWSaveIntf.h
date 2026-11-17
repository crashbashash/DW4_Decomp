#ifndef DW4_BENDMWSAVEINTF_H
#define DW4_BENDMWSAVEINTF_H

struct beNDMWSaveIntf;
struct igMetaEnum;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWSaveIntf_metaObject;
beNDMWSaveIntf *beNDMWSaveIntf_CreateInstance(int allocator);
igMetaEnum *beNDMWSaveIntf_GetMessageEnum(void);
}

#endif
