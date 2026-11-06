/* igDataList slot 23: the byte size of one list element, 0x24 (36). Same value vfunc_18 passes to
 * List_Reserve when it trims the buffer, and the stride of the audio context's shared 36-byte
 * entry table (igPsx2AudioContext vfunc_53). The sibling lists agree: igDependencyList returns 8
 * and igCharMetricsList 0x28, the sizes their own vfunc_18 trims by. */
#include "dw4/reflected.h"
#define AUDIO_SOURCE_ENTRY_SIZE 0x24
int Gap__igPsx2AudioSourceList__vfunc_23(igPsx2AudioSourceList *self) {
    return AUDIO_SOURCE_ENTRY_SIZE;
}
