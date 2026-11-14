int igVirtualCFuncMetaField_ValueFromString(int self, int value, int text) {
    int consumed;

    consumed = 0;
    sscanf(text, &text_0x_08x_n[0], value, &consumed);
    return consumed;
}

void igVirtualCFuncMetaField_ValueToString(int *out, int self, int *value) {
    char text[1024];
    int pool;
    int interned;

    sprintf(text, &text_0x_08x[0], *value);
    if (text == 0) {
        interned = 0;
    } else {
        if (g_stringPool[0] == 0) {
            pool = ((int)StringPool_Allocate(0x10));
            if (pool != 0) {
                pool = ((int)StringPool_Construct((StringPool *)pool));
            }
            g_stringPool[0] = pool;
        }
        interned = StringPool_Intern((StringPool *)g_stringPool[0], (const char *)text);
    }
    *out = interned;
}

int igVirtualCFuncMetaField_GetSize(void) {
    return 4;
}

void igVirtualCFuncMetaField_SetToDefault(void *field, int object) {
 if (object != 0) {
int offset = *(int *)((igMetaField *)field)->_default;
 int vtable = *(int *)(object + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
 ((igMetaFieldView *)field)->SetValue(object, vtable + offset);
}
}

void igVirtualCFuncMetaField_CopyDefaultToValue(int *field, int object) {
    if (object != 0) {
        int *defaultOffset = (int *)((igMetaField *)field)->_default;
        int vtable = *(int *)(object + *(int *)((char *)((void * *)g_objectSystem)[0] + 916));
        ((igMetaFieldView *)field)->SetValue(object, vtable + *defaultOffset);
    }
}

/* igVirtualCFuncMetaField override of the igMetaField slot at vtable +0x6c (slot 27): returns 4.
 * Base igMetaField returns -1 and the ref fields also return 4. The receiver is not read. */
int igVirtualCFuncMetaField_GetAlignment(void) {
    return 4;
}

/* The arena's allocation trigger, called on every operation while the trigger is armed. Each armed condition that
 * holds sets one bit (pool, address, size, operation ordinal, event-tracker count); when every bit the trigger asks
 * for is set, the installed handler runs, or else the event is reported. */
void FUN_0030f040(igArenaMemoryPool *pool, int event, int address, int size) {
    int matched;
    int eventCount;

    if (DAT_005871e8[0] != 0 && (matched = 0, eventCount = -1, (DAT_004c2330[0] & event) != 0)) {
        if (DAT_004c2338[0] == pool->_poolIndex) {
            matched |= 1;
        }
        if (address == DAT_004c2340[0]) {
            matched |= 2;
        }
        if (size == DAT_004c2348[0]) {
            matched |= 4;
        }
        if (DAT_005871e0[0] == DAT_004c2350[0]) {
            matched |= 8;
        }
        if (DAT_004c2358[0] != -1) {
            int tracker = (int)((igMemoryPoolView *)pool)->getEventTracker();
            if (tracker != 0) {
                eventCount = igEventTracker_GetCount((int *)tracker);
                if (eventCount == DAT_004c2358[0]) {
                    matched |= 0x10;
                }
            }
        }
        if (matched != 0 && DAT_005871e8[0] == (DAT_005871e8[0] & matched)) {
            if (DAT_005871f0[0] != 0) {
                DAT_005871f0[0](pool, event, address, size, DAT_005871e0[0], eventCount, matched);
                return;
            }
            if (g_igArenaMemoryPool_defaultMessageLevel[0] < 4 && GPR_00554c34 == 0) {
                int rc = igReportNotice((const char *)text_Arena_trigger_event_s_address_0x,
                                        DAT_004c2310[event], address, size, DAT_005871e0[0], eventCount, matched);
                if (rc != 1 && rc == 2) {
                    GPR_00554c34 = 1;
                }
            }
        }
    }
}

static inline int isFreeChunk(TaggedBlockHeader *h) { if (h->big == 1) { return h->extraUsed; } return 0; }

/* dlmalloc's malloc_init_state: empties the bins, sets the tuning defaults and, when the pool was
 * given raw memory, makes all of it the top chunk. */
void FUN_0030f220(igArenaMemoryPoolView *self) {
    ArenaState *state = self->_arenaState;
    unsigned long long size = self->_size;
    int i;
    int r;
    char *base;
    SystemAllocator_EnsureCreated();
    for (i = 1; i < 96; i++) {
        TaggedBlockHeader *bin = &state->bins[i].header;
        chunkLinks(bin)->forward = bin;
        chunkLinks(bin)->back = bin;
    }
    state->topPad = 0;
    state->mmapLimit = 0;
    state->mmapThreshold = 0x40000;
    state->trimThreshold = 0x40000;
    state->flags |= 1;
    state->maxFast = (75 < self->_smallestChunkSize ? self->_smallestChunkSize : 72) | (state->maxFast & 3);
    if (size != 0) {
        base = (char *)self->GetRawMemory();
        if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && base == 0 && self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (g_igArenaMemoryPool_ignoreE1Notice == 0) {
                r = igReportNotice(text_igArenaMemoryPool_E1_Raw_memory);
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE1Notice = 1;
                }
            }
        }
        if (((unsigned int)base & 7) != 4) {
            char *unaligned = base;
            base = (char *)((((unsigned int)base + 7) & ~7) + 4);
            size -= base - unaligned;
        }
        if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && size <= self->_smallestChunkSize && self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (g_igArenaMemoryPool_ignoreE2Notice == 0) {
                r = igReportNotice(text_igArenaMemoryPool_E2_Raw_memory, self->_smallestChunkSize);
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE2Notice = 1;
                }
            }
        }
        state->top = (TaggedBlockHeader *)base;
        initChunkHeader(self, state->top, (unsigned int)-1, (int)size, 0);
        state->top->used = 1;
    } else {
        state->top = &state->bins[1].header;
    }
    state->pageSize = g_activeSystemAllocator[0]->GetPageSize();
}

