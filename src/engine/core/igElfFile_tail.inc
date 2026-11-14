static void igElfFile_Swap16(unsigned char *p) {
    unsigned short x;
    ((unsigned char *)&x)[0] = p[1];
    ((unsigned char *)&x)[1] = p[0];
    *(unsigned short *)p = x;
}

static void igElfFile_Swap32(unsigned char *p) {
    union { unsigned char b[4]; int w; } swapped;
    swapped.b[0] = p[3];
    swapped.b[1] = p[2];
    swapped.b[2] = p[1];
    swapped.b[3] = p[0];
    *(int *)p = swapped.w;
}

void igElfFile_SwapHeader(unsigned char *p) {
    igElfFile_Swap16(p + 16);
    igElfFile_Swap16(p + 18);
    igElfFile_Swap32(p + 20);
    igElfFile_Swap32(p + 24);
    igElfFile_Swap32(p + 28);
    igElfFile_Swap32(p + 32);
    igElfFile_Swap32(p + 36);
    igElfFile_Swap16(p + 40);
    igElfFile_Swap16(p + 42);
    igElfFile_Swap16(p + 44);
    igElfFile_Swap16(p + 46);
    igElfFile_Swap16(p + 48);
    igElfFile_Swap16(p + 50);
}

void igElfFile_SwapSectionHeaders(unsigned char *headers, int count) {
    unsigned char *p = headers;
    int n = count;
    for (; n > 0; n--) {
        igElfFile_Swap32(p);
        igElfFile_Swap32(p + 4);
        igElfFile_Swap32(p + 8);
        igElfFile_Swap32(p + 12);
        igElfFile_Swap32(p + 16);
        igElfFile_Swap32(p + 20);
        igElfFile_Swap32(p + 24);
        igElfFile_Swap32(p + 28);
        igElfFile_Swap32(p + 32);
        igElfFile_Swap32(p + 36);
        p += 40;
    }
}

void igElfFile_SwapSymbols(unsigned char *symbols, int count) {
    unsigned char *p = symbols;
    int n = count;
    for (; n > 0; n--) {
        igElfFile_Swap32(p);
        igElfFile_Swap32(p + 4);
        igElfFile_Swap32(p + 8);
        igElfFile_Swap16(p + 14);
        p += 16;
    }
}

void igElfFile_Reset(igElfFile *self) {
    igProgramFile_Reset((igProgramFile *)self);
    memset(self->_header, 0, 0x34);
    self->_sectionHeaderStringTableSize = 0;
    self->_sectionHeaderStringTable = 0;
    self->_sectionHeaderCount = 0;
    self->_sectionHeaders = 0;
    self->_symbolStringTableSize = 0;
    self->_symbolStringTable = 0;
    self->_symbolCount = 0;
    self->_symbols = 0;
}

void igElfFile_Open(int *result, ElfFileView *self, const char *path) {
    if (igProgramFile_Open((igProgramFile *)self, path) == g_resultFailure) {
        *result = g_resultFailure.v;
        return;
    }
    if (self->stream->Read(self->magic, 0x34, 1) != 1) {
        igReport_Printf(text_Error_reading_percent_s, self->path);
        igReport_Flush();
        self->Close();
        *result = g_resultFailure.v;
        return;
    }
    int hostEndian = 1;
    int fileEndian = self->endian;
    if (g_byteOrderProbe == 0x12) {
        hostEndian = 2;
    }
    if (fileEndian != hostEndian) {
        igElfFile_SwapHeader(self->magic);
    }
    if (self->magic[0] != 0x7F || self->magic[1] != 'E' || self->magic[2] != 'L' || self->magic[3] != 'F') {
        igReport_Printf((const char *)text_Invalid_file_signature_percent_s, self->path);
        igReport_Flush();
        self->Close();
        *result = g_resultFailure.v;
        return;
    }
    int sectionOffset = self->sectionHeaderOffset;
    if (sectionOffset == 0) {
        igReport_Printf((const char *)text_No_section_headers_in_percent_s, self->path, sectionOffset);
        igReport_Flush();
        self->Close();
        *result = g_resultFailure.v;
        return;
    }
    if (self->Load(sectionOffset, self->sectionHeaderCount * self->sectionHeaderEntrySize, &self->sectionHeaders) == g_resultFailure) {
        *result = g_resultFailure.v;
        return;
    }
    if (g_byteOrderProbe == 0x12) {
        hostEndian = 2;
    } else {
        hostEndian = 1;
    }
    if (self->endian != hostEndian) {
        igElfFile_SwapSectionHeaders((unsigned char *)self->sectionHeaders, self->sectionHeaderCount);
    }
    self->sectionCount = self->sectionHeaderCount;
    if (self->sectionNameIndex != 0) {
        ElfSection *section = igElfFile_GetSectionHeader(self, self->sectionNameIndex);
        if (section != 0 && section->type == 3) {
            self->sectionNamesSize = section->size;
            if (self->Load(section->offset, section->size, &self->sectionNames) == g_resultFailure) {
                *result = g_resultFailure.v;
                return;
            }
        }
    }
    *result = g_resultSuccess.v;
}

