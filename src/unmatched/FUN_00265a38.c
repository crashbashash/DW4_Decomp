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

typedef struct AdxPlayer {
    char pad0[12];
    AdxChannelTable *table;
} AdxPlayer;

unsigned int FUN_00265a38(AdxPlayer *p, int ch)
{
    AdxStream *s = p->table->channels[ch]->stream;

    return (unsigned int)s->ops->query(s, 1) >> 1;
}
