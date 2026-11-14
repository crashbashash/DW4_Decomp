/* Read the pool info from its section of `ini` (the configuration registry by default). Without a
 * section, the defaults section names it under the info's own name. */
igResult Gap__Core__igMemoryPoolInfo__vfunc_25(igInfoView *self, igRegistry *ini, char *section) {
    igSmartPointer<igStringObj> value;
    int index = -1;
    int defaults;
    if (ini == 0) {
        ini = ((ObjectSystemView *)g_objectSystem[0])->configRegistry;
    }
    if (ini == 0) {
        return g_resultFailure;
    }
    if (section == 0 || *section == 0) {
        defaults = FUN_00306360(ini, DAT_004c2228[0], 0);
        if (defaults == -1) {
            return g_resultFailure;
        }
        if (FUN_00306770((int)ini, defaults, self->_name != 0 ? (const char *)self->_name : (const char *)emptyString, &value.p,
                         (const char *)DAT_004f7910, 0) == 0) {
            return g_resultFailure;
        }
        section = igStringObj_Text(value.p);
    }
    if (section != 0 && *section != 0) {
        index = FUN_00306360(ini, section, 0);
        if (index == -1) {
            return g_resultFailure;
        }
    }
    if (self->vfunc_26(ini, index) == g_resultSuccess) {
        return g_resultSuccess;
    }
    return g_resultFailure;
}

void Gap__Core__igMemoryPoolInfo__vfunc_26(int *arg0, int *arg1, int arg2, int arg3) {
    
    if (arg2 == 0) {
        arg2 = ((struct { char pad[56]; int i56; } * *)g_objectSystem)[0]->i56;
    }
    if (arg2 == 0) {
        *arg0 = g_resultFailure.v;
    } else {
        FUN_00306910(arg2, arg3, DAT_004c2230, (int **)(&arg1[2]), (char *)arg1[2], 0);
        FUN_00306910(arg2, arg3, DAT_004c2238, (int **)(&arg1[5]), (char *)arg1[5], 0);
        FUN_00306910(arg2, arg3, DAT_004c2240, (int **)(&arg1[6]), (char *)arg1[6], 0);
        FUN_003065f0(arg2, arg3, DAT_004c2248, &arg1[7], arg1[7], 0);
        FUN_003065f0(arg2, arg3, DAT_004c2250, &arg1[8], arg1[8], 0);
        FUN_003065f0(arg2, arg3, DAT_004c2258, &arg1[9], arg1[9], 0);
        FUN_00306910(arg2, arg3, DAT_004c2260, (int **)(&arg1[10]), (char *)arg1[10], 0);
        FUN_00306910(arg2, arg3, DAT_004c2268, (int **)(&arg1[11]), (char *)arg1[11], 0);
        FUN_00306910(arg2, arg3, DAT_004c2270, (int **)(&arg1[12]), (char *)arg1[12], 0);
        FUN_00306910(arg2, arg3, DAT_004c2278, (int **)(&arg1[13]), (char *)arg1[13], 0);
        FUN_00306910(arg2, arg3, DAT_004c2280, (int **)(&arg1[14]), (char *)arg1[14], 0);
        FUN_00306910(arg2, arg3, DAT_004c2288, (int **)(&arg1[15]), (char *)arg1[15], 0);
        FUN_00306910(arg2, arg3, DAT_004c2290, (int **)(&arg1[16]), (char *)arg1[16], 0);
        FUN_00306910(arg2, arg3, DAT_004c2298, (int **)(&arg1[17]), (char *)arg1[17], 0);
        FUN_00306910(arg2, arg3, DAT_004c22a0, (int **)(&arg1[18]), (char *)arg1[18], 0);
        FUN_00306910(arg2, arg3, DAT_004c22a8, (int **)(&arg1[19]), (char *)arg1[19], 0);
        FUN_003065f0(arg2, arg3, DAT_004c22b0, &arg1[20], arg1[20], 0);
        *arg0 = g_resultSuccess.v;
    }
}

void Gap__Core__igMemoryPoolInfo__vfunc_18(igMemoryPoolInfo *arg0) {
    Gap__Core__igObject__vfunc_16((int)arg0);
    SETSTR(_handleName)
    SETSTR(_aliasedTo)
    arg0->_size = 0;
    arg0->_maxSize = 0;
    arg0->_address = 0;
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
    arg0->_eventTrackerCapacity = 0;
}

/* A string field as printed: an unset one prints as the empty text. */
#define TEXT_OR_NONE(text) ((text) != 0 ? (text) : (const char *)DAT_004f7910)

void igMemoryPoolInfo_Print(igMemoryPoolInfo *info) {
    FUN_00304430((const char *)DAT_004facc0, TEXT_OR_NONE(info->_name != 0 ? (const char *)info->_name : (const char *)emptyString));
    FUN_00304680();
    FUN_00304430((const char *)DAT_004face0, TEXT_OR_NONE((const char *)info->_handleName));
    FUN_00304680();
    FUN_00304430((const char *)DAT_004fad00, TEXT_OR_NONE((const char *)info->_aliasedTo));
    FUN_00304680();
    FUN_00304430((const char *)DAT_004fad20, info->_size);
    FUN_00304680();
    FUN_00304430((const char *)DAT_004fad40, info->_maxSize);
    FUN_00304680();
    FUN_00304430((const char *)DAT_004fad60, info->_address);
    FUN_00304680();
    FUN_00304430((const char *)DAT_004fad90, TEXT_OR_NONE((const char *)info->_class));
    FUN_00304680();
    FUN_00304430((const char *)DAT_004fadb0, TEXT_OR_NONE((const char *)info->_arenaType));
    FUN_00304680();
    FUN_00304430((const char *)DAT_004fadd0, TEXT_OR_NONE((const char *)info->_source));
    FUN_00304680();
    FUN_00304430((const char *)DAT_004fadf0, TEXT_OR_NONE((const char *)info->_scope));
    FUN_00304680();
    FUN_00304430((const char *)DAT_004fae10, TEXT_OR_NONE((const char *)info->_debugOptions));
    FUN_00304680();
    FUN_00304430((const char *)DAT_004fae30, TEXT_OR_NONE((const char *)info->_releaseOptions));
    FUN_00304680();
    FUN_00304430((const char *)DAT_004fae50, TEXT_OR_NONE((const char *)info->_debugChecking));
    FUN_00304680();
    FUN_00304430((const char *)DAT_004fae70, TEXT_OR_NONE((const char *)info->_releaseChecking));
    FUN_00304680();
    FUN_00304430((const char *)DAT_004fae90, TEXT_OR_NONE((const char *)info->_debugMessages));
    FUN_00304680();
    FUN_00304430((const char *)DAT_004faeb0, TEXT_OR_NONE((const char *)info->_releaseMessages));
    FUN_00304680();
    FUN_00304430((const char *)DAT_004faed0, info->_eventTrackerCapacity);
    FUN_00304680();
}
#undef TEXT_OR_NONE

