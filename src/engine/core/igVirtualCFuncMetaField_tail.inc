int Gap__Core__igVirtualCFuncMetaField__vfunc_56(int arg0, int arg1, int arg2) {
    int sp1C;

    sp1C = 0;
    sscanf(arg2, &text_0x_08x_n[0], arg1, &sp1C);
    return sp1C;
}

void Gap__Core__igVirtualCFuncMetaField__vfunc_57(int *arg0, int arg1, int *arg2) {
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

int Gap__Core__igVirtualCFuncMetaField__vfunc_25(void) {
    return 4;
}

void igVirtualCFuncMetaField_SetToDefault(void *arg0, int arg1) {
 if (arg1 != 0) {
int a = **(int **)((char *)(arg0) + 32);
 int b = *(int *)(arg1 + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
 ((igMetaFieldView *)arg0)->vfunc_24(arg1, b + a);
}
}

void Gap__Core__igVirtualCFuncMetaField__vfunc_30(int *arg0, int arg1) {
    if (arg1 != 0) {
        int *c = (int *)arg0[8];
        int u = *(int *)(arg1 + *(int *)((char *)((void * *)g_objectSystem)[0] + 916));
        ((igMetaFieldView *)arg0)->vfunc_24(arg1, u + *c);
    }
}

/* igVirtualCFuncMetaField override of the igMetaField slot at vtable +0x6c (slot 27): returns 4.
 * Base igMetaField returns -1 and the ref fields also return 4. The receiver is not read. */
int Gap__Core__igVirtualCFuncMetaField__vfunc_27(void) {
    return 4;
}

static inline int isFreeChunk(TaggedBlockHeader *h) { if (h->big == 1) { return h->extraUsed; } return 0; }

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

/* Chunk size in bytes: the 19-bit size (12 more bits in the third word when `big`), rounded to a word, plus the
 * header words. */
static inline unsigned int chunkBytes(TaggedBlockHeader *h) {
    unsigned int size = h->size;
    if (h->big == 1) {
        size += h->sizeHigh << 19;
    }
    size = (size + 3) & ~3;
    return size + (h->words + 1) * 4;
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

void FUN_003105c0(igArenaMemoryPoolView *self, TaggedBlockHeader *h, int requested) {
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

void FUN_00310b60(void *arg0, unsigned char *arg1, int extra2) {
    int temp_a0;
    int temp_v0;

    FUN_003105c0((igArenaMemoryPoolView *)arg0, (TaggedBlockHeader *)arg1, extra2);
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