void igArenaMemoryPool_CheckChunk(igArenaMemoryPoolView *self, TaggedBlockHeader *h) {
    ArenaState *state;
    unsigned int size;
    int r;
    char *high;
    char *low;
    unsigned int total;
    state = self->_arenaState;
    size = h->size;
    if (h->big == 1) {
        size += h->sizeHigh << 19;
    }
    size = (size + 3) & ~3;
    total = size + (h->words + 1) * 4;
    high = self->getHighestAddress();
    low = self->getLowestAddress();
    if (isFreeChunk(h) == 0) {
        if (h != state->top) {
            if (state->flags & 1) {
                if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && (char *)h < low && self->_messageLevel > 0) {
                    Memory_PrintPoolStatistics(0, self);
                    if (g_igArenaMemoryPool_ignoreE3Notice == 0) {
                        r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor, h, text_E3_Below_used_address_range, low);
                        if (r != 1 && r == 2) {
                            g_igArenaMemoryPool_ignoreE3Notice = 1;
                        }
                    }
                }
                if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && high < (char *)h + total && self->_messageLevel > 0) {
                    Memory_PrintPoolStatistics(0, self);
                    if (g_igArenaMemoryPool_ignoreE4Notice == 0) {
                        r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor, h, text_E4_Above_used_address_range, state->top);
                        if (r != 1 && r == 2) {
                            g_igArenaMemoryPool_ignoreE4Notice = 1;
                        }
                    }
                }
            }
        } else {
            if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && total < ((self->_smallestChunkSize + 7) & ~7) && self->_messageLevel > 0) {
                Memory_PrintPoolStatistics(0, self);
                if (g_igArenaMemoryPool_ignoreE5Notice == 0) {
                    r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor, h, text_E5_Block_size_less_than, (self->_smallestChunkSize + 7) & ~7);
                    if (r != 1 && r == 2) {
                        g_igArenaMemoryPool_ignoreE5Notice = 1;
                    }
                }
            }
            if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !h->used && self->_messageLevel > 0) {
                Memory_PrintPoolStatistics(0, self);
                if (g_igArenaMemoryPool_ignoreE6Notice == 0) {
                    r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, h, text_E6_Corrupted_header);
                    if (r != 1 && r == 2) {
                        g_igArenaMemoryPool_ignoreE6Notice = 1;
                    }
                }
            }
        }
    } else if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && isFreeChunk(h) != 0 && self->_messageLevel > 0) {
        Memory_PrintPoolStatistics(0, self);
        if (g_igArenaMemoryPool_ignoreE10Notice == 0) {
            r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, h, text_E10_Corrupted_header);
            if (r != 1 && r == 2) {
                g_igArenaMemoryPool_ignoreE10Notice = 1;
            }
        }
    }
}

