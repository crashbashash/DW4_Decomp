#ifndef DW4_RECOVERED_STRING_CHUNKS_H
#define DW4_RECOVERED_STRING_CHUNKS_H
#include "messenger-results.h"
/* Twelve allocation/chunk bodies around the separately recovered release
 * bridge. Packed footers use 16-bit four-byte units. Allocator/delete are leaves. */
uint64_t dw4_string_chunk(const Dw4MessengerResultsApi *,uint32_t entry,const uint64_t args[8]);
#endif
