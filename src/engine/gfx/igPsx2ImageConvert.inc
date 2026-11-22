namespace Gap {
namespace Gfx {

igMetaObject *igPsx2ImageConvert::_Meta;

void igImageConvert::arkRegisterInitialize()
{
    igMetaObject *metaObject = _Meta;	// cache in a local variable

    *(void (**)())&metaObject->_abstractProxy = (void (*)())Gap::Gfx::igPsx2ImageConvert::getClassMetaSafe;
}
}
}

