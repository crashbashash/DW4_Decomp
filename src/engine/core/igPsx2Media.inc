void igPsx2Media_GetMetaObjectFunction(void) {
    igPsx2Media_GetMetaObject();
}

namespace Gap {
namespace Core {

void igMedia::arkRegisterUser() {
    userRegister();
}

void igMedia::_classDestructor() {
    userUnregister();
}
}
}