/* dlmalloc's do_check_free_chunk: a free chunk is not in use, its footer repeats its size, its
 * neighbours are in use and its list links point back at it. */
void igArenaMemoryPool_CheckFreeChunk(igArenaMemoryPoolView *self, TaggedBlockHeader *h) {
    ArenaState *state;
    TaggedBlockHeader *next;
    unsigned int total;
    unsigned int size;
    int big;
    int r;
    state = self->_arenaState;
    total = chunkBytes(h);
    next = (TaggedBlockHeader *)((char *)h + total);
    igArenaMemoryPool_CheckChunk(self, h);
    size = h->size;
    big = h->big;
    if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0) {
        if (big == 1) {
            size += h->sizeHigh << 19;
        }
        size = (size + 3) & ~3;
        if (((TaggedBlockHeader *)((char *)h + (size + (h->words + 1) * 4)))->used && self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (g_igArenaMemoryPool_ignoreE11Notice == 0) {
                r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, h, text_E11_This_block_should_be_marked);
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE11Notice = 1;
                }
            }
        }
    }
    if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && isFreeChunk(h) != 0 && self->_messageLevel > 0) {
        Memory_PrintPoolStatistics(0, self);
        if (g_igArenaMemoryPool_ignoreE12Notice == 0) {
            r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, h, text_E12_Corrupted_header);
            if (r != 1 && r == 2) {
                g_igArenaMemoryPool_ignoreE12Notice = 1;
            }
        }
    }
    if (total >= ((self->_smallestChunkSize + 7) & ~7)) {
        if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && (total & 7) != 0 && self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (g_igArenaMemoryPool_ignoreE13Notice == 0) {
                r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor, h, text_E13_Chunk_size_not_aligned, total);
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE13Notice = 1;
                }
            }
        }
        if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && ((int)chunkLinks(h) & 7) != 0 && self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (g_igArenaMemoryPool_ignoreE14Notice == 0) {
                r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, h, text_E14_Misaligned_possibly_corrupte);
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE14Notice = 1;
                }
            }
        }
        if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && total != ((unsigned int *)next)[-1] && self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (g_igArenaMemoryPool_ignoreE15Notice == 0) {
                r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor, h, text_E15_Footer_size_doesn_t_match_po, total);
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE15Notice = 1;
                }
            }
        }
        if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !h->used && self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (g_igArenaMemoryPool_ignoreE16Notice == 0) {
                r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, h, text_E16_Block_may_be_corrupted_not_c);
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE16Notice = 1;
                }
            }
        }
        if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && next != state->top && !((TaggedBlockHeader *)((char *)next + chunkBytes(next)))->used && self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (g_igArenaMemoryPool_ignoreE17Notice == 0) {
                r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, h, text_E17_Subsequent_block_may_be_corr);
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE17Notice = 1;
                }
            }
        }
        if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && (chunkLinks(h)->forward == 0 || chunkLinks(chunkLinks(h)->forward)->back != h) && self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (g_igArenaMemoryPool_ignoreE18Notice == 0) {
                r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, h, text_E18_Corrupted_free_list_forward);
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE18Notice = 1;
                }
            }
        }
        if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && (chunkLinks(h)->back == 0 || chunkLinks(chunkLinks(h)->back)->forward != h) && self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (g_igArenaMemoryPool_ignoreE19Notice == 0) {
                r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, h, text_E19_Corrupted_free_list_back_lin);
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE19Notice = 1;
                }
            }
        }
    } else {
        if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && total != 4 && self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (g_igArenaMemoryPool_ignoreE20Notice == 0) {
                r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor, h, text_E20_Invalid_marker_size_possible, total);
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE20Notice = 1;
                }
            }
        }
    }
}

