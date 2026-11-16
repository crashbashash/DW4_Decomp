#ifndef DW4_BENDMWITEMREVISIONPOCKETBASE_H
#define DW4_BENDMWITEMREVISIONPOCKETBASE_H

struct beNDMWItemRevisionPocketBase;
struct beNDMWStatus;

extern "C" {
int beNDMWItemRevisionPocketBase_GetPrice(beNDMWItemRevisionPocketBase *self, beNDMWStatus *status, const char *priceKey);
}

#endif