void igElfFile_Close(int *result, ElfFileView *self) {
    if (self->sectionHeaders != 0) {
        igObject_FreeMemory((int)self, (int)self->sectionHeaders);
    }
    if (self->sectionNames != 0) {
        igObject_FreeMemory((int)self, (int)self->sectionNames);
    }
    if (self->strings != 0) {
        igObject_FreeMemory((int)self, (int)self->strings);
    }
    if (self->symbols != 0) {
        igObject_FreeMemory((int)self, (int)self->symbols);
    }
    igProgramFile_Close(result, self);
}

ElfSection *igElfFile_GetSectionHeader(ElfFileView *self, int index) {
    char *base = (char *)self->sectionHeaders;
    if (base != 0 && index >= 0 && index <= self->sectionCount) {
        return (ElfSection *)(base + index * self->sectionHeaderEntrySize);
    }
    return 0;
}

int igElfFile_FindSectionByType(ElfFileView *self, int type, int nth) {
    int i;
    int t;
    for (i = 0; i < self->sectionCount; i++) {
        t = igElfFile_GetSectionHeader(self, i)->type;
        if (t == type) {
            if (nth-- == 0) {
                return i;
            }
        }
    }
    return -1;
}

int igElfFile_GetSymbol(void *self, int index) {
    char *base = (char *)((ElfFileView *)self)->symbols;
    if (base != 0 && index >= 0 && index <= ((ElfFileView *)self)->symbolCount) return (int)(base + index*16); return 0;
}

/* Loads the symbol table (the first SHT_SYMTAB section) and its string table, which is the SHT_STRTAB
 * section after it, before it or two after it that is not the section-name table; swaps the symbols
 * when the file's byte order is not the machine's. */
igResult igElfFile_LoadSymbols(ElfFileView *self) {
    int index = igElfFile_FindSectionByType(self, 2, 0);
    ElfSection *symbols;
    ElfSection *before;
    ElfSection *after;
    ElfSection *next;
    int expected;
    if (index == -1) {
        igReport_Printf(DAT_004fde00, self->path);
        igReport_Flush();
        self->Close();
        return g_resultFailure;
    }
    symbols = igElfFile_GetSectionHeader(self, index);
    before = igElfFile_GetSectionHeader(self, index - 1);
    after = igElfFile_GetSectionHeader(self, index + 1);
    next = igElfFile_GetSectionHeader(self, index + 2);
    if (after != 0 && after->type == 3 && after->size != self->sectionNamesSize) {
        self->stringsSize = after->size;
        if (self->Load(after->offset, after->size, &self->strings) == g_resultFailure) {
            return g_resultFailure;
        }
    } else if (before != 0 && before->type == 3 && before->size != self->sectionNamesSize) {
        self->stringsSize = before->size;
        if (self->Load(before->offset, before->size, &self->strings) == g_resultFailure) {
            return g_resultFailure;
        }
    } else if (next != 0 && next->type == 3 && next->size != self->sectionNamesSize) {
        self->stringsSize = next->size;
        if (self->Load(next->offset, next->size, &self->strings) == g_resultFailure) {
            return g_resultFailure;
        }
    } else {
        igReport_Printf(DAT_004fde20, self->path);
        igReport_Flush();
        self->Close();
        return g_resultFailure;
    }
    self->symbolCount = (unsigned)symbols->size >> 4;
    if (self->Load(symbols->offset, symbols->size, &self->symbols) == g_resultFailure) {
        return g_resultFailure;
    }
    expected = (g_byteOrderProbe == 18) ? 2 : 1;
    if (self->endian != expected) {
        igElfFile_SwapSymbols((unsigned char *)self->symbols, self->symbolCount);
    }
    return g_resultSuccess;
}

