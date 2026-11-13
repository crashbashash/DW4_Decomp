typedef struct AdxStreamOps AdxStreamOps;

typedef struct AdxStream {
    AdxStreamOps *ops;
} AdxStream;

struct AdxStreamOps {
    char pad0[36];
    int (*query)(AdxStream *s, int what);
};

typedef struct AdxChannel {
    char pad0[8];
    AdxStream *stream;
} AdxChannel;

typedef struct AdxChannelTable {
    char pad0[8];
    AdxChannel *channels[1];
} AdxChannelTable;

typedef struct AdxVoice {
    char pad0[8];
    AdxChannel *ch;
} AdxVoice;

extern int ps2rna_nvoice;
extern int ps2rna_setup_voice;

int FUN_0027aa40(AdxVoice *v)
{
    AdxStream *s;

    if (ps2rna_setup_voice == 1 && ps2rna_nvoice <= 0)
        return 0;
    s = v->ch->stream;
    return (0x4000 - s->ops->query(s, 0)) / 2;
}
