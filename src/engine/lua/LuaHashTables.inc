/* The binding's hash tables. Each grows to twice its buckets when it holds more entries than
 * buckets and shrinks to half, down to its minimum, when it holds fewer than half; it allocates
 * its buckets on the first insertion and frees them when the last entry goes. */
static inline unsigned int LuaHashTable_Bucket(unsigned int key, unsigned int bucketCount, unsigned int shift) {
    return (bucketCount - 1) & (key ^ (key >> shift));
}

void LuaFieldTable_Insert(LuaHashLink *link) {
    LuaFieldTable_Resize();
    LuaFieldTable_Link(link, g_luaFieldBuckets, g_luaFieldBucketCount, g_luaFieldBucketShift);
    g_luaFieldCount++;
}

void LuaFieldTable_Link(LuaHashLink *link, LuaHashLink **buckets, unsigned int bucketCount, unsigned int shift) {
    LuaHashLink **bucket = &buckets[LuaHashTable_Bucket(link->key, bucketCount, shift)];

    link->next = *bucket;
    if (*bucket != 0) {
        (*bucket)->prev = link;
    }
    link->prev = 0;
    *bucket = link;
}

void LuaFieldTable_Resize(void) {
    unsigned int oldShift;
    unsigned int shift;
    unsigned int bucketCount;
    unsigned int size;
    LuaHashLink **buckets;
    unsigned int index;
    LuaHashLink *entry;
    LuaHashLink *next;

    if (g_luaFieldBuckets == 0) {
        g_luaFieldBuckets = (LuaHashLink **)Memory_AllocateDefaultBuffer(g_luaFieldBucketCount * 4);
        memset(g_luaFieldBuckets, 0, g_luaFieldBucketCount * 4);
        return;
    }
    if (g_luaFieldTableBusy == 0) {
        if (g_luaFieldCount == 0) {
            Memory_FreeBufferAliasA(g_luaFieldBuckets);
            g_luaFieldBuckets = 0;
            g_luaFieldBucketCount = 0x400;
            return;
        }
        oldShift = g_luaFieldBucketShift;
        shift = oldShift;
        if (g_luaFieldBucketCount < g_luaFieldCount) {
            shift = oldShift + 1;
        } else if (g_luaFieldCount < (g_luaFieldBucketCount >> 1) && oldShift > 10) {
            shift = oldShift - 1;
        }
        if (shift != oldShift) {
            bucketCount = 1 << shift;
            size = bucketCount * 4;
            buckets = (LuaHashLink **)Memory_AllocateDefaultBuffer(size);
            memset(buckets, 0, size);
            for (index = 0; index < g_luaFieldBucketCount; index++) {
                for (entry = g_luaFieldBuckets[index]; entry != 0; entry = next) {
                    next = entry->next;
                    LuaFieldTable_Link(entry, buckets, bucketCount, shift);
                }
            }
            g_luaFieldBucketCount = bucketCount;
            g_luaFieldBucketShift = shift;
            Memory_FreeBufferAliasA(g_luaFieldBuckets);
            g_luaFieldBuckets = buckets;
        }
    }
}

void LuaFunctionTable_Insert(LuaHashLink *link) {
    LuaFunctionTable_Resize();
    LuaFunctionTable_Link(link, g_luaFunctionBuckets, g_luaFunctionBucketCount, g_luaFunctionBucketShift);
    g_luaFunctionCount++;
}

void LuaFunctionTable_Link(LuaHashLink *link, LuaHashLink **buckets, unsigned int bucketCount, unsigned int shift) {
    LuaHashLink **bucket = &buckets[LuaHashTable_Bucket(link->key, bucketCount, shift)];

    link->next = *bucket;
    if (*bucket != 0) {
        (*bucket)->prev = link;
    }
    link->prev = 0;
    *bucket = link;
}

void LuaFunctionTable_Resize(void) {
    unsigned int oldShift;
    unsigned int shift;
    unsigned int bucketCount;
    unsigned int size;
    LuaHashLink **buckets;
    unsigned int index;
    LuaHashLink *entry;
    LuaHashLink *next;

    if (g_luaFunctionBuckets == 0) {
        g_luaFunctionBuckets = (LuaHashLink **)Memory_AllocateDefaultBuffer(g_luaFunctionBucketCount * 4);
        memset(g_luaFunctionBuckets, 0, g_luaFunctionBucketCount * 4);
        return;
    }
    if (g_luaFunctionTableBusy == 0) {
        if (g_luaFunctionCount == 0) {
            Memory_FreeBufferAliasA(g_luaFunctionBuckets);
            g_luaFunctionBuckets = 0;
            g_luaFunctionBucketCount = 0x100;
            return;
        }
        oldShift = g_luaFunctionBucketShift;
        shift = oldShift;
        if (g_luaFunctionBucketCount < g_luaFunctionCount) {
            shift = oldShift + 1;
        } else if (g_luaFunctionCount < (g_luaFunctionBucketCount >> 1) && oldShift > 8) {
            shift = oldShift - 1;
        }
        if (shift != oldShift) {
            bucketCount = 1 << shift;
            size = bucketCount * 4;
            buckets = (LuaHashLink **)Memory_AllocateDefaultBuffer(size);
            memset(buckets, 0, size);
            for (index = 0; index < g_luaFunctionBucketCount; index++) {
                for (entry = g_luaFunctionBuckets[index]; entry != 0; entry = next) {
                    next = entry->next;
                    LuaFunctionTable_Link(entry, buckets, bucketCount, shift);
                }
            }
            g_luaFunctionBucketCount = bucketCount;
            g_luaFunctionBucketShift = shift;
            Memory_FreeBufferAliasA(g_luaFunctionBuckets);
            g_luaFunctionBuckets = buckets;
        }
    }
}

