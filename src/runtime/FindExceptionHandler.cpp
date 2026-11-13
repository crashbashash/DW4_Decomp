#include "dw4/runtime/exception.h"

static inline unsigned char CurrentAction(const ActionIterator *iter) {
    return iter->info.action_pointer ? iter->info.action_pointer[0] & 0x1F : 0;
}

static inline unsigned char *DecodeCatchBlock(unsigned char *p, ex_catchblock *cb) {
    unsigned char *q = p + 5;
    /* matching construct: manual — the second byte read into its own local gives retail register order */
    unsigned int b1 = p[1];
    cb->catch_type = (char *)(b1 | (p[2] << 8) | (p[3] << 16) | (p[4] << 24));
    cb->catch_type = cb->catch_type ? cb->catch_type : 0;
    q = __DecodeUnsignedNumber(q, &cb->catch_pcoffset);
    return __DecodeSignedNumber(q, &cb->cinfo_ref);
}

static inline void DecodeSpecification(unsigned char *p, ex_specification *spec) {
    unsigned char *q = p + 1;
    q = __DecodeUnsignedNumber(q, &spec->specs);
    q = __DecodeUnsignedNumber(q, &spec->pcoffset);
    q = __DecodeSignedNumber(q, &spec->cinfo_ref);
    spec->spec = q;
}

static inline int IsInSpecification(char *throwtype, ex_specification *spec) {
    long offset;
    unsigned char *p = spec->spec;
    unsigned int i;

    for (i = 0; i < spec->specs; i++, p += 4) {
        char *catch_type;
        /* matching construct: manual — the second byte read into its own local gives retail register order */
        unsigned int b1 = p[1];
        *(unsigned int *)&catch_type = p[0] | (b1 << 8) | (p[2] << 16) | (p[3] << 24);
        if (__throw_catch_compare(throwtype, catch_type, &offset)) {
            return 1;
        }
    }
    return 0;
}

/* The catch block that takes the thrown type; a violated exception specification unwinds into its handler instead. */
extern "C" unsigned char *FindExceptionHandler(ThrowContext *context, MWExceptionInfo *info, long *result_offset) {
    ActionIterator iter;
    unsigned char action;
    ex_catchblock catchblock;
    ex_specification spec;

    iter.info = *info;
    iter.context = *context;
    for (action = CurrentAction(&iter);; action = NextAction(&iter)) {
        switch (action) {
        case EXACTION_CATCHBLOCK: {
            DecodeCatchBlock(iter.info.action_pointer, &catchblock);
            if (!__throw_catch_compare(context->throwtype, catchblock.catch_type, result_offset)) {
                continue;
            }
            goto found;
        }
        case EXACTION_SPECIFICATION: {
            DecodeSpecification(iter.info.action_pointer, &spec);
            if (!IsInSpecification(context->throwtype, &spec)) {
                unsigned char *action_pointer = iter.info.action_pointer;
                CatchInfo *catchinfo;
#pragma exception_terminate
                UnwindStack(context, info, action_pointer);
                catchinfo = (CatchInfo *)(context->FP + spec.cinfo_ref);
                catchinfo->location = context->location;
                catchinfo->typeinfo = context->throwtype;
                catchinfo->dtor = context->dtor;
                catchinfo->stacktop = action_pointer;
                __TransferControl(context, info, info->current_function + spec.pcoffset);
            }
            continue;
        }
        case EXACTION_BRANCH:
        case EXACTION_TERMINATE:
        default:
            __terminate();
            goto found;
        case EXACTION_ENDOFLIST: case EXACTION_DESTROYLOCAL: case EXACTION_DESTROYLOCALCOND:
        case EXACTION_DESTROYLOCALPOINTER: case EXACTION_DESTROYLOCALARRAY: case EXACTION_DESTROYBASE:
        case EXACTION_DESTROYMEMBER: case EXACTION_DESTROYMEMBERCOND: case EXACTION_DESTROYMEMBERARRAY:
        case EXACTION_DELETEPOINTER: case EXACTION_DELETEPOINTERCOND: case EXACTION_ACTIVECATCHBLOCK:
            continue;
        }
    }
found:
    return iter.info.action_pointer;
}
