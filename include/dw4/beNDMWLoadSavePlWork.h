#ifndef DW4_BENDMWLOADSAVEPLWORK_H
#define DW4_BENDMWLOADSAVEPLWORK_H

struct beNDMWLoadSavePlWork;

extern "C" {
beNDMWLoadSavePlWork *beNDMWLoadSavePlWork_Create(int allocator);
unsigned char beNDMWLoadSavePlWork__GetIsEntry(beNDMWLoadSavePlWork *work);
unsigned char beNDMWLoadSavePlWork__GetIsRdy(beNDMWLoadSavePlWork *work);
void beNDMWLoadSavePlWork__SetIsCtrl(beNDMWLoadSavePlWork *work, int isCtrl);
}

#endif
