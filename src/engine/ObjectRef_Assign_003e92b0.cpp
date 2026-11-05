/* Complete combat callback ownership dependency; original template type unknown. */
/* Only the reviewed object prefix is projected here. */
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
typedef struct ObjectRefTarget { int word0; int references; } ObjectRefTarget;
void igObject_Destroy(ObjectRefTarget *);
ObjectRefTarget **ObjectRef_Assign_003e92b0(ObjectRefTarget **destination,ObjectRefTarget **source) {
    ObjectRefTarget *incoming=*source;
    ObjectRefTarget *outgoing;
    if(incoming) ++incoming->references;
    outgoing=*destination;
    if(outgoing) {
        --outgoing->references;
        if(((unsigned long long)(long long)outgoing->references & 0x7fffffULL)==0)
            igObject_Destroy(outgoing);
    }
    *destination=incoming;
    return destination;
}
} /* extern "C" */
