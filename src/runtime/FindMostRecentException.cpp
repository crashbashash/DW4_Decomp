#include "dw4/runtime/exception.h"

static inline unsigned char CurrentAction(const ActionIterator *iter) {
    return iter->info.action_pointer ? iter->info.action_pointer[0] & 0x1F : 0;
}

/* Rethrow: the exception of the innermost active catch block becomes the one being thrown. */
extern "C" CatchInfo *FindMostRecentException(ThrowContext *context, MWExceptionInfo *info) {
    ActionIterator iter;
    unsigned char action;
    int cinfo_ref;
    CatchInfo *catchinfo;

    iter.info = *info;
    iter.context = *context;
    for (action = CurrentAction(&iter);; action = NextAction(&iter)) {
        switch (action) {
        case EXACTION_ACTIVECATCHBLOCK:
            break;
        case EXACTION_BRANCH:
        case EXACTION_TERMINATE:
        default:
            __terminate();
            break;
        case EXACTION_ENDOFLIST: case EXACTION_DESTROYLOCAL: case EXACTION_DESTROYLOCALCOND:
        case EXACTION_DESTROYLOCALPOINTER: case EXACTION_DESTROYLOCALARRAY: case EXACTION_DESTROYBASE:
        case EXACTION_DESTROYMEMBER: case EXACTION_DESTROYMEMBERCOND: case EXACTION_DESTROYMEMBERARRAY:
        case EXACTION_DELETEPOINTER: case EXACTION_DELETEPOINTERCOND: case EXACTION_CATCHBLOCK:
        case EXACTION_SPECIFICATION:
            continue;
        }
        break;
    }
    __DecodeSignedNumber(iter.info.action_pointer + 1, &cinfo_ref);
    catchinfo = (CatchInfo *)(iter.context.FP + cinfo_ref);
    context->throwtype = (char *)catchinfo->typeinfo;
    context->location = catchinfo->location;
    context->dtor = 0;
    context->catchinfo = catchinfo;
    return catchinfo;
}