void LuaClassTable_Insert(LuaHashLink *link) {
    LuaClassTable_Resize();
    LuaClassTable_Link(link, g_luaClassBuckets, g_luaClassBucketCount, g_luaClassBucketShift);
    g_luaClassCount++;
}

void LuaClassTable_Link(LuaHashLink *link, LuaHashLink **buckets, unsigned int bucketCount, unsigned int shift) {
    LuaHashLink **bucket = &buckets[LuaHashTable_Bucket(link->key, bucketCount, shift)];

    link->next = *bucket;
    if (*bucket != 0) {
        (*bucket)->prev = link;
    }
    link->prev = 0;
    *bucket = link;
}

void LuaClassTable_Resize(void) {
    unsigned int oldShift;
    unsigned int shift;
    unsigned int bucketCount;
    unsigned int size;
    LuaHashLink **buckets;
    unsigned int index;
    LuaHashLink *entry;
    LuaHashLink *next;

    if (g_luaClassBuckets == 0) {
        g_luaClassBuckets = (LuaHashLink **)Memory_AllocateDefaultBuffer(g_luaClassBucketCount * 4);
        memset(g_luaClassBuckets, 0, g_luaClassBucketCount * 4);
        return;
    }
    if (g_luaClassTableBusy == 0) {
        if (g_luaClassCount == 0) {
            Memory_FreeBufferAliasA(g_luaClassBuckets);
            g_luaClassBuckets = 0;
            g_luaClassBucketCount = 128;
            return;
        }
        oldShift = g_luaClassBucketShift;
        shift = oldShift;
        if (g_luaClassBucketCount < g_luaClassCount) {
            shift = oldShift + 1;
        } else if (g_luaClassCount < (g_luaClassBucketCount >> 1) && oldShift > 7) {
            shift = oldShift - 1;
        }
        if (shift != oldShift) {
            bucketCount = 1 << shift;
            size = bucketCount * 4;
            buckets = (LuaHashLink **)Memory_AllocateDefaultBuffer(size);
            memset(buckets, 0, size);
            for (index = 0; index < g_luaClassBucketCount; index++) {
                for (entry = g_luaClassBuckets[index]; entry != 0; entry = next) {
                    next = entry->next;
                    LuaClassTable_Link(entry, buckets, bucketCount, shift);
                }
            }
            g_luaClassBucketCount = bucketCount;
            g_luaClassBucketShift = shift;
            Memory_FreeBufferAliasA(g_luaClassBuckets);
            g_luaClassBuckets = buckets;
        }
    }
}

void LuaPropertyTable_Link(LuaPropertyLink *link, LuaProperty **buckets, unsigned int bucketCount, unsigned int shift) {
    buckets += LuaHashTable_Bucket(link->key, bucketCount, shift);
    link->next = *buckets;
    if (*buckets != 0) {
        (*buckets)->LuaPropertyLink::prev = static_cast<LuaProperty *>(link);
    }
    link->prev = 0;
    *buckets = static_cast<LuaProperty *>(link);
}

