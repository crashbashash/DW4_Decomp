/* The VU1 microcode's symbol table: the linked-in text of `sym.ini`, `name;offset;` pairs naming each
 * program's entry and end in the microcode image. */
#include <stdlib.h>
#include <string.h>
#include "dw4/p2vu1Symbols.h"

extern char p2Vu1SymbolText[];
int p2Vu1SymbolsUnsplit = 1;
int p2Vu1SymbolBase;
int p2Vu1SymbolTextLength;

/* Splits the text into NUL-terminated names and offsets once; offsets are read relative to `base`. */
int p2OpenVu1Symbols(const char *path, int base) {
    int length;
    int i;

    length = strlen(p2Vu1SymbolText);
    p2Vu1SymbolBase = base;
    if (p2Vu1SymbolsUnsplit != 0) {
        p2Vu1SymbolTextLength = length;
        for (i = 0; i < length; i++) {
            if (p2Vu1SymbolText[i] == ';') {
                p2Vu1SymbolText[i] = 0;
            }
        }
        p2Vu1SymbolsUnsplit = 0;
    }
    return 1;
}

void p2CloseVu1Symbols(void) {
    p2Vu1SymbolBase = 0;
}

int p2FindVu1Symbol(const char *name) {
    int address;
    int offset;
    char *entry;

    address = -1;
    offset = 0;
    do {
        entry = p2Vu1SymbolText + offset;
        if (strcmp(entry, name) == 0) {
            offset += strlen(entry) + 1;
            address = p2Vu1SymbolBase + atoi(p2Vu1SymbolText + offset);
            break;
        }
        offset += strlen(entry) + 1;
        offset += strlen(p2Vu1SymbolText + offset) + 1;
    } while (offset < p2Vu1SymbolTextLength);
    return address;
}