static inline void prepareSink(igSymbolTableView *table, int count, unsigned low, unsigned top) {
    igSymbolTable_SetCapacity((int)table, count);
    igSymbolTable_SetHashCapacity((int)table, count * 4);
    igSymbolTable_SetAddressRange(table, low & ~1023, top);
    igSymbolTable_ReserveStorage(table);
}

/* Fills `table` with the file's symbols (only global, weak and local functions when
 * `functionsOnly`), sized and address-ranged from a first pass over them. */
igResult igElfFile_LoadSymbolTable(ElfFileView *self, igSymbolTableView *table, int functionsOnly) {
    char text[264];
    unsigned low;
    int j;
    int i;
    ElfSymbol *entry;
    int count;
    unsigned high;
    low = -1U;
    high = 0;
    count = 0;
    if (self->symbolCount == 0) {
        if (self->LoadSymbols() == g_resultFailure) {
            return g_resultFailure;
        }
    }
    if (self->symbolCount == 0) {
        igReport_Printf(text_No_symbols_in_s, self->path);
        igReport_Flush();
        return g_resultFailure;
    }
    if (functionsOnly == 0) {
        count = self->symbolCount;
    }
    for (i = 0; i < self->symbolCount; i++) {
        ElfSymbol *sym = (ElfSymbol *)igElfFile_GetSymbol(self, i);
        unsigned value = sym->value;
        if (value == 0 || value == -1U) {
            continue;
        }
        if (functionsOnly != 0) {
            int info = sym->info;
            int bind = info >> 4;
            if (!(!((unsigned)(bind - STB_GLOBAL) > 1) || bind == STB_LOCAL)) {
                continue;
            }
            if ((info & 15) != STT_FUNC) {
                continue;
            }
            count++;
        }
        if (value < low) {
            low = value;
        }
        if (high < value) {
            high = value;
        }
    }
    high = (high & ~1023) + 1024;
    prepareSink(table, count, low, high);
    for (j = 0; j < self->symbolCount; j++) {
        entry = (ElfSymbol *)igElfFile_GetSymbol(self, j);
        if (functionsOnly != 0) {
            int info = entry->info;
            int bind = info >> 4;
            if (bind == STB_GLOBAL) {
            } else if (bind == STB_WEAK) {
            } else if (bind != STB_LOCAL) {
                continue;
            }
            if ((info & 15) != STT_FUNC) {
                continue;
            }
        }
        self->Demangle((char *)self->strings + entry->name, text, 255, 0);
        table->AddSymbol(text, (void *)entry->value, entry->size, 0);
    }
    return g_resultSuccess;
}

void igElfFile_DemangleName(const char *in, char *out, int size) {
    char *cursor = (char *)in;
    char inner[256];
    int pointers = 0;
    int copy;
    int parts;
    int length;
    int advance;
    int limit;
    int c;
    char *open;
    while ((c = *cursor) != 0) {
        char kind = c;
        if (kind == 'P') {
            cursor++;
            pointers++;
        } else if (kind == 'Q') {
            cursor++;
            parts = *cursor - '0';
            if (parts > 0 && parts < 10) {
                cursor++;
                while (parts-- != 0) {
                    length = 0;
                    while ((c = *cursor) >= '0' && c <= 57) {
                        length = c - '0' + length * 10;
                        cursor++;
                    }
                    limit = size - 1;
                    copy = length;
                    if (copy > limit) {
                        copy = limit;
                    }
                    strncpy(out, cursor, copy);
                    out[copy] = 0;
                    open = strchr(out, '<');
                    if (open != 0) {
                        length = open - out;
                        memcpy(inner, open + 1, copy + 1 - length);
                        advance = length + 1;
                        if (advance > 254) {
                            advance = 254;
                        }
                        if (advance > size) {
                            advance = size;
                        }
                        out += advance;
                        size -= advance;
                        *out = 0;
                        igElfFile_DemangleName(inner, out, size);
                        advance = strlen(out);
                        size -= advance;
                        out += advance;
                        if (size > 1) {
                            *out = '>';
                            size--;
                            out++;
                        }
                        if (size > 1) {
                            *out = 0;
                            size--;
                            out++;
                        }
                    } else {
                        cursor += length;
                        out += copy;
                        size -= copy;
                    }
                    if (parts != 0 && size > 2) {
                        size -= 2;
                        out[0] = ':';
                        out[1] = ':';
                        out += 2;
                    }
                }
            }
            while (((pointers != 0) ^ 1) == 0 && size > 1) {
                *out = '*';
                size--;
                pointers--;
                out++;
                *out = 0;
            }
            continue;
        } else {
            cursor++;
        }
    }
    *out = 0;
}

