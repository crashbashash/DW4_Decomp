/* Complete combat callback ownership dependency; original template type unknown. */
/* Only the reviewed object prefix is projected here. */
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
typedef struct ObjectRefTarget { int word0; int references; } ObjectRefTarget;
void igObject_Destroy(ObjectRefTarget *);
void ObjectRef_Release_003e9110(ObjectRefTarget *object) {
    if(object) {
        --object->references;
        if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
            igObject_Destroy(object);
    }
}
} /* extern "C" */