void LuaPropertyTable_Resize(void) {
    unsigned int oldShift;
    unsigned int shift;
    unsigned int bucketCount;
    unsigned int size;
    LuaProperty **buckets;
    unsigned int index;
    LuaProperty *entry;
    LuaProperty *next;

    if (g_luaPropertyBuckets == 0) {
        g_luaPropertyBuckets = (LuaProperty **)Memory_AllocateDefaultBuffer(g_luaPropertyBucketCount * 4);
        memset(g_luaPropertyBuckets, 0, g_luaPropertyBucketCount * 4);
        return;
    }
    if (g_luaPropertyTableBusy == 0) {
        if (g_luaPropertyCount == 0) {
            Memory_FreeBufferAliasA(g_luaPropertyBuckets);
            g_luaPropertyBuckets = 0;
            g_luaPropertyBucketCount = 256;
            return;
        }
        oldShift = g_luaPropertyBucketShift;
        shift = oldShift;
        if (g_luaPropertyBucketCount < g_luaPropertyCount) {
            shift = oldShift + 1;
        } else if (g_luaPropertyCount < (g_luaPropertyBucketCount >> 1) && oldShift > 8) {
            shift = oldShift - 1;
        }
        if (shift != oldShift) {
            bucketCount = 1 << shift;
            size = bucketCount * 4;
            buckets = (LuaProperty **)Memory_AllocateDefaultBuffer(size);
            memset(buckets, 0, size);
            for (index = 0; index < g_luaPropertyBucketCount; index++) {
                for (entry = g_luaPropertyBuckets[index]; entry != 0; entry = next) {
                    next = entry->LuaPropertyLink::next;
                    LuaPropertyTable_Link(&static_cast<LuaPropertyLink &>(*entry), buckets, bucketCount, shift);
                }
            }
            g_luaPropertyBucketCount = bucketCount;
            g_luaPropertyBucketShift = shift;
            Memory_FreeBufferAliasA(g_luaPropertyBuckets);
            g_luaPropertyBuckets = buckets;
        }
    }
}

void LuaConstantTable_Link(LuaHashLink *link, LuaHashLink **buckets, unsigned int bucketCount, unsigned int shift) {
    LuaHashLink **bucket = &buckets[LuaHashTable_Bucket(link->key, bucketCount, shift)];

    link->next = *bucket;
    if (*bucket != 0) {
        (*bucket)->prev = link;
    }
    link->prev = 0;
    *bucket = link;
}

void LuaConstantTable_Resize(void) {
    unsigned int oldShift;
    unsigned int shift;
    unsigned int bucketCount;
    unsigned int size;
    LuaHashLink **buckets;
    unsigned int index;
    LuaHashLink *entry;
    LuaHashLink *next;

    if (g_luaConstantBuckets == 0) {
        g_luaConstantBuckets = (LuaHashLink **)Memory_AllocateDefaultBuffer(g_luaConstantBucketCount * 4);
        memset(g_luaConstantBuckets, 0, g_luaConstantBucketCount * 4);
        return;
    }
    if (g_luaConstantTableBusy == 0) {
        if (g_luaConstantCount == 0) {
            Memory_FreeBufferAliasA(g_luaConstantBuckets);
            g_luaConstantBuckets = 0;
            g_luaConstantBucketCount = 256;
            return;
        }
        oldShift = g_luaConstantBucketShift;
        shift = oldShift;
        if (g_luaConstantBucketCount < g_luaConstantCount) {
            shift = oldShift + 1;
        } else if (g_luaConstantCount < (g_luaConstantBucketCount >> 1) && oldShift > 8) {
            shift = oldShift - 1;
        }
        if (shift != oldShift) {
            bucketCount = 1 << shift;
            size = bucketCount * 4;
            buckets = (LuaHashLink **)Memory_AllocateDefaultBuffer(size);
            memset(buckets, 0, size);
            for (index = 0; index < g_luaConstantBucketCount; index++) {
                for (entry = g_luaConstantBuckets[index]; entry != 0; entry = next) {
                    next = entry->next;
                    LuaConstantTable_Link(entry, buckets, bucketCount, shift);
                }
            }
            g_luaConstantBucketCount = bucketCount;
            g_luaConstantBucketShift = shift;
            Memory_FreeBufferAliasA(g_luaConstantBuckets);
            g_luaConstantBuckets = buckets;
        }
    }
}

void LuaEnumTable_Link(LuaHashLink *link, LuaHashLink **buckets, unsigned int bucketCount, unsigned int shift) {
    LuaHashLink **bucket = &buckets[LuaHashTable_Bucket(link->key, bucketCount, shift)];

    link->next = *bucket;
    if (*bucket != 0) {
        (*bucket)->prev = link;
    }
    link->prev = 0;
    *bucket = link;
}

