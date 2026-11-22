namespace Gap {
namespace Core {

void igMemoryFile::arkRegisterUser() {
    userRegister();
}

void igMemoryFile::_classDestructor() {
    userUnregister();
}
}
}

