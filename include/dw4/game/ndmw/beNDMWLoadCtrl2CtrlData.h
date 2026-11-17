#ifndef DW4_BENDMWLOADCTRL2CTRLDATA_H
#define DW4_BENDMWLOADCTRL2CTRLDATA_H

struct beNDMWLoadCtrl2CtrlData;
struct igMetaEnum;

extern "C" {
igMetaEnum *LoadCtrl2Message_GetMetaEnum(void);
beNDMWLoadCtrl2CtrlData *beNDMWLoadCtrl2CtrlData_Create(int allocator);
}

#endif
