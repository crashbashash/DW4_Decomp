#ifndef DW4_BENDMWDEGIDATA_H
#define DW4_BENDMWDEGIDATA_H

struct beNDMWDegiData;

extern "C" {
beNDMWDegiData *beNDMWDegiData_Create(int allocator);
void beNDMWDegiData__LoadFromProperties(beNDMWDegiData *degi, int props);
void beNDMWDegiData__StoreToProperties(beNDMWDegiData *degi, void *props, int font);
}

#endif
