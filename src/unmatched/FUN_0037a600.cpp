/* Deleting reference-wrapper destructor (FUN_00135430 family); the deletion flag is signed short. */
extern "C" {
typedef struct ObjectRefTarget { int word0; int references; } ObjectRefTarget;
typedef struct ObjectRefWord { ObjectRefTarget *value; } ObjectRefWord;
void igObject_Destroy(ObjectRefTarget *);
void FUN_00100610(void *);
ObjectRefWord *FUN_0037a600(ObjectRefWord *self,int delete_storage);
}

ObjectRefWord *FUN_0037a600(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}
