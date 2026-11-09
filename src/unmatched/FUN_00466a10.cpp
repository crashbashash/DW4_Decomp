#include "dw4/igSmartPointer.h"

extern "C" {
struct Marker : public igObject { };
struct Hit { char pad8[8]; int object; char pad12[8]; float distance; };
struct PickRecord { char pad[104]; float nearest; unsigned char found; char p109[3]; Marker *marker; };
Marker *FUN_0019f630(int);
int FUN_001c5790(Marker *, int);
}

static inline void setMarker(PickRecord *record, const igSmartPointer<Marker> &marker) {
    Marker *held = marker.get();
    Marker *previous;
    if (held != 0) {
        held->_refCount = held->_refCount + 1;
    }
    previous = record->marker;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    record->marker = held;
}
static inline Marker *createMarker() { AdoptReference tag = AdoptReference(); return FUN_0019f630(0); }
extern "C" void FUN_00466a10(PickRecord *record, Hit *hit) {
    int object = hit->object;
    if (hit->distance <= record->nearest) {
        record->found = 1;
        record->nearest = hit->distance;
        setMarker(record, igSmartPointer<Marker>(createMarker()));
        FUN_001c5790(record->marker, object);
    }
}
