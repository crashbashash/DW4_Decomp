int igBoolMetaField_ValueFromString(void *self, char *value, int text) {
    int consumed;
    int number;

    consumed = 0;
    number = 0;
    sscanf((const char *)text, "%d%n", &number, &consumed);
    if (consumed > 0) {
        *value = number != 0;
        return consumed;
    }
    if (strncasecmp("true", (const char *)text, 4) == 0) {
        *value = 1;
        return 4;
    }
    if (strncasecmp("false", (const char *)text, 5) == 0) {
        *value = 0;
        return 5;
    }
    return 0;
}

void igBoolMetaField_ValueToString(int *result, void *self, unsigned char *value) {
    int buffer[256];
    int *text;
    int pool;
    int interned;

    if (*value != 0) {
        text = (int *)("true");
    } else {
        text = (int *)("false");
    }
    sprintf((char *)buffer, (const char *)&percent_s[0], text);
    if (buffer == 0) {
        interned = 0;
    } else {
        if (g_stringPool == 0) {
            pool = ((int)StringPool_Allocate(0x10));
            if (pool != 0) {
                pool = ((int)StringPool_Construct((StringPool *)pool));
            }
            g_stringPool = (StringPool *)pool;
        }
        interned = (int)StringPool_Intern((StringPool *)g_stringPool, (const char *)buffer);
    }
    *result = interned;
}

int **igBoolMetaField_Construct(int **self, int unused) {
    igMetaField_Construct((igMetaField *)self);
    *self = &g_igBoolMetaField_vtable[0];
    if (self != 0) {
        igBoolMetaField_Init(self);
    }
    return self;
}

int **igBoolMetaField_Init(int **self) {
    igMetaField_Init((igMetaField *)self);
    *self = &g_igBoolMetaField_vtable[0];
    return self;
}

int **igBoolMetaField_CopyConstruct(int **self, int source) {
    igMetaField_CopyConstruct((igMetaField *)self, (igMetaField *)source);
    *self = &g_igBoolMetaField_vtable[0];
    return self;
}

void igBoolMetaField_Destruct(int extra0) {
    igMetaField_Destruct((igMetaField *)extra0);
}

int igBoolMetaField_GetSize(void) {
    return 1;
}

void igBoolMetaField_SetDefaultValue(igMetaField *self, char value) {
    char defaultValue;

    defaultValue = value;
    ((igMetaFieldView *)(self))->SetDefault(&defaultValue);
}

int igBoolMetaField_GetAlignment(void) {
    return 1;
}

void igCallStackTable_SetCapacity(int table, int capacity)
{
    ((igCallStackTable *)table)->_capacity = capacity;
}