void igElfFile_Demangle(int *result, void *self, char *mangled, char *out, int size) {
    char inner[256];
    char *start;
    char *sep;
    char *open;
    int parts;
    int c;
    int length;
    int copy;
    int limit;
    int advance;
    int nameLength;
    char *scan;
    int i;
    char *tail;
    sep = strstr(*mangled != 0 ? mangled + 1 : mangled, text_double_underscore);
    start = out;
    if (sep != 0) {
        nameLength = sep - mangled;
    } else {
        nameLength = strlen(mangled);
        if (nameLength > size - 1) {
            nameLength = size - 1;
        }
        strncpy(out, mangled, nameLength);
        out[nameLength] = 0;
        *result = g_resultSuccess.v;
        return;
    }
    if (sep[2] == 'Q') {
        sep += 2;
        sep++;
        parts = *sep - '0';
        if (parts > 0 && parts < 10) {
            sep++;
            while (parts-- != 0) {
                length = 0;
                while ((c = *sep) >= '0' && c <= 57) {
                    length = c - '0' + length * 10;
                    sep++;
                }
                limit = size - 1;
                copy = length;
                if (copy > limit) {
                    copy = limit;
                }
                strncpy(out, sep, copy);
                out[copy] = 0;
                open = strchr(out, '<');
                if (open != 0) {
                    length = open - out;
                    memcpy(inner, open + 1, copy + 1 - length);
                    advance = length + 1;
                    if (advance > 254) {
                        advance = 254;
                    }
                    if (advance > size) {
                        advance = size;
                    }
                    out += advance;
                    size -= advance;
                    *out = 0;
                    igElfFile_DemangleName(inner, out, size);
                    advance = strlen(out);
                    size -= advance;
                    out += advance;
                    if (size > 1) {
                        *out = '>';
                        size--;
                        out++;
                    }
                    if (size > 1) {
                        *out = 0;
                        size--;
                        out++;
                    }
                } else {
                    sep += length;
                    out += copy;
                    size -= copy;
                }
                if (size > 2) {
                    size -= 2;
                    out[0] = ':';
                    out[1] = ':';
                    out += 2;
                }
            }
        }
    }
    *out = 0;
    tail = out - 1;
    if (strncmp(mangled, text_double_underscore, 2) == 0) {
        while (((start < tail) ^ 1) == 0 && *tail == ':') {
            tail--;
        }
        scan = tail;
        if (*tail != 0) {
            tail++;
        }
        while (((start < scan) ^ 1) == 0 && *scan != ':') {
            scan--;
        }
        if (*scan == ':') {
            scan++;
        }
        if (strncmp(mangled, text_ct, nameLength) == 0) {
            nameLength = tail - scan;
            if (nameLength > size - 1) {
                nameLength = size - 1;
            }
            strncpy(out, scan, nameLength);
            out[nameLength] = 0;
            *result = g_resultSuccess.v;
            return;
        }
        if (strncmp(mangled, text_dt, nameLength) == 0) {
            nameLength = tail - scan;
            if (size > 0) {
                *out = '~';
                size--;
                out++;
            }
            if (nameLength > size - 1) {
                nameLength = size - 1;
            }
            strncpy(out, scan, nameLength);
            out[nameLength] = 0;
            *result = g_resultSuccess.v;
            return;
        }
        for (i = 0; g_elfSpecialNames[i].mangled != 0; i++) {
            if (strncmp(g_elfSpecialNames[i].mangled, mangled, nameLength) == 0 && g_elfSpecialNames[i].name != 0) {
                nameLength = strlen(g_elfSpecialNames[i].name);
                if (nameLength > size - 1) {
                    nameLength = size - 1;
                }
                strncpy(out, g_elfSpecialNames[i].name, nameLength);
                out[nameLength] = 0;
                *result = g_resultSuccess.v;
                return;
            }
        }
    }
    if (nameLength > size - 1) {
        nameLength = size - 1;
    }
    strncpy(out, mangled, nameLength);
    out[nameLength] = 0;
    *result = g_resultSuccess.v;
}

