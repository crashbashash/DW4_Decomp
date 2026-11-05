/* Retain a nonnull object by incrementing its packed reference word. */
typedef struct ObjectRefTarget { int word0; int references; } ObjectRefTarget;
void ObjectRef_Retain_003e90d0(ObjectRefTarget *object) {
    if(object) ++object->references;
}
