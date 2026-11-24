namespace Gap {
namespace Sg {

bool igShaderFactory::configureShader(igSimpleShaderDispatchView *toConfigure, igInterpretedShaderData *configuration, igCapabilityManager *platformCapabilities)
{
    igShaderData *shaderData = toConfigure->_shaderData;
    igSmartPointer<igAttrList> emptyList(igAttrList::_instantiateFromPool(getMemoryPool()));
    shaderData->removeAll();
    shaderData->appendPass(emptyList, emptyList, 0);
    toConfigure->reset();
    return true;
}

igStringObjRef igShaderFactory::getInterfaceParameterString(const char *parameterName)
{
    return igStringObjRef((igStringObj *)0, kRetainReference);
}

void igShaderFactory::setFileCachingMode(FILE_CACHING_MODE mode)
{
    if (mode != _fileCachingMode) {
        _fileCachingMode = mode;
        if (_fileCachingMode == NO_CACHING)
            resetFileCache();
    }
}

void igShaderFactory::resetFileCache()
{

}
}
}

