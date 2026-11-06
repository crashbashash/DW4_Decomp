/* When channel index is in state 5, releases its buffer handler through ops slot 12 and clears the
 * pointer. */
struct Handler;
struct HandlerOps {
    char pad[12];
    void (*fn12)(struct Handler *);
};
struct Handler {
    struct HandlerOps *ops;
};
struct ChannelBuf {
    char *data;                           /* +16 */
    struct Handler *handler;              /* +20 */
};
struct Channel {
    int state;
    int f4, f8, f12;
    struct ChannelBuf buf;                /* +16 */
    char pad24[116 - 24];
};
struct Owner29d7d0 {
    char pad[4872];
    struct Channel channels[1];           /* +4872 */
};

void FUN_0029d7d0(struct Owner29d7d0 *owner, int index) {
    struct Channel *channels = owner->channels;
    struct Channel *channel = &channels[index];
    struct ChannelBuf *buf = &channel->buf;
    struct Handler *handler;

    if (channel->state == 5) {
        handler = buf->handler;
        if (handler != 0) {
            handler->ops->fn12(handler);
            buf->handler = 0;
        }
    }
}