/* dlmalloc's do_check_inuse_chunk. Each failed check prints the pool statistics and reports a notice; answering
 * the notice with 2 silences that check for the rest of the run. */
void igArenaMemoryPool_CheckInUseChunk(igArenaMemoryPoolView *self, TaggedBlockHeader *h) {
    ArenaState *state;
    TaggedBlockHeader *next;
    TaggedBlockHeader *prev;
    int r;
    state = self->_arenaState;
    igArenaMemoryPool_CheckChunk(self, h);
    if (isFreeChunk(h) != 0) {
        return;
    }
    if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !((TaggedBlockHeader *)((char *)h + chunkBytes(h)))->used && self->_messageLevel > 0) {
        Memory_PrintPoolStatistics(0, self);
        if (g_igArenaMemoryPool_ignoreE21Notice == 0) {
            r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, h, text_E21_This_block_should_be_marked);
            if (r != 1 && r == 2) {
                g_igArenaMemoryPool_ignoreE21Notice = 1;
            }
        }
    }
    next = (TaggedBlockHeader *)((char *)h + chunkBytes(h));
    if (!h->used) {
        prev = (TaggedBlockHeader *)((char *)h - ((int *)h)[-1]);
        if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && (TaggedBlockHeader *)((char *)prev + chunkBytes(prev)) != h && self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (g_igArenaMemoryPool_ignoreE22Notice == 0) {
                r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, h, text_E22_Corrupted_free_list);
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE22Notice = 1;
                }
            }
        }
        igArenaMemoryPool_CheckFreeChunk(self, prev);
    }
    if (next == state->top) {
        if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !next->used && self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (g_igArenaMemoryPool_ignoreE23Notice == 0) {
                r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, h, text_E23_This_block_should_be_marked);
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE23Notice = 1;
                }
            }
        }
        if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && chunkBytes(next) < ((self->_smallestChunkSize + 7) & ~7) && self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (g_igArenaMemoryPool_ignoreE24Notice == 0) {
                r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor, h, text_E24_Block_size_too_small_possibl, chunkBytes(next));
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE24Notice = 1;
                }
            }
        }
    } else if (!((TaggedBlockHeader *)((char *)next + chunkBytes(next)))->used) {
        igArenaMemoryPool_CheckFreeChunk(self, next);
    }
}

static inline int isFreeChunk2(TaggedBlockHeader *h) { if (((TaggedBlockHeader *)h)->big == 1) { return h->extraUsed; } return 0; }