int *igElfFile_LookupValueName(int value, int *table) {
    int *name;
    while ((name = (int *)table[1]) != 0) {
        if (table[0] == value) return name;
        table += 2;
    }
    return &emptyString_4[0];
}

char *igElfFile_FormatFlags(int flags, int names, char *out) {
    int flag;
    int i;
    char *name;
    char *sep;
    i = 0;
    *out = 0;
    do {
        flag = flags & (1 << i);
        if (flag != 0) {
            name = ((char *)igElfFile_LookupValueName(flag, (int *)names));
            if (*name != 0) {
                if (*out != 0) {
                    sep = ((char *)emptyString_4);
                } else {
                    sep = text_comma_space;
                }
                sprintf(&out[strlen(out)], percent_s_percent_s, sep, name);
            }
        }
        i++;
    } while (i < 32);
    return out;
}

void igElfFile_PrintHeader(ElfFileView *o) {
    igReport_Printf(text_ELF_header);
    igReport_Flush();
    igReport_Printf(text_e_ident_EI_NIDENT);
    igReport_Flush();
    igReport_Printf(text_EI_MAG0_0x_percent_2x, o->magic[0]);
    igReport_Flush();
    igReport_Printf(text_EI_MAG1_percent_c, o->magic[1]);
    igReport_Flush();
    igReport_Printf(text_EI_MAG2_percent_c, o->magic[2]);
    igReport_Flush();
    igReport_Printf(text_EI_MAG3_percent_c, o->magic[3]);
    igReport_Flush();
    igReport_Printf(text_EI_CLASS_percent_s, ((int)igElfFile_LookupValueName(o->elfClass, &g_elfClassNames[0])));
    igReport_Flush();
    igReport_Printf(text_EI_DATA_percent_s, ((int)igElfFile_LookupValueName(o->endian, &g_elfDataNames[0])));
    igReport_Flush();
    igReport_Printf(text_EI_VERSION_percent_d, o->identVersion);
    igReport_Flush();
    igReport_Printf(EI_PAD);
    igReport_Flush();
    igReport_Printf(text_e_type_percent_s, ((int)igElfFile_LookupValueName(o->type, &g_elfTypeNames[0])));
    igReport_Flush();
    igReport_Printf(text_e_machine_percent_s, ((int)igElfFile_LookupValueName(o->machine, &g_elfMachineNames[0])));
    igReport_Flush();
    igReport_Printf(text_e_version_percent_d, o->version);
    igReport_Flush();
    igReport_Printf(text_e_entry_0x_percent_08x, o->entry);
    igReport_Flush();
    igReport_Printf(text_e_phoff_0x_percent_08x, o->programHeaderOffset);
    igReport_Flush();
    igReport_Printf(text_e_shoff_0x_percent_08x, o->sectionHeaderOffset);
    igReport_Flush();
    igReport_Printf(text_e_flags_0x_percent_08x, o->flags);
    igReport_Flush();
    igReport_Printf(text_e_ehsize_0x_percent_08x, o->headerSize);
    igReport_Flush();
    igReport_Printf(text_e_phentsize_0x_percent_08x, o->programHeaderEntrySize);
    igReport_Flush();
    igReport_Printf(text_e_phnum_0x_percent_08x, o->programHeaderCount);
    igReport_Flush();
    igReport_Printf(text_e_shentsize_0x_percent_08x, o->sectionHeaderEntrySize);
    igReport_Flush();
    igReport_Printf(text_e_shnum_0x_percent_08x, o->sectionHeaderCount);
    igReport_Flush();
    igReport_Printf(text_e_shstrndx_0x_percent_08x, o->sectionNameIndex);
    igReport_Flush();
    igReport_Printf(newline_2);
    igReport_Flush();
}

