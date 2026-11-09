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

extern int DAT_004b1dc0;
extern int DAT_004b1dc8;

int FUN_0027aaa8(AdxVoice *v)
{
    AdxStream *s;

    if (DAT_004b1dc8 == 1 && DAT_004b1dc0 <= 0)
        return 0;
    s = v->ch->stream;
    return s->ops->query(s, 0) / 2;
}
