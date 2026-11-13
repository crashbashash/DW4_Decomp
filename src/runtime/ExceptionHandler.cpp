/* The target-independent half of the C++ exception handler: decoding a function's action list, finding the catch
 * block for a thrown type, unwinding the frames in between, and the exception-specification fallback. The frame
 * layout, the exception index and the jump into a catch block are in ExceptionHandlerTS.cpp. */
#include "dw4/runtime/exception.h"
#include "dw4/runtime/cxxlib.h"

/* The numbers of an action record are packed: bit 0 clear, one byte (value << 1); else bit 1 clear, two bytes;
 * else bit 2 clear, three bytes; else four. */
extern "C" unsigned char *__DecodeUnsignedNumber(unsigned char *p, unsigned int *value) {
    unsigned int b0 = p[0];
    unsigned int b1, b2;
    if (!(b0 & 1)) {
        *value = b0 >> 1;
        return p + 1;
    }
    b1 = p[1];
    if (!(b0 & 2)) {
        *value = ((b0 >> 2) << 8) | b1;
        return p + 2;
    }
    b2 = p[2];
    if (!(b0 & 4)) {
        *value = b2 | (((b0 >> 3) << 16) | (b1 << 8));
        return p + 3;
    }
    *value = p[3] | ((b2 << 8) | (((b0 >> 3) << 24) | (b1 << 16)));
    return p + 4;
}

/* As __DecodeUnsignedNumber, with the first byte's top bit the sign. */
extern "C" unsigned char *__DecodeSignedNumber(unsigned char *p, int *value) {
    int b0 = (signed char)p[0];
    unsigned int b1, b2;
    if (!(b0 & 1)) {
        *value = b0 >> 1;
        return p + 1;
    }
    b1 = p[1];
    if (!(b0 & 2)) {
        *value = ((b0 >> 2) << 8) | b1;
        return p + 2;
    }
    b2 = p[2];
    if (!(b0 & 4)) {
        *value = b2 | (((b0 >> 3) << 16) | (b1 << 8));
        return p + 3;
    }
    *value = p[3] | ((b2 << 8) | (((b0 >> 3) << 24) | (b1 << 16)));
    return p + 4;
}

typedef void (*Destructor)(void *object, short how);
typedef void (*DeleteFunc)(void *object);

/* What a destructor destroys: the class's own part, leaving its virtual bases, or the complete object. */
enum { DTOR_PARTIAL = 0, DTOR_COMPLETE = -1 };

/* A function or type address, stored unaligned and little-endian. */
static inline unsigned char *DecodeAddress(unsigned char *p, void **address) {
    *address = (void *)((unsigned int)p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24));
    return p + 4;
}

static inline char *LocalVariable(ThrowContext *context, int offset) {
    return context->FP + offset;
}

/* The end of a catch block: the caught object is destroyed. */
extern "C" void __end__catch(CatchInfo *catchinfo) {
    if (catchinfo->location != 0 && catchinfo->dtor != 0) {
        ((Destructor)catchinfo->dtor)(catchinfo->location, DTOR_COMPLETE);
    }
}

static inline unsigned char CurrentAction(const ActionIterator *iter) {
    return iter->info.action_pointer ? *iter->info.action_pointer & EXACTION_MASK : EXACTION_ENDOFLIST;
}

static inline void DecodeCatchBlock(unsigned char *ap, ex_catchblock *cb) {
    ap += 1;
    ap = DecodeAddress(ap, (void **)&cb->catch_type);
    cb->catch_type = cb->catch_type ? cb->catch_type : 0;
    ap = __DecodeUnsignedNumber(ap, &cb->catch_pcoffset);
    __DecodeSignedNumber(ap, &cb->cinfo_ref);
}

static inline void DecodeSpecification(unsigned char *ap, ex_specification *spec) {
    ap += 1;
    ap = __DecodeUnsignedNumber(ap, &spec->specs);
    ap = __DecodeUnsignedNumber(ap, &spec->pcoffset);
    ap = __DecodeSignedNumber(ap, &spec->cinfo_ref);
    spec->spec = ap;
}