void igElfFile_PrintSectionHeaders(int *self) {
    int count;
    int i;
    count = self[19];
    igReport_Printf(text_Section_headers_percent_d_0x_percent_x, count, count);
    igReport_Flush();
    for (i = 0; i < self[19]; i++) {
        igElfFile_PrintSectionHeader((ElfFileView *)self, i, igElfFile_GetSectionHeader((ElfFileView *)self, i));
    }
}

void igElfFile_PrintSectionHeader(ElfFileView *self, int index, ElfSection *section) {
    char flagText[128];

    igReport_Printf(text_Section_header_percent_d);
    igReport_Flush();
    igReport_Printf(text_sh_name_0x_percent_x_percent_s, section->name, (int)self->sectionNames + section->name);
    igReport_Flush();
    igReport_Printf(text_sh_type_percent_s, ((int)igElfFile_LookupValueName(section->type, &g_elfSectionTypeNames[0])));
    igReport_Flush();
    igReport_Printf(text_sh_flags_0x_percent_08x_percent_s, section->flags, ((int)igElfFile_FormatFlags(section->flags, (int)&g_elfSectionFlagNames[0], (char *)flagText)));
    igReport_Flush();
    igReport_Printf(text_sh_addr_0x_percent_08x, section->addr);
    igReport_Flush();
    igReport_Printf(text_sh_offset_0x_percent_08x, section->offset);
    igReport_Flush();
    igReport_Printf(text_sh_size_0x_percent_08x, section->size);
    igReport_Flush();
    igReport_Printf(text_sh_link_0x_percent_08x, section->link);
    igReport_Flush();
    igReport_Printf(text_sh_info_0x_percent_08x, section->info);
    igReport_Flush();
    igReport_Printf(text_sh_addralign_0x_percent_08x, section->addressAlign);
    igReport_Flush();
    igReport_Printf(text_sh_entsize_0x_percent_08x, section->entrySize);
    igReport_Flush();
    igReport_Printf(newline_2);
    igReport_Flush();
}

void igElfFile_PrintSymbols(ElfFileView *self) {
    int count;
    int i;

    count = self->symbolCount;
    igReport_Printf(text_Symbols_percent_d_0x_percent_x, count, count);
    igReport_Flush();
    for (i = 0; i < self->symbolCount; i++) {
        igElfFile_PrintSymbol((igElfFile *)self, i, (ElfSymbol *)(igElfFile_GetSymbol(self, i)));
    }
}

void igElfFile_PrintSymbol(igElfFile *self, int index, ElfSymbol *symbol) {
    int *section;
    char *sectionName;

    section = ((int *)igElfFile_GetSectionHeader((ElfFileView *)self, symbol->sectionIndex));
    if (section != 0) {
        sectionName = (char *)(self->_sectionHeaderStringTable + *section);
    } else {
        sectionName = ((char *)emptyString_4);
    }
    igReport_Printf(text_Symbol_percent_d, index);
    igReport_Flush();
    igReport_Printf(text_st_name_0x_percent_x_percent_s, symbol->name, self->_symbolStringTable + symbol->name);
    igReport_Flush();
    igReport_Printf(text_st_value_0x_percent_08x, symbol->value);
    igReport_Flush();
    igReport_Printf(text_st_size_0x_percent_08x, symbol->size);
    igReport_Flush();
    igReport_Printf(text_st_info_0x_percent_08x, symbol->info);
    igReport_Flush();
    igReport_Printf(text_bind_percent_s, ((int)igElfFile_LookupValueName(symbol->info >> 4, (int *)g_elfSymbolBindNames)));
    igReport_Flush();
    igReport_Printf(text_type_percent_s, ((int)igElfFile_LookupValueName(symbol->info & 0xF, (int *)g_elfSymbolTypeNames)));
    igReport_Flush();
    igReport_Printf(text_st_other_0x_percent_08x, symbol->other);
    igReport_Flush();
    igReport_Printf(text_st_shndx_0x_percent_08x_percent_s, symbol->sectionIndex, sectionName);
    igReport_Flush();
    igReport_Printf(newline_2);
    igReport_Flush();
}

