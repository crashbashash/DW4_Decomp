#include "dw4/runtime/exception.h"

/* Step past the current action to the next one, popping to the caller's frame at the end of a list; branches are followed. */
extern "C" unsigned char NextAction(ActionIterator *iter) {
    unsigned char *ap;
    unsigned char action;
    ThrowContext *context = &iter->context;

    for (;;) {
        ap = iter->info.action_pointer;
        bool valid = ap;
        if (!valid || (*ap & 0x80)) {
            __FindExceptionTable(__PopStackFrame(context, &iter->info), &iter->info);
            if (iter->info.exception_record == 0) {
                __terminate();
            }
            __SetupFrameInfo(context, &iter->info);
            if (iter->info.action_pointer == 0) {
                continue;
            }
            break;
        }
        switch (*ap & 0x1F) {
        case EXACTION_DESTROYLOCAL: {
            int local;
            iter->info.action_pointer = __DecodeSignedNumber(ap + 1, &local) + 4;
            break;
        }
        case EXACTION_DESTROYLOCALCOND: {
            int cond, local;
            iter->info.action_pointer = __DecodeSignedNumber(__DecodeSignedNumber(ap + 1, &cond), &local) + 4;
            break;
        }
        case EXACTION_DESTROYLOCALPOINTER: {
            int pointer;
            iter->info.action_pointer = __DecodeSignedNumber(ap + 1, &pointer) + 4;
            break;
        }
        case EXACTION_DESTROYLOCALARRAY: {
            int localarray;
            unsigned int elements, element_size;
            iter->info.action_pointer = __DecodeUnsignedNumber(__DecodeUnsignedNumber(__DecodeSignedNumber(ap + 1, &localarray), &elements), &element_size) + 4;
            break;
        }
        case EXACTION_DESTROYBASE: {
            int pointer, offset;
            iter->info.action_pointer = __DecodeSignedNumber(__DecodeSignedNumber(ap + 1, &pointer), &offset) + 4;
            break;
        }
        case EXACTION_DESTROYMEMBER: {
            int pointer, offset;
            iter->info.action_pointer = __DecodeSignedNumber(__DecodeSignedNumber(ap + 1, &pointer), &offset) + 4;
            break;
        }
        case EXACTION_DESTROYMEMBERCOND: {
            int cond, pointer, offset;
            iter->info.action_pointer = __DecodeSignedNumber(__DecodeSignedNumber(__DecodeSignedNumber(ap + 1, &cond), &pointer), &offset) + 4;
            break;
        }
        case EXACTION_DESTROYMEMBERARRAY: {
            int pointer, offset;
            unsigned int elements, element_size;
            iter->info.action_pointer = __DecodeUnsignedNumber(__DecodeUnsignedNumber(__DecodeSignedNumber(__DecodeSignedNumber(ap + 1, &pointer), &offset), &elements), &element_size) + 4;
            break;
        }
        case EXACTION_DELETEPOINTER: {
            int pointer;
            iter->info.action_pointer = __DecodeSignedNumber(ap + 1, &pointer) + 4;
            break;
        }
        case EXACTION_DELETEPOINTERCOND: {
            int cond, pointer;
            iter->info.action_pointer = __DecodeSignedNumber(__DecodeSignedNumber(ap + 1, &cond), &pointer) + 4;
            break;
        }
        case EXACTION_CATCHBLOCK: {
            char *catch_type;
            unsigned int catch_pcoffset;
            int cinfo_ref;
            /* matching construct: manual — the second byte read into its own local gives retail register order */
            unsigned int b1 = ap[1];
            *(unsigned int *)&catch_type = b1 | (ap[2] << 8) | (ap[3] << 16) | (ap[4] << 24);
            iter->info.action_pointer = __DecodeSignedNumber(__DecodeUnsignedNumber(ap + 5, &catch_pcoffset), &cinfo_ref);
            break;
        }
        case EXACTION_ACTIVECATCHBLOCK: {
            int cinfo_ref;
            iter->info.action_pointer = __DecodeSignedNumber(ap + 1, &cinfo_ref);
            break;
        }
        case EXACTION_SPECIFICATION: {
            unsigned int specs, pcoffset;
            int cinfo_ref;
            iter->info.action_pointer = __DecodeSignedNumber(__DecodeUnsignedNumber(__DecodeUnsignedNumber(ap + 1, &specs), &pcoffset), &cinfo_ref) + specs * 4;
            break;
        }
        default:
            __terminate();
            break;
        }
        break;
    }
    while ((action = *iter->info.action_pointer & 0x1F) == EXACTION_BRANCH) {
        int offset;
        __DecodeSignedNumber(iter->info.action_pointer + 1, &offset);
        iter->info.action_pointer += offset;
    }
    return action;
}
