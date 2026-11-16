/* Read the pool info from its section of `ini` (the configuration registry by default). Without a
 * section, the defaults section names it under the info's own name. */
igResult igMemoryPoolInfo_LoadFromRegistry(igInfoView *self, igRegistry *ini, char *section) {
    igSmartPointer<igStringObj> value;
    int index = -1;
    int defaults;
    if (ini == 0) {
        ini = g_objectSystem->configRegistry;
    }
    if (ini == 0) {
        return g_resultFailure;
    }
    if (section == 0 || *section == 0) {
        defaults = igRegistry_GetSectionIndex(ini, g_memoryPoolsSectionName, 0);
        if (defaults == -1) {
            return g_resultFailure;
        }
        if (igRegistry_GetValueStringObj((int)ini, defaults, self->_name != 0 ? (const char *)self->_name : (const char *)emptyString, &value.p,
                         (const char *)"", 0) == 0) {
            return g_resultFailure;
        }
        section = igStringObj_Text(value.p);
    }
    if (section != 0 && *section != 0) {
        index = igRegistry_GetSectionIndex(ini, section, 0);
        if (index == -1) {
            return g_resultFailure;
        }
    }
    if (self->UserRegistryLoad(ini, index) == g_resultSuccess) {
        return g_resultSuccess;
    }
    return g_resultFailure;
}

char *g_memoryPoolInfoNameKey = "Name";
char *g_memoryPoolInfoHandleKey = "Handle";
char *g_memoryPoolInfoAliasedToKey = "AliasedTo";
char *g_memoryPoolInfoSizeKey = "Size";
char *g_memoryPoolInfoMaxSizeKey = "MaxSize";
char *g_memoryPoolInfoAddressKey = "Address";
char *g_memoryPoolInfoClassKey = "Class";
char *g_memoryPoolInfoArenaTypeKey = "ArenaType";
char *g_memoryPoolInfoSourceKey = "Source";
char *g_memoryPoolInfoScopeKey = "Scope";
char *g_memoryPoolInfoDebugOptionsKey = "DebugOptions";
char *g_memoryPoolInfoReleaseOptionsKey = "ReleaseOptions";
char *g_memoryPoolInfoDebugCheckingKey = "DebugChecking";
char *g_memoryPoolInfoReleaseCheckingKey = "ReleaseChecking";
char *g_memoryPoolInfoDebugMessagesKey = "DebugMessages";
char *g_memoryPoolInfoReleaseMessagesKey = "ReleaseMessages";
char *g_memoryPoolInfoEventTrackerCapacityKey = "EventTrackerCapacity";

void igMemoryPoolInfo_UserRegistryLoad(int *result, int *info, int ini, int section) {
    
    if (ini == 0) {
        ini = (int)g_objectSystem->configRegistry;
    }
    if (ini == 0) {
        *result = g_resultFailure.v;
    } else {
        igRegistry_GetValueString(ini, section, g_memoryPoolInfoNameKey, (int **)(&info[2]), (char *)info[2], 0);
        igRegistry_GetValueString(ini, section, g_memoryPoolInfoHandleKey, (int **)(&info[5]), (char *)info[5], 0);
        igRegistry_GetValueString(ini, section, g_memoryPoolInfoAliasedToKey, (int **)(&info[6]), (char *)info[6], 0);
        igRegistry_GetValueInt(ini, section, g_memoryPoolInfoSizeKey, &info[7], info[7], 0);
        igRegistry_GetValueInt(ini, section, g_memoryPoolInfoMaxSizeKey, &info[8], info[8], 0);
        igRegistry_GetValueInt(ini, section, g_memoryPoolInfoAddressKey, &info[9], info[9], 0);
        igRegistry_GetValueString(ini, section, g_memoryPoolInfoClassKey, (int **)(&info[10]), (char *)info[10], 0);
        igRegistry_GetValueString(ini, section, g_memoryPoolInfoArenaTypeKey, (int **)(&info[11]), (char *)info[11], 0);
        igRegistry_GetValueString(ini, section, g_memoryPoolInfoSourceKey, (int **)(&info[12]), (char *)info[12], 0);
        igRegistry_GetValueString(ini, section, g_memoryPoolInfoScopeKey, (int **)(&info[13]), (char *)info[13], 0);
        igRegistry_GetValueString(ini, section, g_memoryPoolInfoDebugOptionsKey, (int **)(&info[14]), (char *)info[14], 0);
        igRegistry_GetValueString(ini, section, g_memoryPoolInfoReleaseOptionsKey, (int **)(&info[15]), (char *)info[15], 0);
        igRegistry_GetValueString(ini, section, g_memoryPoolInfoDebugCheckingKey, (int **)(&info[16]), (char *)info[16], 0);
        igRegistry_GetValueString(ini, section, g_memoryPoolInfoReleaseCheckingKey, (int **)(&info[17]), (char *)info[17], 0);
        igRegistry_GetValueString(ini, section, g_memoryPoolInfoDebugMessagesKey, (int **)(&info[18]), (char *)info[18], 0);
        igRegistry_GetValueString(ini, section, g_memoryPoolInfoReleaseMessagesKey, (int **)(&info[19]), (char *)info[19], 0);
        igRegistry_GetValueInt(ini, section, g_memoryPoolInfoEventTrackerCapacityKey, &info[20], info[20], 0);
        *result = g_resultSuccess.v;
    }
}

