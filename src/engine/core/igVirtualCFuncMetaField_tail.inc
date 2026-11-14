int igVirtualCFuncMetaField_ValueFromString(int arg0, int arg1, int arg2) {
    int sp1C;

    sp1C = 0;
    sscanf(arg2, &text_0x_08x_n[0], arg1, &sp1C);
    return sp1C;
}

void igVirtualCFuncMetaField_ValueToString(int *arg0, int arg1, int *arg2) {
    char sp20[1024];
    int var_v0;
    int var_v1;

    sprintf(sp20, &text_0x_08x[0], *arg2);
    if (sp20 == 0) {
        var_v1 = 0;
    } else {
        if (g_stringPool[0] == 0) {
            var_v0 = ((int)StringPool_Allocate(0x10));
            if (var_v0 != 0) {
                var_v0 = ((int)StringPool_Construct((StringPool *)var_v0));
            }
            g_stringPool[0] = var_v0;
        }
        var_v1 = StringPool_Intern((StringPool *)g_stringPool[0], (const char *)sp20);
    }
    *arg0 = var_v1;
}

int igVirtualCFuncMetaField_GetSize(void) {
    return 4;
}

void igVirtualCFuncMetaField_SetToDefault(void *arg0, int arg1) {
 if (arg1 != 0) {
int a = **(int **)((char *)(arg0) + 32);
 int b = *(int *)(arg1 + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
 ((igMetaFieldView *)arg0)->vfunc_24(arg1, b + a);
}
}

void igVirtualCFuncMetaField_CopyDefaultToValue(int *arg0, int arg1) {
    if (arg1 != 0) {
        int *c = (int *)arg0[8];
        int u = *(int *)(arg1 + *(int *)((char *)((void * *)g_objectSystem)[0] + 916));
        ((igMetaFieldView *)arg0)->vfunc_24(arg1, u + *c);
    }
}

/* igVirtualCFuncMetaField override of the igMetaField slot at vtable +0x6c (slot 27): returns 4.
 * Base igMetaField returns -1 and the ref fields also return 4. The receiver is not read. */
int igVirtualCFuncMetaField_GetAlignment(void) {
    return 4;
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
        TaggedBlockHeader *bin = (TaggedBlockHeader *)state->bins[i];
        chunkLinks(bin)->forward = bin;
        chunkLinks(bin)->back = bin;
    }
    state->f1992 = 0;
    state->mmapLimit = 0;
    state->mmapThreshold = 0x40000;
    state->trimThreshold = 0x40000;
    state->flags |= 1;
    state->maxFast = (75 < self->_smallestChunkSize ? self->_smallestChunkSize : 72) | (state->maxFast & 3);
    if (size != 0) {
        base = (char *)self->vfunc_26();
        if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && base == 0 && self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (GPR_00554c38 == 0) {
                r = igReportNotice(DAT_004fb4d0);
                if (r != 1 && r == 2) {
                    GPR_00554c38 = 1;
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
            if (GPR_00554c3c == 0) {
                r = igReportNotice(DAT_004fb510, self->_smallestChunkSize);
                if (r != 1 && r == 2) {
                    GPR_00554c3c = 1;
                }
            }
        }
        state->top = base;
        initChunkHeader((TaggedBlockHeader *)state->top, (unsigned int)-1, (int)size, (unsigned int)self->_poolIndex >> 1, 0);
        ((TaggedBlockHeader *)state->top)->used = 1;
    } else {
        state->top = state->bins[1];
    }
    state->pageSize = g_activeSystemAllocator[0]->vfunc_21();
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
        if ((char *)h != state->top) {
            if (state->flags & 1) {
                if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && (char *)h < low && self->_messageLevel > 0) {
                    Memory_PrintPoolStatistics(0, self);
                    if (GPR_00554c40 == 0) {
                        r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor, h, text_E3_Below_used_address_range, low);
                        if (r != 1 && r == 2) {
                            GPR_00554c40 = 1;
                        }
                    }
                }
                if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && high < (char *)h + total && self->_messageLevel > 0) {
                    Memory_PrintPoolStatistics(0, self);
                    if (GPR_00554c44 == 0) {
                        r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor, h, text_E4_Above_used_address_range, state->top);
                        if (r != 1 && r == 2) {
                            GPR_00554c44 = 1;
                        }
                    }
                }
            }
        } else {
            if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && total < ((self->_smallestChunkSize + 7) & ~7) && self->_messageLevel > 0) {
                Memory_PrintPoolStatistics(0, self);
                if (GPR_00554c48 == 0) {
                    r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor, h, text_E5_Block_size_less_than, (self->_smallestChunkSize + 7) & ~7);
                    if (r != 1 && r == 2) {
                        GPR_00554c48 = 1;
                    }
                }
            }
            if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !h->used && self->_messageLevel > 0) {
                Memory_PrintPoolStatistics(0, self);
                if (GPR_00554c4c == 0) {
                    r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, h, text_E6_Corrupted_header);
                    if (r != 1 && r == 2) {
                        GPR_00554c4c = 1;
                    }
                }
            }
        }
    } else if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && isFreeChunk(h) != 0 && self->_messageLevel > 0) {
        Memory_PrintPoolStatistics(0, self);
        if (GPR_00554c50 == 0) {
            r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, h, text_E10_Corrupted_header);
            if (r != 1 && r == 2) {
                GPR_00554c50 = 1;
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
            if (GPR_00554c54 == 0) {
                r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, h, DAT_004fb6a0);
                if (r != 1 && r == 2) {
                    GPR_00554c54 = 1;
                }
            }
        }
    }
    if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && isFreeChunk(h) != 0 && self->_messageLevel > 0) {
        Memory_PrintPoolStatistics(0, self);
        if (GPR_00554c58 == 0) {
            r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, h, DAT_004fb6e0);
            if (r != 1 && r == 2) {
                GPR_00554c58 = 1;
            }
        }
    }
    if (total >= ((self->_smallestChunkSize + 7) & ~7)) {
        if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && (total & 7) != 0 && self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (GPR_00554c5c == 0) {
                r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor, h, DAT_004fb700, total);
                if (r != 1 && r == 2) {
                    GPR_00554c5c = 1;
                }
            }
        }
        if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && ((int)chunkLinks(h) & 7) != 0 && self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (GPR_00554c60 == 0) {
                r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, h, DAT_004fb720);
                if (r != 1 && r == 2) {
                    GPR_00554c60 = 1;
                }
            }
        }
        if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && total != ((unsigned int *)next)[-1] && self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (GPR_00554c64 == 0) {
                r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor, h, DAT_004fb750, total);
                if (r != 1 && r == 2) {
                    GPR_00554c64 = 1;
                }
            }
        }
        if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !h->used && self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (GPR_00554c68 == 0) {
                r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, h, DAT_004fb790);
                if (r != 1 && r == 2) {
                    GPR_00554c68 = 1;
                }
            }
        }
        if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && (char *)next != state->top && !((TaggedBlockHeader *)((char *)next + chunkBytes(next)))->used && self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (GPR_00554c6c == 0) {
                r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, h, DAT_004fb7d0);
                if (r != 1 && r == 2) {
                    GPR_00554c6c = 1;
                }
            }
        }
        if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && (chunkLinks(h)->forward == 0 || chunkLinks(chunkLinks(h)->forward)->back != h) && self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (GPR_00554c70 == 0) {
                r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, h, DAT_004fb810);
                if (r != 1 && r == 2) {
                    GPR_00554c70 = 1;
                }
            }
        }
        if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && (chunkLinks(h)->back == 0 || chunkLinks(chunkLinks(h)->back)->forward != h) && self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (GPR_00554c74 == 0) {
                r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, h, DAT_004fb840);
                if (r != 1 && r == 2) {
                    GPR_00554c74 = 1;
                }
            }
        }
    } else {
        if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && total != 4 && self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (GPR_00554c78 == 0) {
                r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor, h, DAT_004fb870, total);
                if (r != 1 && r == 2) {
                    GPR_00554c78 = 1;
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
    if ((char *)next == state->top) {
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
        if ((char *)h != state->top) {
            if (state->flags & 1) {
                if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && (char *)h < low && self->_messageLevel > 0) {
                    Memory_PrintPoolStatistics(0, self);
                    if (GPR_00554c8c == 0) {
                        r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor, h, text_E25_Below_used_address_range, low);
                        if (r != 1 && r == 2) {
                            GPR_00554c8c = 1;
                        }
                    }
                }
                if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && high < (char *)h + total && self->_messageLevel > 0) {
                    Memory_PrintPoolStatistics(0, self);
                    if (GPR_00554c90 == 0) {
                        r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor, h, text_E26_Above_used_address_range, high);
                        if (r != 1 && r == 2) {
                            GPR_00554c90 = 1;
                        }
                    }
                }
            }
        } else {
            if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && total < ((self->_smallestChunkSize + 7) & ~7) && self->_messageLevel > 0) {
                Memory_PrintPoolStatistics(0, self);
                if (GPR_00554c94 == 0) {
                    r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor, h, text_E27_Block_size_less_than, (self->_smallestChunkSize + 7) & ~7);
                    if (r != 1 && r == 2) {
                        GPR_00554c94 = 1;
                    }
                }
            }
            if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !h->used && self->_messageLevel > 0) {
                Memory_PrintPoolStatistics(0, self);
                if (GPR_00554c98 == 0) {
                    r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, h, text_E28_Corrupted_header);
                    if (r != 1 && r == 2) {
                        GPR_00554c98 = 1;
                    }
                }
            }
        }
    } else if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && isFreeChunk2(h) != 0 && self->_messageLevel > 0) {
        Memory_PrintPoolStatistics(0, self);
        if (GPR_00554c9c == 0) {
            r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, h, text_E32_Corrupted_header);
            if (r != 1 && r == 2) {
                GPR_00554c9c = 1;
            }
        }
    }
    if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && total < ((self->_smallestChunkSize + 7) & ~7) && self->_messageLevel > 0) {
        Memory_PrintPoolStatistics(0, self);
        if (GPR_00554ca0 == 0) {
            r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor, h, text_E33_Block_size_too_small_possibl, total);
            if (r != 1 && r == 2) {
                GPR_00554ca0 = 1;
            }
        }
    }
    if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && ((int)((char *)h + (h->big == 0 ? 4 : 12)) & 7) && self->_messageLevel > 0) {
        Memory_PrintPoolStatistics(0, self);
        if (GPR_00554ca4 == 0) {
            r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, h, text_E34_Block_not_aligned_properly);
            if (r != 1 && r == 2) {
                GPR_00554ca4 = 1;
            }
        }
    }
    if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && (int)(total - requested) < 0 && self->_messageLevel > 0) {
        Memory_PrintPoolStatistics(0, self);
        if (GPR_00554ca8 == 0) {
            r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor, h, text_E35_Block_size_bad_possible_corr, total);
            if (r != 1 && r == 2) {
                GPR_00554ca8 = 1;
            }
        }
    }
    if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && (int)(total - (requested + ((self->_smallestChunkSize + 7) & ~7))) >= 0 && self->_messageLevel > 0) {
        Memory_PrintPoolStatistics(0, self);
        if (GPR_00554cac == 0) {
            r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor, h, text_E36_Block_size_bad_possible_corr, total);
            if (r != 1 && r == 2) {
                GPR_00554cac = 1;
            }
        }
    }
}

