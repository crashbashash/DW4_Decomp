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

char g_byteOrderProbe = 0x34;

void igElfFile_Open(int *result, ElfFileView *self, const char *path) {
    if (igProgramFile_Open((igProgramFile *)self, path) == g_resultFailure) {
        *result = g_resultFailure.v;
        return;
    }
    if (self->stream->Read(self->magic, 0x34, 1) != 1) {
        igReport_Printf("Error reading: %s\n", self->path);
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
        igReport_Printf((const char *)"Invalid file signature: %s\n", self->path);
        igReport_Flush();
        self->Close();
        *result = g_resultFailure.v;
        return;
    }
    int sectionOffset = self->sectionHeaderOffset;
    if (sectionOffset == 0) {
        igReport_Printf((const char *)"No section headers in: %s\n", self->path, sectionOffset);
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
        igReport_Printf("No symbol section in: %s\n", self->path);
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
        igReport_Printf("Can't find symbol string table in: %s\n", self->path);
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
        igReport_Printf("No symbols in: %s", self->path);
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

ElfOperatorName g_elfSpecialNames[] = {
    { "__ct", 0 },
    { "__dt", 0 },
    { "__as", "operator=" },
    { "__eq", "operator==" },
    { "__ne", "operator!=" },
    { "__gt", "operator>" },
    { "__ge", "operator>=" },
    { "__lt", "operator<" },
    { "__le", "operator<=" },
    { "__rf", "operator&" },
    { "__pt", "operator*" },
    { "__ls", "operator<<" },
    { "__rs", "operator>>" },
    { 0, 0 },
};

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
    sep = strstr(*mangled != 0 ? mangled + 1 : mangled,"__");
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
    if (strncmp(mangled,"__", 2) == 0) {
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
        if (strncmp(mangled,"__ct", nameLength) == 0) {
            nameLength = tail - scan;
            if (nameLength > size - 1) {
                nameLength = size - 1;
            }
            strncpy(out, scan, nameLength);
            out[nameLength] = 0;
            *result = g_resultSuccess.v;
            return;
        }
        if (strncmp(mangled,"__dt", nameLength) == 0) {
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

const char *igElfFile_LookupValueName(int value, const ElfValueName *table) {
    const char *name;
    while ((name = table->name) != 0) {
        if (table->value == value) return name;
        table++;
    }
    return "";
}

char *igElfFile_FormatFlags(int flags, const ElfValueName *names, char *out) {
    int flag;
    int i;
    char *name;
    char *sep;
    i = 0;
    *out = 0;
    do {
        flag = flags & (1 << i);
        if (flag != 0) {
            name = ((char *)igElfFile_LookupValueName(flag, names));
            if (*name != 0) {
                if (*out != 0) {
                    sep = ((char *)"");
                } else {
                    sep =", ";
                }
                sprintf(&out[strlen(out)],"%s%s", sep, name);
            }
        }
        i++;
    } while (i < 32);
    return out;
}

ElfValueName g_elfClassNames[] = {
    { 0, "ELFCLASSNONE" },
    { 1, "ELFCLASS32" },
    { 2, "ELFCLASS64" },
    { 0, 0 },
};
ElfValueName g_elfDataNames[] = {
    { 0, "ELFDATANONE" },
    { 1, "ELFDATA2LSB" },
    { 2, "ELFDATA2MSB" },
    { 0, 0 },
};
ElfValueName g_elfTypeNames[] = {
    { 0, "ET_NONE" },
    { 1, "ET_REL" },
    { 2, "ET_EXEC" },
    { 3, "ET_DYN" },
    { 4, "ET_CORE" },
    { 0xff00, "ET_LOPROC" },
    { 0xffff, "ET_HIPROC" },
    { 0, 0 },
};
ElfValueName g_elfMachineNames[] = {
    { 0, "ET_NONE" },
    { 1, "EM_M32" },
    { 2, "EM_SPARC" },
    { 3, "EM_386" },
    { 4, "EM_68K" },
    { 5, "EM_88K" },
    { 7, "EM_860" },
    { 8, "EM_MIPS" },
    { 0xa, "EM_MIPS_RS4_BE" },
    { 0, 0 },
};

void igElfFile_PrintHeader(ElfFileView *o) {
    igReport_Printf("    ELF header:\n");
    igReport_Flush();
    igReport_Printf("        e_ident[EI_NIDENT]:\n");
    igReport_Flush();
    igReport_Printf("            EI_MAG0:    0x%2x\n", o->magic[0]);
    igReport_Flush();
    igReport_Printf("            EI_MAG1:    '%c'\n", o->magic[1]);
    igReport_Flush();
    igReport_Printf("            EI_MAG2:    '%c'\n", o->magic[2]);
    igReport_Flush();
    igReport_Printf("            EI_MAG3:    '%c'\n", o->magic[3]);
    igReport_Flush();
    igReport_Printf("            EI_CLASS:   %s\n", ((int)igElfFile_LookupValueName(o->elfClass, g_elfClassNames)));
    igReport_Flush();
    igReport_Printf("            EI_DATA:    %s\n", ((int)igElfFile_LookupValueName(o->endian, g_elfDataNames)));
    igReport_Flush();
    igReport_Printf("            EI_VERSION: %d\n", o->identVersion);
    igReport_Flush();
    igReport_Printf("            EI_PAD:\n");
    igReport_Flush();
    igReport_Printf("        e_type:\t        %s\n", ((int)igElfFile_LookupValueName(o->type, g_elfTypeNames)));
    igReport_Flush();
    igReport_Printf("        e_machine:      %s\n", ((int)igElfFile_LookupValueName(o->machine, g_elfMachineNames)));
    igReport_Flush();
    igReport_Printf("        e_version:      %d\n", o->version);
    igReport_Flush();
    igReport_Printf("        e_entry:        0x%08x\n", o->entry);
    igReport_Flush();
    igReport_Printf("        e_phoff:        0x%08x\n", o->programHeaderOffset);
    igReport_Flush();
    igReport_Printf("        e_shoff:        0x%08x\n", o->sectionHeaderOffset);
    igReport_Flush();
    igReport_Printf("        e_flags:        0x%08x\n", o->flags);
    igReport_Flush();
    igReport_Printf("        e_ehsize:       0x%08x\n", o->headerSize);
    igReport_Flush();
    igReport_Printf("        e_phentsize:    0x%08x\n", o->programHeaderEntrySize);
    igReport_Flush();
    igReport_Printf("        e_phnum:        0x%08x\n", o->programHeaderCount);
    igReport_Flush();
    igReport_Printf("        e_shentsize:    0x%08x\n", o->sectionHeaderEntrySize);
    igReport_Flush();
    igReport_Printf("        e_shnum:        0x%08x\n", o->sectionHeaderCount);
    igReport_Flush();
    igReport_Printf("        e_shstrndx:     0x%08x\n", o->sectionNameIndex);
    igReport_Flush();
    igReport_Printf(newline_2);
    igReport_Flush();
}

void igElfFile_PrintSectionHeaders(int *self) {
    int count;
    int i;
    count = self[19];
    igReport_Printf("    Section headers:  %d (0x%x)\n", count, count);
    igReport_Flush();
    for (i = 0; i < self[19]; i++) {
        igElfFile_PrintSectionHeader((ElfFileView *)self, i, igElfFile_GetSectionHeader((ElfFileView *)self, i));
    }
}

ElfValueName g_elfSectionTypeNames[] = {
    { 0, "SHT_NULL" },
    { 1, "SHT_PROGBITS" },
    { 2, "SHT_SYMTAB" },
    { 3, "SHT_STRTAB" },
    { 4, "SHT_RELA" },
    { 5, "SHT_HASH" },
    { 6, "SHT_DYNAMIC" },
    { 7, "SHT_NOTE" },
    { 8, "SHT_NOBITS" },
    { 9, "SHT_REL" },
    { 0xa, "SHT_SHLIB" },
    { 0xb, "SHT_DYNSYM" },
    { 0x70000000, "SHT_LOPROC" },
    { 0x7fffffff, "SHT_HIPROC" },
    { 0x80000000, "SHT_LOUSER" },
    { 0xffffffff, "SHT_HIUSER" },
    { 0, 0 },
};
ElfValueName g_elfSectionFlagNames[] = {
    { 1, "SHF_WRITE" },
    { 2, "SHF_ALLOC" },
    { 4, "SHF_EXECINSTR" },
    { 0xf0000000, "SHF_MASKPROC" },
    { 0, 0 },
};

void igElfFile_PrintSectionHeader(ElfFileView *self, int index, ElfSection *section) {
    char flagText[128];

    igReport_Printf("    Section header [%d]:\n");
    igReport_Flush();
    igReport_Printf("        sh_name:\t     0x%x \"%s\"\n", section->name, (int)self->sectionNames + section->name);
    igReport_Flush();
    igReport_Printf("        sh_type:\t     %s\n", ((int)igElfFile_LookupValueName(section->type, g_elfSectionTypeNames)));
    igReport_Flush();
    igReport_Printf("        sh_flags:        0x%08x (%s)\n", section->flags, ((int)igElfFile_FormatFlags(section->flags, g_elfSectionFlagNames, (char *)flagText)));
    igReport_Flush();
    igReport_Printf("        sh_addr:         0x%08x\n", section->addr);
    igReport_Flush();
    igReport_Printf("        sh_offset:       0x%08x\n", section->offset);
    igReport_Flush();
    igReport_Printf("        sh_size:         0x%08x\n", section->size);
    igReport_Flush();
    igReport_Printf("        sh_link:         0x%08x\n", section->link);
    igReport_Flush();
    igReport_Printf("        sh_info:         0x%08x\n", section->info);
    igReport_Flush();
    igReport_Printf("        sh_addralign:    0x%08x\n", section->addressAlign);
    igReport_Flush();
    igReport_Printf("        sh_entsize:      0x%08x\n", section->entrySize);
    igReport_Flush();
    igReport_Printf(newline_2);
    igReport_Flush();
}

void igElfFile_PrintSymbols(ElfFileView *self) {
    int count;
    int i;

    count = self->symbolCount;
    igReport_Printf("    Symbols:  %d (0x%x)\n", count, count);
    igReport_Flush();
    for (i = 0; i < self->symbolCount; i++) {
        igElfFile_PrintSymbol((igElfFile *)self, i, (ElfSymbol *)(igElfFile_GetSymbol(self, i)));
    }
}

ElfValueName g_elfSymbolBindNames[] = {
    { 0, "STB_LOCAL" },
    { 1, "STB_GLOBAL" },
    { 2, "STB_WEAK" },
    { 0xd, "STB_LOPROC" },
    { 0xf, "STB_HIPROC" },
    { 0, 0 },
};
ElfValueName g_elfSymbolTypeNames[] = {
    { 0, "STT_NOTYPE" },
    { 1, "STT_OBJECT" },
    { 2, "STT_FUNC" },
    { 3, "STT_SECTION" },
    { 4, "STT_FILE" },
    { 0xd, "STT_LOPROC" },
    { 0xf, "STT_HIPROC" },
    { 0, 0 },
};

void igElfFile_PrintSymbol(igElfFile *self, int index, ElfSymbol *symbol) {
    int *section;
    char *sectionName;

    section = ((int *)igElfFile_GetSectionHeader((ElfFileView *)self, symbol->sectionIndex));
    if (section != 0) {
        sectionName = (char *)(self->_sectionHeaderStringTable + *section);
    } else {
        sectionName = ((char *)"");
    }
    igReport_Printf("    Symbol [%d]:\n", index);
    igReport_Flush();
    igReport_Printf("        st_name:\t     0x%x \"%s\"\n", symbol->name, self->_symbolStringTable + symbol->name);
    igReport_Flush();
    igReport_Printf("        st_value:        0x%08x\n", symbol->value);
    igReport_Flush();
    igReport_Printf("        st_size:         0x%08x\n", symbol->size);
    igReport_Flush();
    igReport_Printf("        st_info:         0x%08x\n", symbol->info);
    igReport_Flush();
    igReport_Printf("            bind:            %s\n", ((int)igElfFile_LookupValueName(symbol->info >> 4, g_elfSymbolBindNames)));
    igReport_Flush();
    igReport_Printf("            type:            %s\n", ((int)igElfFile_LookupValueName(symbol->info & 0xF, g_elfSymbolTypeNames)));
    igReport_Flush();
    igReport_Printf("        st_other:        0x%08x\n", symbol->other);
    igReport_Flush();
    igReport_Printf("        st_shndx:        0x%08x \"%s\"\n", symbol->sectionIndex, sectionName);
    igReport_Flush();
    igReport_Printf(newline_2);
    igReport_Flush();
}