void igArenaMemoryPool_CheckBlock(igArenaMemoryPoolView *self, TaggedBlockHeader *h, int requested) {
    ArenaState *state;
    unsigned int size;
    int r;
    char *high;
    char *low;
    unsigned int total;
    state = self->_arenaState;
    size = h->size;
    if (h->big == 1) {
        size += h->sizeHigh << 19;
    }
    size = (size + 3) & ~3;
    total = size + (h->words + 1) * 4;
    high = self->getHighestAddress();
    low = self->getLowestAddress();
    if (isFreeChunk(h) == 0) {
        if (h != state->top) {
            if (state->flags & 1) {
                if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && (char *)h < low && self->_messageLevel > 0) {
                    Memory_PrintPoolStatistics(0, self);
                    if (g_igArenaMemoryPool_ignoreE25Notice == 0) {
                        r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor, h, text_E25_Below_used_address_range, low);
                        if (r != 1 && r == 2) {
                            g_igArenaMemoryPool_ignoreE25Notice = 1;
                        }
                    }
                }
                if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && high < (char *)h + total && self->_messageLevel > 0) {
                    Memory_PrintPoolStatistics(0, self);
                    if (g_igArenaMemoryPool_ignoreE26Notice == 0) {
                        r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor, h, text_E26_Above_used_address_range, high);
                        if (r != 1 && r == 2) {
                            g_igArenaMemoryPool_ignoreE26Notice = 1;
                        }
                    }
                }
            }
        } else {
            if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && total < ((self->_smallestChunkSize + 7) & ~7) && self->_messageLevel > 0) {
                Memory_PrintPoolStatistics(0, self);
                if (g_igArenaMemoryPool_ignoreE27Notice == 0) {
                    r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor, h, text_E27_Block_size_less_than, (self->_smallestChunkSize + 7) & ~7);
                    if (r != 1 && r == 2) {
                        g_igArenaMemoryPool_ignoreE27Notice = 1;
                    }
                }
            }
            if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !h->used && self->_messageLevel > 0) {
                Memory_PrintPoolStatistics(0, self);
                if (g_igArenaMemoryPool_ignoreE28Notice == 0) {
                    r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, h, text_E28_Corrupted_header);
                    if (r != 1 && r == 2) {
                        g_igArenaMemoryPool_ignoreE28Notice = 1;
                    }
                }
            }
        }
    } else if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && isFreeChunk2(h) != 0 && self->_messageLevel > 0) {
        Memory_PrintPoolStatistics(0, self);
        if (g_igArenaMemoryPool_ignoreE32Notice == 0) {
            r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, h, text_E32_Corrupted_header);
            if (r != 1 && r == 2) {
                g_igArenaMemoryPool_ignoreE32Notice = 1;
            }
        }
    }
    if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && total < ((self->_smallestChunkSize + 7) & ~7) && self->_messageLevel > 0) {
        Memory_PrintPoolStatistics(0, self);
        if (g_igArenaMemoryPool_ignoreE33Notice == 0) {
            r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor, h, text_E33_Block_size_too_small_possibl, total);
            if (r != 1 && r == 2) {
                g_igArenaMemoryPool_ignoreE33Notice = 1;
            }
        }
    }
    if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && ((int)((char *)h + (h->big == 0 ? 4 : 12)) & 7) && self->_messageLevel > 0) {
        Memory_PrintPoolStatistics(0, self);
        if (g_igArenaMemoryPool_ignoreE34Notice == 0) {
            r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, h, text_E34_Block_not_aligned_properly);
            if (r != 1 && r == 2) {
                g_igArenaMemoryPool_ignoreE34Notice = 1;
            }
        }
    }
    if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && (int)(total - requested) < 0 && self->_messageLevel > 0) {
        Memory_PrintPoolStatistics(0, self);
        if (g_igArenaMemoryPool_ignoreE35Notice == 0) {
            r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor, h, text_E35_Block_size_bad_possible_corr, total);
            if (r != 1 && r == 2) {
                g_igArenaMemoryPool_ignoreE35Notice = 1;
            }
        }
    }
    if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && (int)(total - (requested + ((self->_smallestChunkSize + 7) & ~7))) >= 0 && self->_messageLevel > 0) {
        Memory_PrintPoolStatistics(0, self);
        if (g_igArenaMemoryPool_ignoreE36Notice == 0) {
            r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor, h, text_E36_Block_size_bad_possible_corr, total);
            if (r != 1 && r == 2) {
                g_igArenaMemoryPool_ignoreE36Notice = 1;
            }
        }
    }
}

void igArenaMemoryPool_CheckInUseBlock(void *pool, unsigned char *chunk, int requested) {
    int messageLevel;
    int answer;

    igArenaMemoryPool_CheckBlock((igArenaMemoryPoolView *)pool, (TaggedBlockHeader *)chunk, requested);
    if (((igArenaMemoryPoolView *)pool)->_heapIntegrityCheckLevel > 0) {
        messageLevel = ((igArenaMemoryPoolView *)pool)->_messageLevel;
        if ((messageLevel > 0) && !(*chunk & 1) && (messageLevel > 0)) {
            Memory_PrintPoolStatistics(0, pool);
            if (g_igArenaMemoryPool_ignoreE37Notice == 0) {
                answer = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, chunk, &text_E37_Corrupted_header[0]);
                if ((answer != 1) && (answer == 2)) {
                    g_igArenaMemoryPool_ignoreE37Notice = 1;
                }
            }
        }
    }
}


