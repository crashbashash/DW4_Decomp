#ifndef DW4_BENDMWSAVECTRLCTRLDATA_H
#define DW4_BENDMWSAVECTRLCTRLDATA_H

struct beNDMWSaveCtrlCtrlData;
struct igMetaEnum;

extern "C" {
igMetaEnum *SaveCtrlMessage_GetMetaEnum(void);
beNDMWSaveCtrlCtrlData *beNDMWSaveCtrlCtrlData_Create(int allocator);
}

#endif
