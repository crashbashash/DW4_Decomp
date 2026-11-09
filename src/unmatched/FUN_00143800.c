typedef struct AudioVoiceEntry {
    char pad0[8];
    unsigned char low : 5;
    unsigned char active : 1;
    unsigned char high : 2;
    char pad9[27];
} AudioVoiceEntry;

typedef struct AudioVoiceTable {
    char pad0[16];
    AudioVoiceEntry *entries;
} AudioVoiceTable;

typedef struct AudioVoiceHandle {
    char pad0[12];
    int voice;
} AudioVoiceHandle;

extern AudioVoiceTable *g_audioTableOwner;

void FUN_00143800(AudioVoiceHandle *h)
{
    g_audioTableOwner->entries[h->voice].active = 0;
}
