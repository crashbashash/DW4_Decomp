namespace Gap {
namespace Sg {

void igShaderInfo::userRegister()
{
    igShaderFactoryList::arkRegister();
    igSmartPointer<igShaderInfo> info(_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem)));
    info->setName("shaderInfo");
    g_globalContext->getDirectory((const char *)text_system)->appendInfo(info);
}

void igShaderInfo::userUnregister()
{
    g_globalContext->getDirectory((const char *)text_system)->removeInfo("shaderInfo");
}

bool igShaderInfo::attemptResolve(igDirectory *parentDir, void *ref)
{
    int index = _factoryList->find((igShaderFactory *)ref, 0);
    if (index == -1)
        return false;
    igShaderFactory *factory = _factoryList->get(index);
    if (factory->getFileCachingMode() == igShaderFactory::PERSISTENT_CACHE)
        return false;
    const char *name = factory->getNameRef().p ? factory->getNameRef().p : emptyString;
    igDirectory_AddExternalInfoRef(parentDir, this, name, (igObject *)ref);
    return true;
}

void *igShaderInfo::resolve(const char *key)
{
    void *found = _factoryList->search((igStringMetaField *)igNamedObject::k_name, key);
    if (found != 0)
        return found;
    return _factoryList->search((igStringMetaField *)igNamedObject::k_name, "empty");
}
}
}

