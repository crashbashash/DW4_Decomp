#ifndef DW4_BENDMWLOGOCTRLDATA_H
#define DW4_BENDMWLOGOCTRLDATA_H

struct beNDMWLogoCtrlData;
struct igMetaEnum;

extern "C" {
beNDMWLogoCtrlData *beNDMWLogoCtrlData_Create(int allocator);
igMetaEnum *beNDMWLogoCtrlData_GetMessageEnum(void);
}

#endif