void igMemoryPoolInfo_TrimCapacity(igMemoryPoolInfo *info) {
    igObject_TrimCapacity((int)info);
    SETSTR(_handleName)
    SETSTR(_aliasedTo)
    info->_size = 0;
    info->_maxSize = 0;
    info->_address = 0;
    SETSTR(_class)
    SETSTR(_arenaType)
    SETSTR(_source)
    SETSTR(_scope)
    SETSTR(_debugOptions)
    SETSTR(_releaseOptions)
    SETSTR(_debugChecking)
    SETSTR(_releaseChecking)
    SETSTR(_debugMessages)
    SETSTR(_releaseMessages)
    info->_eventTrackerCapacity = 0;
}

/* A string field as printed: an unset one prints as the empty text. */
#define TEXT_OR_NONE(text) ((text) != 0 ? (text) : (const char *)"")

void igMemoryPoolInfo_Print(igMemoryPoolInfo *info) {
    igReport_Printf((const char *)"igMemoryPoolInfo:          %s\n", TEXT_OR_NONE(info->_name != 0 ? (const char *)info->_name : (const char *)emptyString));
    igReport_Flush();
    igReport_Printf((const char *)"    _handleName:           %s\n", TEXT_OR_NONE((const char *)info->_handleName));
    igReport_Flush();
    igReport_Printf((const char *)"    _aliasedTo:            %s\n", TEXT_OR_NONE((const char *)info->_aliasedTo));
    igReport_Flush();
    igReport_Printf((const char *)"    _size:                 %d\n", info->_size);
    igReport_Flush();
    igReport_Printf((const char *)"    _maxSize:              %d\n", info->_maxSize);
    igReport_Flush();
    igReport_Printf((const char *)"    _address:              0x%08x\n", info->_address);
    igReport_Flush();
    igReport_Printf((const char *)"    _class:                %s\n", TEXT_OR_NONE((const char *)info->_class));
    igReport_Flush();
    igReport_Printf((const char *)"    _arenaType:            %s\n", TEXT_OR_NONE((const char *)info->_arenaType));
    igReport_Flush();
    igReport_Printf((const char *)"    _source:               %s\n", TEXT_OR_NONE((const char *)info->_source));
    igReport_Flush();
    igReport_Printf((const char *)"    _scope:                %s\n", TEXT_OR_NONE((const char *)info->_scope));
    igReport_Flush();
    igReport_Printf((const char *)"    _debugOptions:         %s\n", TEXT_OR_NONE((const char *)info->_debugOptions));
    igReport_Flush();
    igReport_Printf((const char *)"    _releaseOptions:       %s\n", TEXT_OR_NONE((const char *)info->_releaseOptions));
    igReport_Flush();
    igReport_Printf((const char *)"    _debugChecking:        %s\n", TEXT_OR_NONE((const char *)info->_debugChecking));
    igReport_Flush();
    igReport_Printf((const char *)"    _releaseChecking:      %s\n", TEXT_OR_NONE((const char *)info->_releaseChecking));
    igReport_Flush();
    igReport_Printf((const char *)"    _debugMessages:        %s\n", TEXT_OR_NONE((const char *)info->_debugMessages));
    igReport_Flush();
    igReport_Printf((const char *)"    _releaseMessages:      %s\n", TEXT_OR_NONE((const char *)info->_releaseMessages));
    igReport_Flush();
    igReport_Printf((const char *)"    _eventTrackerCapacity: %d\n", info->_eventTrackerCapacity);
    igReport_Flush();
}
#undef TEXT_OR_NONE

