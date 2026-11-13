#include "dw4/runtime/exception.h"

static inline unsigned char *DecodeCatchBlock(unsigned char *p, ex_catchblock *cb) {
    unsigned char *q = p + 5;
    /* matching construct: manual — the second byte read into its own local gives retail register order */
    unsigned int b1 = p[1];
    cb->catch_type = (char *)(b1 | (p[2] << 8) | (p[3] << 16) | (p[4] << 24));
    cb->catch_type = cb->catch_type ? cb->catch_type : 0;
    q = __DecodeUnsignedNumber(q, &cb->catch_pcoffset);
    return __DecodeSignedNumber(q, &cb->cinfo_ref);
}

static inline void SetCatchInfo(ThrowContext *context, CatchInfo *catchinfo, long offset) {
    catchinfo->location = context->location;
    catchinfo->typeinfo = context->throwtype;
    catchinfo->dtor = context->dtor;
    if (*context->throwtype == '*') {
        catchinfo->sublocation = &catchinfo->pointercopy;
        catchinfo->pointercopy = *(int *)context->location + offset;
    } else {
        catchinfo->sublocation = (char *)context->location + offset;
    }
}

/* Entered from __throw with the thrower's registers saved: find the handler, unwind to it and jump in. */
extern "C" void __ThrowHandler(ThrowContext *context) {
    MWExceptionInfo info;
    ex_catchblock catchblock;
    long offset;
    unsigned char *action;

    __FindExceptionTable(context->returnaddr, &info);
    if (info.exception_record == 0) {
        __terminate();
    }
    __SetupFrameInfo(context, &info);
    if (context->throwtype == 0) {
        context->catchinfo = FindMostRecentException(context, &info);
    } else {
        context->catchinfo = 0;
    }
    action = FindExceptionHandler(context, &info, &offset);
    DecodeCatchBlock(action, &catchblock);
    UnwindStack(context, &info, action);
    SetCatchInfo(context, (CatchInfo *)(context->FP + (long)catchblock.cinfo_ref), offset);
    __TransferControl(context, &info, info.current_function + catchblock.catch_pcoffset);
}