void igArenaMemoryPool_CheckInUseBlock(void *arg0, unsigned char *arg1, int extra2) {
    int temp_a0;
    int temp_v0;

    igArenaMemoryPool_CheckBlock((igArenaMemoryPoolView *)arg0, (TaggedBlockHeader *)arg1, extra2);
    if (*(int *)((char *)arg0 + 184) > 0) {
        temp_a0 = *(int *)((char *)arg0 + 188);
        if ((temp_a0 > 0) && !(*arg1 & 1) && (temp_a0 > 0)) {
            Memory_PrintPoolStatistics(0, arg0);
            if (DAT_00554cb0 == 0) {
                temp_v0 = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, arg1, &text_E37_Corrupted_header[0]);
                if ((temp_v0 != 1) && (temp_v0 == 2)) {
                    DAT_00554cb0 = 1;
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
    if (state->top == 0 || state->top == state->bins[1]) {
        return;
    }
    if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && (state->pageSize & (state->pageSize - 1)) != 0 && self->_messageLevel > 0) {
        Memory_PrintPoolStatistics(0, self);
        if (GPR_00554cb4 == 0) {
            r = igReportNotice(DAT_004fbb00, DAT_004fbb20);
            if (r != 1 && r == 2) {
                GPR_00554cb4 = 1;
            }
        }
    }
    if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !((state->maxFast & ~3) <= (91 < self->_smallestChunkSize ? self->_smallestChunkSize : 88)) && self->_messageLevel > 0) {
        Memory_PrintPoolStatistics(0, self);
        if (GPR_00554cb8 == 0) {
            r = igReportNotice(DAT_004fbb00, DAT_004fbb60);
            if (r != 1 && r == 2) {
                GPR_00554cb8 = 1;
            }
        }
    }
    maxFastBin = (state->maxFast >> 3) - 2;
    for (i = 0; i < 10; ++i) {
        p = state->fastBins[i];
        if (i > maxFastBin) {
            if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && p != 0 && self->_messageLevel > 0) {
                Memory_PrintPoolStatistics(0, self);
                if (GPR_00554cbc == 0) {
                    r = igReportNotice(DAT_004fbb00, DAT_004fbba0);
                    if (r != 1 && r == 2) {
                        GPR_00554cbc = 1;
                    }
                }
            }
        }
        if (p != 0) {
            if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !IS_ARENA_CHUNK(self, p) && self->_messageLevel > 0) {
                Memory_PrintPoolStatistics(0, self);
                if (GPR_00554cc0 == 0) {
                    r = igReportNotice(DAT_004fbc00, DAT_004fbc40, p);
                    if (r != 1 && r == 2) {
                        GPR_00554cc0 = 1;
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
                if (GPR_00554cc4 == 0) {
                    r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, p, DAT_004fbc60);
                    if (r != 1 && r == 2) {
                        GPR_00554cc4 = 1;
                    }
                }
            }
            next = chunkLinks(p)->forward;
            if (next != 0) {
                if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !IS_ARENA_CHUNK(self, next) && self->_messageLevel > 0) {
                    Memory_PrintPoolStatistics(0, self);
                    if (GPR_00554cc8 == 0) {
                        r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, p, DAT_004fbcb0);
                        if (r != 1 && r == 2) {
                            GPR_00554cc8 = 1;
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
            if (GPR_00554ccc == 0) {
                r = igReportNotice(DAT_004fbb00, DAT_004fbce0);
                if (r != 1 && r == 2) {
                    GPR_00554ccc = 1;
                }
            }
        }
    } else if (!(state->maxFast & 2)) {
        if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && total != 0 && self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (GPR_00554cd0 == 0) {
                r = igReportNotice(DAT_004fbb00, DAT_004fbd20);
                if (r != 1 && r == 2) {
                    GPR_00554cd0 = 1;
                }
            }
        }
    }
    for (i = 1; i < 96; ++i) {
        b = (TaggedBlockHeader *)state->bins[i];
        if (i >= 2) {
            binbit = state->binMap[i >> 5] & (1 << (i & 0x1f));
            empty = chunkLinks(b)->back == b;
            if (!binbit) {
                if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !empty && self->_messageLevel > 0) {
                    Memory_PrintPoolStatistics(0, self);
                    if (GPR_00554cd4 == 0) {
                        r = igReportNotice(DAT_004fbb00, DAT_004fbd70);
                        if (r != 1 && r == 2) {
                            GPR_00554cd4 = 1;
                        }
                    }
                }
            } else if (!empty) {
                if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !binbit && self->_messageLevel > 0) {
                    Memory_PrintPoolStatistics(0, self);
                    if (GPR_00554cd8 == 0) {
                        r = igReportNotice(DAT_004fbb00, DAT_004fbdb0);
                        if (r != 1 && r == 2) {
                            GPR_00554cd8 = 1;
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
                    if (GPR_00554cdc == 0) {
                        r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, p, DAT_004fbe00);
                        if (r != 1 && r == 2) {
                            GPR_00554cdc = 1;
                        }
                    }
                }
                if (size >= 256) {
                    if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !(chunkLinks(p)->back == b || chunkBytes(chunkLinks(p)->back) >= chunkBytes(p)) && self->_messageLevel > 0) {
                        Memory_PrintPoolStatistics(0, self);
                        if (GPR_00554ce0 == 0) {
                            r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, p, DAT_004fbe50);
                            if (r != 1 && r == 2) {
                                GPR_00554ce0 = 1;
                            }
                        }
                    }
                }
            }
            for (q = (TaggedBlockHeader *)((char *)p + chunkBytes(p)); (char *)q != state->top && ((TaggedBlockHeader *)((char *)q + chunkBytes(q)))->used && chunkBytes(q) >= ((self->_smallestChunkSize + 7) & ~7); q = (TaggedBlockHeader *)((char *)q + chunkBytes(q))) {
                igArenaMemoryPool_CheckInUseChunk(self, q);
            }
        }
    }
    if (self->_heapIntegrityCheckLevel > 0) {
        igArenaMemoryPool_CheckChunk(self, (TaggedBlockHeader *)state->top);
    }
}
