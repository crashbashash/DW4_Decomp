/* Only the object prefix used here is declared. */
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
}
