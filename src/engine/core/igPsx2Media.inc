void igPsx2Media_GetMetaObjectFunction(void) {
    igPsx2Media_GetMetaObject();
}

namespace Gap {
namespace Core {

void igMedia::userRegister() {
    igMedia_CreateMediaList();
}

void igMedia::_classDestructor() {
    userUnregister();
}
}
}

