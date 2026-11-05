#ifndef DW4_PLAYERINIT_H
#define DW4_PLAYERINIT_H
#include "dw4/database.h"
#include "dw4/playerrecords.h"
/* Fresh character name/stat path for the four original starter models p_*.
 * ASCII creation grid: 1..8 input characters. The US conversion table filters
 * unsupported punctuation; converted codes are padded to an eight-code object.
 * Builds privately and publishes only on success. Existing borrowed slot folder
 * addresses survive publication; its previous payloads are then released. */
int dw4_playerrecords_create(dw4_playerrecords *,const dw4_databases *,int32_t slot,
    const char *model,const char *name,char *error,size_t cap);
#endif
