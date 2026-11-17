#ifndef DW4_BENDMWTITLE2CTRLDATA_H
#define DW4_BENDMWTITLE2CTRLDATA_H

struct beNDMWTitle2CtrlData;
struct igMetaEnum;

extern "C" {
beNDMWTitle2CtrlData *beNDMWTitle2CtrlData_Create(int allocator);
igMetaEnum *beNDMWTitle2CtrlData_GetMessageEnum(void);
}

#endif
