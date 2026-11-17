#ifndef DW4_BENDMWLOADINTF2CTRLDATA_H
#define DW4_BENDMWLOADINTF2CTRLDATA_H

struct beNDMWLoadIntf2CtrlData;
struct igMetaEnum;

extern "C" {
igMetaEnum *LoadIntf2Message_GetMetaEnum(void);
beNDMWLoadIntf2CtrlData *beNDMWLoadIntf2CtrlData_Create(int allocator);
}

#endif
