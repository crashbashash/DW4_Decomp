/* Starts channel index from state 4 by handing the source to its buffer (FUN_0029dc18), or reports
 * error 0xFF000409. */
int FUN_0029dc18();
int FUN_002a0bb8();

struct ChannelBuf {
    char *data;                           /* +16 */
    int size;                             /* +20 */
};
struct Channel {
    int state;
    int f4, f8, f12;
    struct ChannelBuf buf;                /* +16 */
    char pad24[116 - 24];
};
struct Owner29dba8 {
    char pad[4872];
    struct Channel channels[1];           /* +4872 */
};
struct Source29dba8 {
    int f0;
    int f4;
};

int FUN_0029dba8(struct Owner29dba8 *owner, struct Source29dba8 *source, int index) {
    struct Channel *channels = owner->channels;
    struct Channel *channel = &channels[index];
    struct ChannelBuf *buf = &channel->buf;

    if (channel->state != 4) {
        return FUN_002a0bb8(owner, 0xFF000409);
    }
    FUN_0029dc18(buf, source, channel, source->f4 != 0);
    return 0;
}
