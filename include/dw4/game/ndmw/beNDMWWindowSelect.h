#ifndef DW4_BENDMWWINDOWSELECT_H
#define DW4_BENDMWWINDOWSELECT_H

struct beNDMWWindowSelect;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWWindowSelect_metaObject;
bool beNDMWWindowSelect_CanRequestFO2TOP(beNDMWWindowSelect *self);
}

#endif