static inline int IsInSpecification(char *throwtype, ex_specification *spec) {
    unsigned char *p = spec->spec;
    char *catch_type;
    long offset;
    unsigned int i;

    for (i = 0; i < spec->specs; i++) {
        DecodeAddress(p, (void **)&catch_type);
        if (__throw_catch_compare(throwtype, catch_type, &offset)) {
            return 1;
        }
        p += 4;
    }
    return 0;
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

/* Entered from a function whose exception specification the thrown type violates (catchinfo->stacktop is the
 * specification's action): the unexpected handler may throw a type the specification allows, or bad_exception if
 * the specification lists it; anything else terminates. */
extern "C" void __unexpected(CatchInfo *catchinfo) {
    unsigned char *action = (unsigned char *)catchinfo->stacktop;
    ex_specification spec;

#pragma exception_magic
    try {
        __call_unexpected_handler();
    } catch (...) {
        DecodeSpecification(action, &spec);
        if (IsInSpecification((char *)((CatchInfo *)&__exception_magic)->typeinfo, &spec)) {
            throw;
        }
        if (IsInSpecification("!std::bad_exception!!", &spec)) {
            throw std::bad_exception();
        }
    }
    __terminate();
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

/* One handler per action type: each decodes its record (the type byte, then its fields in the order the handler reads
 * them) and moves the action pointer past it; under APPLY it also runs the cleanup. A cleanup's object or condition
 * sits in the frame at its offset, or in the saved register of that number when the type byte's EXACTION_REGPTR or
 * EXACTION_REGCOND bit is set. */
enum { SKIP, APPLY };

/* A branch moves the action pointer by its offset, relative to the branch action. */
static inline void Branch(MWExceptionInfo *info) {
    int target;
    __DecodeSignedNumber(info->action_pointer + 1, &target);
    info->action_pointer += target;
}

static inline void DestroyLocal(int apply, MWExceptionInfo *info, ThrowContext *context) {
    unsigned char *ap = info->action_pointer;
    int local;
    void *dtor;

    ap = __DecodeSignedNumber(ap + 1, &local);
    ap = DecodeAddress(ap, &dtor);
    if (apply) {
        ((Destructor)dtor)(LocalVariable(context, local), DTOR_COMPLETE);
    }
    info->action_pointer = ap;
}

static inline void DestroyLocalCond(int apply, MWExceptionInfo *info, ThrowContext *context) {
    unsigned char *ap = info->action_pointer;
    int regcond;
    int cond, local;
    void *dtor;
    char destroy;

    regcond = *ap & EXACTION_REGCOND;
    ap = __DecodeSignedNumber(ap + 1, &cond);
    ap = __DecodeSignedNumber(ap, &local);
    ap = DecodeAddress(ap, &dtor);
    if (apply) {
        if (regcond) {
            destroy = (char)context->target.GPR[cond];
        } else {
            destroy = *LocalVariable(context, cond);
        }
        if (destroy) {
            ((Destructor)dtor)(LocalVariable(context, local), DTOR_COMPLETE);
        }
    }
    info->action_pointer = ap;
}

static inline void DestroyLocalPointer(int apply, MWExceptionInfo *info, ThrowContext *context) {
    unsigned char *ap = info->action_pointer;
    int regptr;
    int pointer;
    void *dtor;
    void *object;

    regptr = *ap & EXACTION_REGPTR;
    ap = __DecodeSignedNumber(ap + 1, &pointer);
    ap = DecodeAddress(ap, &dtor);
    if (apply) {
        if (regptr) {
            object = (void *)(int)context->target.GPR[pointer];
        } else {
            object = *(void **)LocalVariable(context, pointer);
        }
        ((Destructor)dtor)(object, DTOR_COMPLETE);
    }
    info->action_pointer = ap;
}

static inline void DestroyLocalArray(int apply, MWExceptionInfo *info, ThrowContext *context) {
    unsigned char *ap = info->action_pointer;
    int array;
    unsigned int elements, element_size, i;
    void *dtor;
    char *element;

    ap = __DecodeSignedNumber(ap + 1, &array);
    ap = __DecodeUnsignedNumber(ap, &elements);
    ap = __DecodeUnsignedNumber(ap, &element_size);
    ap = DecodeAddress(ap, &dtor);
    if (apply) {
        element = LocalVariable(context, array);
        for (element += elements * element_size, i = elements; i > 0; i--) {
            element -= element_size;
            ((Destructor)dtor)(element, DTOR_COMPLETE);
        }
    }
    info->action_pointer = ap;
}

static inline void DestroyBase(int apply, MWExceptionInfo *info, ThrowContext *context) {
    unsigned char *ap = info->action_pointer;
    int regptr;
    int pointer, offset;
    void *dtor;
    char *object;

    regptr = *ap & EXACTION_REGPTR;
    ap = __DecodeSignedNumber(ap + 1, &pointer);
    ap = __DecodeSignedNumber(ap, &offset);
    ap = DecodeAddress(ap, &dtor);
    if (apply) {
        if (regptr) {
            object = (char *)(int)context->target.GPR[pointer];
        } else {
            object = *(char **)LocalVariable(context, pointer);
        }
        ((Destructor)dtor)(object + offset, DTOR_PARTIAL);
    }
    info->action_pointer = ap;
}

static inline void DestroyMember(int apply, MWExceptionInfo *info, ThrowContext *context) {
    unsigned char *ap = info->action_pointer;
    int regptr;
    int pointer, offset;
    void *dtor;
    char *object;

    regptr = *ap & EXACTION_REGPTR;
    ap = __DecodeSignedNumber(ap + 1, &pointer);
    ap = __DecodeSignedNumber(ap, &offset);
    ap = DecodeAddress(ap, &dtor);
    if (apply) {
        if (regptr) {
            object = (char *)(int)context->target.GPR[pointer];
        } else {
            object = *(char **)LocalVariable(context, pointer);
        }
        ((Destructor)dtor)(object + offset, DTOR_COMPLETE);
    }
    info->action_pointer = ap;
}

static inline void DestroyMemberCond(int apply, MWExceptionInfo *info, ThrowContext *context) {
    unsigned char *ap = info->action_pointer;
    int regptr, regcond;
    int cond, pointer, offset;
    void *dtor;
    char *object;
    char destroy;

    regcond = *ap & EXACTION_REGCOND;
    regptr = *ap & EXACTION_REGPTR;
    ap = __DecodeSignedNumber(ap + 1, &cond);
    ap = __DecodeSignedNumber(ap, &pointer);
    ap = __DecodeSignedNumber(ap, &offset);
    ap = DecodeAddress(ap, &dtor);
    if (apply) {
        if (regcond) {
            destroy = (char)context->target.GPR[cond];
        } else {
            destroy = *LocalVariable(context, cond);
        }
        if (destroy) {
            if (regptr) {
                object = (char *)(int)context->target.GPR[pointer];
            } else {
                object = *(char **)LocalVariable(context, pointer);
            }
            ((Destructor)dtor)(object + offset, DTOR_COMPLETE);
        }
    }
    info->action_pointer = ap;
}

static inline void DestroyMemberArray(int apply, MWExceptionInfo *info, ThrowContext *context) {
    unsigned char *ap = info->action_pointer;
    int regptr;
    int pointer, offset;
    unsigned int elements, element_size, i;
    void *dtor;
    char *element;

    regptr = *ap & EXACTION_REGPTR;
    ap = __DecodeSignedNumber(ap + 1, &pointer);
    ap = __DecodeSignedNumber(ap, &offset);
    ap = __DecodeUnsignedNumber(ap, &elements);
    ap = __DecodeUnsignedNumber(ap, &element_size);
    ap = DecodeAddress(ap, &dtor);
    if (apply) {
        if (regptr) {
            element = (char *)(int)context->target.GPR[pointer] + offset;
        } else {
            element = *(char **)LocalVariable(context, pointer) + offset;
        }
        for (element += elements * element_size, i = elements; i > 0; i--) {
            element -= element_size;
            ((Destructor)dtor)(element, DTOR_COMPLETE);
        }
    }
    info->action_pointer = ap;
}

static inline void DeletePointer(int apply, MWExceptionInfo *info, ThrowContext *context) {
    unsigned char *ap = info->action_pointer;
    int pointer;
    void *deletefunc;
    void *object;
    int regptr;

    regptr = *ap & EXACTION_REGPTR;
    ap = __DecodeSignedNumber(ap + 1, &pointer);
    ap = DecodeAddress(ap, &deletefunc);
    if (apply) {
        if (regptr) {
            object = (void *)(int)context->target.GPR[pointer];
        } else {
            object = *(void **)LocalVariable(context, pointer);
        }
        ((DeleteFunc)deletefunc)(object);
    }
    info->action_pointer = ap;
}

static inline void DeletePointerCond(int apply, MWExceptionInfo *info, ThrowContext *context) {
    unsigned char *ap = info->action_pointer;
    int cond, pointer;
    void *deletefunc;
    void *object;
    int regptr, regcond;
    char destroy;

    regcond = *ap & EXACTION_REGCOND;
    regptr = *ap & EXACTION_REGPTR;
    ap = __DecodeSignedNumber(ap + 1, &cond);
    ap = __DecodeSignedNumber(ap, &pointer);
    ap = DecodeAddress(ap, &deletefunc);
    if (apply) {
        if (regcond) {
            destroy = (char)context->target.GPR[cond];
        } else {
            destroy = *LocalVariable(context, cond);
        }
        if (destroy) {
            if (regptr) {
                object = (void *)(int)context->target.GPR[pointer];
            } else {
                object = *(void **)LocalVariable(context, pointer);
            }
            ((DeleteFunc)deletefunc)(object);
        }
    }
    info->action_pointer = ap;
}

static inline void CatchBlock(MWExceptionInfo *info) {
    unsigned char *ap = info->action_pointer;
    char *catch_type;
    unsigned int pcoffset;
    int cinfo_ref;

    ap += 1;
    ap = DecodeAddress(ap, (void **)&catch_type);
    ap = __DecodeUnsignedNumber(ap, &pcoffset);
    ap = __DecodeSignedNumber(ap, &cinfo_ref);
    info->action_pointer = ap;
}

/* A catch block whose handler is running: the exception it caught is destroyed, unless that same object is being
 * rethrown, which then takes over destroying it. */
static inline void ActiveCatchBlock(int apply, MWExceptionInfo *info, ThrowContext *context) {
    unsigned char *ap = info->action_pointer;
    int cinfo_ref;
    CatchInfo *catchinfo;

    ap = __DecodeSignedNumber(ap + 1, &cinfo_ref);
    if (apply) {
        catchinfo = (CatchInfo *)LocalVariable(context, cinfo_ref);
        if (catchinfo->dtor) {
            if (context->location == catchinfo->location) {
                context->dtor = catchinfo->dtor;
            } else {
                ((Destructor)catchinfo->dtor)(catchinfo->location, DTOR_COMPLETE);
            }
        }
    }
    info->action_pointer = ap;
}

static inline void Specification(MWExceptionInfo *info) {
    unsigned char *ap = info->action_pointer;
    unsigned int specs, pcoffset;
    int cinfo_ref;

    ap = __DecodeUnsignedNumber(ap + 1, &specs);
    ap = __DecodeUnsignedNumber(ap, &pcoffset);
    ap = __DecodeSignedNumber(ap, &cinfo_ref);
    ap += specs * 4;
    info->action_pointer = ap;
}

/* Run the cleanups of every frame from the thrower's up to `catcher`, the catch block or exception specification
 * that takes the exception. */
extern "C" void UnwindStack(ThrowContext *context, MWExceptionInfo *info, unsigned char *catcher) {
    unsigned char action;

#pragma exception_terminate
    for (;;) {
        if (!info->action_pointer) {
            __FindExceptionTable(__PopStackFrame(context, info), info);
            if (!info->exception_record) {
                __terminate();
            }
            __SetupFrameInfo(context, info);
            if (!info->action_pointer) {
                continue;
            }
        }
        action = *info->action_pointer;
        switch (action & EXACTION_MASK) {
        case EXACTION_BRANCH:
            Branch(info);
            break;
        case EXACTION_DESTROYLOCAL:
            DestroyLocal(APPLY, info, context);
            break;
        case EXACTION_DESTROYLOCALCOND:
            DestroyLocalCond(APPLY, info, context);
            break;
        case EXACTION_DESTROYLOCALPOINTER:
            DestroyLocalPointer(APPLY, info, context);
            break;
        case EXACTION_DESTROYLOCALARRAY:
            DestroyLocalArray(APPLY, info, context);
            break;
        case EXACTION_DESTROYBASE:
            DestroyBase(APPLY, info, context);
            break;
        case EXACTION_DESTROYMEMBER:
            DestroyMember(APPLY, info, context);
            break;
        case EXACTION_DESTROYMEMBERCOND:
            DestroyMemberCond(APPLY, info, context);
            break;
        case EXACTION_DESTROYMEMBERARRAY:
            DestroyMemberArray(APPLY, info, context);
            break;
        case EXACTION_DELETEPOINTER:
            DeletePointer(APPLY, info, context);
            break;
        case EXACTION_DELETEPOINTERCOND:
            DeletePointerCond(APPLY, info, context);
            break;
        case EXACTION_CATCHBLOCK:
            if (catcher == info->action_pointer) {
                return;
            }
            CatchBlock(info);
            break;
        case EXACTION_ACTIVECATCHBLOCK:
            ActiveCatchBlock(APPLY, info, context);
            break;
        case EXACTION_SPECIFICATION:
            if (catcher == info->action_pointer) {
                return;
            }
            Specification(info);
            break;
        default:
            __terminate();
        }
        if (action & EXACTION_ENDBIT) {
            info->action_pointer = 0;
        }
    }
}

/* Step past the current action to the next one, popping to the caller's frame at the end of a list; branches are followed. */
extern "C" unsigned char NextAction(ActionIterator *iter) {
    MWExceptionInfo *info = &iter->info;
    ThrowContext *context = &iter->context;
    unsigned char action;

    for (;;) {
        if (!info->action_pointer || *info->action_pointer & EXACTION_ENDBIT) {
            __FindExceptionTable(__PopStackFrame(context, info), info);
            if (!info->exception_record) {
                __terminate();
            }
            __SetupFrameInfo(context, info);
            if (!info->action_pointer) {
                continue;
            }
        } else {
            switch (*info->action_pointer & EXACTION_MASK) {
            case EXACTION_DESTROYLOCAL:
                DestroyLocal(SKIP, info, context);
                break;
            case EXACTION_DESTROYLOCALCOND:
                DestroyLocalCond(SKIP, info, context);
                break;
            case EXACTION_DESTROYLOCALPOINTER:
                DestroyLocalPointer(SKIP, info, context);
                break;
            case EXACTION_DESTROYLOCALARRAY:
                DestroyLocalArray(SKIP, info, context);
                break;
            case EXACTION_DESTROYBASE:
                DestroyBase(SKIP, info, context);
                break;
            case EXACTION_DESTROYMEMBER:
                DestroyMember(SKIP, info, context);
                break;
            case EXACTION_DESTROYMEMBERCOND:
                DestroyMemberCond(SKIP, info, context);
                break;
            case EXACTION_DESTROYMEMBERARRAY:
                DestroyMemberArray(SKIP, info, context);
                break;
            case EXACTION_DELETEPOINTER:
                DeletePointer(SKIP, info, context);
                break;
            case EXACTION_DELETEPOINTERCOND:
                DeletePointerCond(SKIP, info, context);
                break;
            case EXACTION_CATCHBLOCK:
                CatchBlock(info);
                break;
            case EXACTION_ACTIVECATCHBLOCK:
                ActiveCatchBlock(SKIP, info, context);
                break;
            case EXACTION_SPECIFICATION:
                Specification(info);
                break;
            default:
                __terminate();
            }
        }
        while ((action = *info->action_pointer & EXACTION_MASK) == EXACTION_BRANCH) {
            Branch(info);
        }
        return action;
    }
}

static inline ExceptionTableIndex *FindIndexEntry(ExceptionTableIndex *table, unsigned int count, char *return_address) {
    int lo, mid, hi;
    ExceptionTableIndex *entry;
    for (lo = 0, hi = count - 1; lo <= hi;) {
        entry = &table[mid = (lo + hi) >> 1];
        if (return_address < entry->function_address) {
            hi = mid - 1;
        } else if (return_address > entry->function_address + (entry->function_size & ~1)) {
            lo = mid + 1;
        } else {
            return entry;
        }
    }
    return 0;
}

/* The exception record of the function holding `return_address`, and the action list of the code range around it
 * (none when the address is outside every range: nothing to do in that frame). */
extern "C" void __FindExceptionTable(char *return_address, MWExceptionInfo *info) {
    ExceptionTableIndex *entry;
    unsigned char *ranges;
    unsigned int offset;
    unsigned int pc;
    unsigned int delta;
    unsigned int length;
    unsigned int actions;

    info->exception_record = 0;
    info->action_pointer = 0;
    if (!__GetExceptionIndexBounds(info, return_address)) {
        return;
    }
    return_address = (char *)((int)return_address & ~1L);
    entry = FindIndexEntry(info->exception_table_start, info->exception_table_end - info->exception_table_start, return_address);
    if (!entry) {
        return;
    }
    if (entry->function_size & 1) {
        info->exception_record = (char *)&entry->exception_table;
    } else {
        info->exception_record = entry->exception_table;
    }
    info->current_function = entry->function_address;
    offset = return_address - entry->function_address;
    ranges = __SkipFrameInfo(info->exception_record);
    for (pc = 0;;) {
        ranges = __DecodeUnsignedNumber(ranges, &delta);
        if (delta == 0) {
            return;
        }
        ranges = __DecodeUnsignedNumber(ranges, &length);
        ranges = __DecodeUnsignedNumber(ranges, &actions);
        pc += delta;
        if (offset < pc) {
            return;
        }
        pc += length;
        if (offset <= pc) {
            break;
        }
    }
    info->action_pointer = (unsigned char *)info->exception_record + actions;
}