void LuaEnumTable_Resize(void) {
    unsigned int oldShift;
    unsigned int shift;
    unsigned int bucketCount;
    unsigned int size;
    LuaHashLink **buckets;
    unsigned int index;
    LuaHashLink *entry;
    LuaHashLink *next;

    if (g_luaEnumBuckets == 0) {
        g_luaEnumBuckets = (LuaHashLink **)Memory_AllocateDefaultBuffer(g_luaEnumBucketCount * 4);
        memset(g_luaEnumBuckets, 0, g_luaEnumBucketCount * 4);
        return;
    }
    if (g_luaEnumTableBusy == 0) {
        if (g_luaEnumCount == 0) {
            Memory_FreeBufferAliasA(g_luaEnumBuckets);
            g_luaEnumBuckets = 0;
            g_luaEnumBucketCount = 16;
            return;
        }
        oldShift = g_luaEnumBucketShift;
        shift = oldShift;
        if (g_luaEnumBucketCount < g_luaEnumCount) {
            shift = oldShift + 1;
        } else if (g_luaEnumCount < (g_luaEnumBucketCount >> 1) && oldShift > 4) {
            shift = oldShift - 1;
        }
        if (shift != oldShift) {
            bucketCount = 1 << shift;
            size = bucketCount * 4;
            buckets = (LuaHashLink **)Memory_AllocateDefaultBuffer(size);
            memset(buckets, 0, size);
            for (index = 0; index < g_luaEnumBucketCount; index++) {
                for (entry = g_luaEnumBuckets[index]; entry != 0; entry = next) {
                    next = entry->next;
                    LuaEnumTable_Link(entry, buckets, bucketCount, shift);
                }
            }
            g_luaEnumBucketCount = bucketCount;
            g_luaEnumBucketShift = shift;
            Memory_FreeBufferAliasA(g_luaEnumBuckets);
            g_luaEnumBuckets = buckets;
        }
    }
}

void LuaEnumTable_Remove(LuaHashLink *link) {
    LuaHashLink **bucket;

    if (link->next != 0) {
        link->next->prev = link->prev;
    }
    if (link->prev != 0) {
        link->prev->next = link->next;
    } else {
        bucket = &g_luaEnumBuckets[LuaHashTable_Bucket(link->key, g_luaEnumBucketCount, g_luaEnumBucketShift)];
        if (*bucket == link) {
            *bucket = link->next;
        } else {
            return;
        }
    }
    g_luaEnumCount--;
    LuaEnumTable_Resize();
}

void LuaConstantTable_Remove(LuaHashLink *link) {
    LuaHashLink **bucket;

    if (link->next != 0) {
        link->next->prev = link->prev;
    }
    if (link->prev != 0) {
        link->prev->next = link->next;
    } else {
        bucket = &g_luaConstantBuckets[LuaHashTable_Bucket(link->key, g_luaConstantBucketCount, g_luaConstantBucketShift)];
        if (*bucket == link) {
            *bucket = link->next;
        } else {
            return;
        }
    }
    g_luaConstantCount--;
    LuaConstantTable_Resize();
}

void LuaPropertyTable_Remove(LuaPropertyLink *link) {
    LuaProperty **bucket;
    LuaProperty *property;
    unsigned int index;
    unsigned int key;

    if (link->next != 0) {
        link->next->LuaPropertyLink::prev = link->prev;
    }
    if (link->prev != 0) {
        link->prev->LuaPropertyLink::next = link->next;
    } else {
        key = link->key;
        index = (g_luaPropertyBucketCount - 1) & (key ^ (key >> g_luaPropertyBucketShift));
        property = static_cast<LuaProperty *>(link);
        bucket = &g_luaPropertyBuckets[index];
        if (*bucket == property) {
            *bucket = link->next;
        } else {
            return;
        }
    }
    g_luaPropertyCount--;
    LuaPropertyTable_Resize();
}

void LuaClassTable_Remove(LuaHashLink *link) {
    LuaHashLink **bucket;

    if (link->next != 0) {
        link->next->prev = link->prev;
    }
    if (link->prev != 0) {
        link->prev->next = link->next;
    } else {
        bucket = &g_luaClassBuckets[LuaHashTable_Bucket(link->key, g_luaClassBucketCount, g_luaClassBucketShift)];
        if (*bucket == link) {
            *bucket = link->next;
        } else {
            return;
        }
    }
    g_luaClassCount--;
    LuaClassTable_Resize();
}

void LuaFunctionTable_Remove(LuaHashLink *link) {
    LuaHashLink **bucket;

    if (link->next != 0) {
        link->next->prev = link->prev;
    }
    if (link->prev != 0) {
        link->prev->next = link->next;
    } else {
        bucket = &g_luaFunctionBuckets[LuaHashTable_Bucket(link->key, g_luaFunctionBucketCount, g_luaFunctionBucketShift)];
        if (*bucket == link) {
            *bucket = link->next;
        } else {
            return;
        }
    }
    g_luaFunctionCount--;
    LuaFunctionTable_Resize();
}

void LuaFieldTable_Remove(LuaHashLink *link) {
    LuaHashLink **bucket;

    if (link->next != 0) {
        link->next->prev = link->prev;
    }
    if (link->prev != 0) {
        link->prev->next = link->next;
    } else {
        bucket = &g_luaFieldBuckets[LuaHashTable_Bucket(link->key, g_luaFieldBucketCount, g_luaFieldBucketShift)];
        if (*bucket == link) {
            *bucket = link->next;
        } else {
            return;
        }
    }
    g_luaFieldCount--;
    LuaFieldTable_Resize();
}
