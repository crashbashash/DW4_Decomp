extern "C" {
struct Marker { int word0; int references; };
struct Hit { char pad8[8]; int object; char pad12[8]; float distance; };
struct PickRecord { char pad[104]; float nearest; unsigned char found; char p109[3]; Marker *marker; };
Marker *FUN_0019f630(int);
int FUN_001c5790(Marker *, int);
int igObject_Destroy(Marker *);
}
struct AdoptReference { };
template <class T> struct igSmartPointer {
    T *p;
    igSmartPointer(T *object, AdoptReference) : p(object) {}
    ~igSmartPointer() {
        if (p != 0) {
            p->references = p->references - 1;
            if ((p->references & 0x7FFFFF) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    T *get() const { return p; }
};
static inline void setMarker(PickRecord *record, const igSmartPointer<Marker> &marker) {
    Marker *held = marker.get();
    Marker *previous;
    if (held != 0) {
        held->references = held->references + 1;
    }
    previous = record->marker;
    if (previous != 0) {
        previous->references = previous->references - 1;
        if ((previous->references & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    record->marker = held;
}
extern "C" void FUN_00466a10(PickRecord *record, Hit *hit) {
    int object = hit->object;
    if (hit->distance <= record->nearest) {
        record->found = 1;
        record->nearest = hit->distance;
        {
            igSmartPointer<Marker> marker(FUN_0019f630(0), AdoptReference());
            setMarker(record, marker);
        }
        FUN_001c5790(record->marker, object);
    }
}