/* dlmalloc's do_check_malloc_state: walks every fast bin and every bin, checking each chunk, that
 * it sits in the right bin, and that the bin map and the fast-chunk flag agree with what is there. */
void FUN_00310c00(igArenaMemoryPoolView *self) {
    unsigned int i;
    TaggedBlockHeader *p;
    TaggedBlockHeader *q;
    unsigned int idx;
    TaggedBlockHeader *b;
    unsigned int binbit;
    unsigned int size;
    unsigned int maxFastBin;
    ArenaState *state = self->_arenaState;
    int empty;
    int r;
    unsigned int total = 0;
    /* dlmalloc's two compile-time asserts, on the size type and on the alignment being a power of
     * two: neither can fail, but the integrity level they test is still read here. */
    if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !(sizeof(unsigned int) <= sizeof(char *)) && self->_messageLevel > 0) {
        Memory_PrintPoolStatistics(0, self);
    }
    if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !((8 & (8 - 1)) == 0) && self->_messageLevel > 0) {
        Memory_PrintPoolStatistics(0, self);
    }
    if (state->top == 0 || state->top == &state->bins[1].header) {
        return;
    }
    if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && (state->pageSize & (state->pageSize - 1)) != 0 && self->_messageLevel > 0) {
        Memory_PrintPoolStatistics(0, self);
        if (g_igArenaMemoryPool_ignoreE38Notice == 0) {
            r = igReportNotice(text_igArenaMemoryPool_s, text_E38_Corrupted_control_structure);
            if (r != 1 && r == 2) {
                g_igArenaMemoryPool_ignoreE38Notice = 1;
            }
        }
    }
    if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !((state->maxFast & ~3) <= (91 < self->_smallestChunkSize ? self->_smallestChunkSize : 88)) && self->_messageLevel > 0) {
        Memory_PrintPoolStatistics(0, self);
        if (g_igArenaMemoryPool_ignoreE39Notice == 0) {
            r = igReportNotice(text_igArenaMemoryPool_s, text_E39_Corrupted_control_structure);
            if (r != 1 && r == 2) {
                g_igArenaMemoryPool_ignoreE39Notice = 1;
            }
        }
    }
    maxFastBin = (state->maxFast >> 3) - 2;
    for (i = 0; i < 10; ++i) {
        p = state->fastBins[i];
        if (i > maxFastBin) {
            if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && p != 0 && self->_messageLevel > 0) {
                Memory_PrintPoolStatistics(0, self);
                if (g_igArenaMemoryPool_ignoreE40Notice == 0) {
                    r = igReportNotice(text_igArenaMemoryPool_s, text_E40_Corrupted_control_structure);
                    if (r != 1 && r == 2) {
                        g_igArenaMemoryPool_ignoreE40Notice = 1;
                    }
                }
            }
        }
        if (p != 0) {
            if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !IS_ARENA_CHUNK(self, p) && self->_messageLevel > 0) {
                Memory_PrintPoolStatistics(0, self);
                if (g_igArenaMemoryPool_ignoreE95Notice == 0) {
                    r = igReportNotice(text_igArenaMemoryPool_s_Possibly_cor, text_igArenaDoCheckMallocState_E95, p);
                    if (r != 1 && r == 2) {
                        g_igArenaMemoryPool_ignoreE95Notice = 1;
                    }
                }
            }
        }
        while (p != 0) {
            TaggedBlockHeader *next;
            igArenaMemoryPool_CheckInUseChunk(self, p);
            total += chunkBytes(p);
            if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && (chunkBytes(p) >> 3) - 2 != i && self->_messageLevel > 0) {
                Memory_PrintPoolStatistics(0, self);
                if (g_igArenaMemoryPool_ignoreE41Notice == 0) {
                    r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, p, text_E41_Corrupted_control_structure);
                    if (r != 1 && r == 2) {
                        g_igArenaMemoryPool_ignoreE41Notice = 1;
                    }
                }
            }
            next = chunkLinks(p)->forward;
            if (next != 0) {
                if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !IS_ARENA_CHUNK(self, next) && self->_messageLevel > 0) {
                    Memory_PrintPoolStatistics(0, self);
                    if (g_igArenaMemoryPool_ignoreE96Notice == 0) {
                        r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, p, text_E96_Corrupted_free_block_link_in);
                        if (r != 1 && r == 2) {
                            g_igArenaMemoryPool_ignoreE96Notice = 1;
                        }
                    }
                }
            }
            p = next;
        }
    }
    if (total != 0) {
        if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !(state->maxFast & 2) && self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (g_igArenaMemoryPool_ignoreE42Notice == 0) {
                r = igReportNotice(text_igArenaMemoryPool_s, text_E42_Corrupted_control_structure);
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE42Notice = 1;
                }
            }
        }
    } else if (!(state->maxFast & 2)) {
        if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && total != 0 && self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (g_igArenaMemoryPool_ignoreE43Notice == 0) {
                r = igReportNotice(text_igArenaMemoryPool_s, text_E43_Corrupted_control_structure);
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE43Notice = 1;
                }
            }
        }
    }
    for (i = 1; i < 96; ++i) {
        b = &state->bins[i].header;
        if (i >= 2) {
            binbit = state->binMap[i >> 5] & (1 << (i & 0x1f));
            empty = chunkLinks(b)->back == b;
            if (!binbit) {
                if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !empty && self->_messageLevel > 0) {
                    Memory_PrintPoolStatistics(0, self);
                    if (g_igArenaMemoryPool_ignoreE44Notice == 0) {
                        r = igReportNotice(text_igArenaMemoryPool_s, text_E44_Corrupted_control_structure);
                        if (r != 1 && r == 2) {
                            g_igArenaMemoryPool_ignoreE44Notice = 1;
                        }
                    }
                }
            } else if (!empty) {
                if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !binbit && self->_messageLevel > 0) {
                    Memory_PrintPoolStatistics(0, self);
                    if (g_igArenaMemoryPool_ignoreE45Notice == 0) {
                        r = igReportNotice(text_igArenaMemoryPool_s, text_E45_Corrupted_control_structure);
                        if (r != 1 && r == 2) {
                            g_igArenaMemoryPool_ignoreE45Notice = 1;
                        }
                    }
                }
            }
        }
        for (p = chunkLinks(b)->back; p != b; p = chunkLinks(p)->back) {
            igArenaMemoryPool_CheckFreeChunk(self, p);
            size = chunkBytes(p);
            total += size;
            if (i >= 2) {
                idx = size < 256 ? size >> 3 : largeBinIndex(size);
                if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && idx != i && self->_messageLevel > 0) {
                    Memory_PrintPoolStatistics(0, self);
                    if (g_igArenaMemoryPool_ignoreE46Notice == 0) {
                        r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, p, text_E46_Corrupted_block_or_free_bloc);
                        if (r != 1 && r == 2) {
                            g_igArenaMemoryPool_ignoreE46Notice = 1;
                        }
                    }
                }
                if (size >= 256) {
                    if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !(chunkLinks(p)->back == b || chunkBytes(chunkLinks(p)->back) >= chunkBytes(p)) && self->_messageLevel > 0) {
                        Memory_PrintPoolStatistics(0, self);
                        if (g_igArenaMemoryPool_ignoreE47Notice == 0) {
                            r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, p, text_E47_Corrupted_block_or_free_bloc);
                            if (r != 1 && r == 2) {
                                g_igArenaMemoryPool_ignoreE47Notice = 1;
                            }
                        }
                    }
                }
            }
            for (q = (TaggedBlockHeader *)((char *)p + chunkBytes(p)); q != state->top && ((TaggedBlockHeader *)((char *)q + chunkBytes(q)))->used && chunkBytes(q) >= ((self->_smallestChunkSize + 7) & ~7); q = (TaggedBlockHeader *)((char *)q + chunkBytes(q))) {
                igArenaMemoryPool_CheckInUseChunk(self, q);
            }
        }
    }
    if (self->_heapIntegrityCheckLevel > 0) {
        igArenaMemoryPool_CheckChunk(self, state->top);
    }
}
