extern double floor(double);
struct Voice {
    unsigned int position;
    int f4;
    unsigned char used : 1;
    unsigned char stereo : 1;
    unsigned char seek : 1;
    unsigned char loop : 1;
    unsigned char reserved4 : 1;
    unsigned char reserved5 : 1;
    unsigned char playing : 1;
    unsigned char paused : 1;
    unsigned char reserved8 : 4;
    unsigned char dirty : 1;
    char pad[26];
};
struct VoiceTable { char pad[16]; struct Voice *items; };
struct PlayRequest { char pad[8]; float start; int channels; int pad16; int mode; };
extern struct VoiceTable *DAT_0055f5d0[4];
/* matching construct: a small sweep of spellings */
void Gap__igPsx2AudioContext__vfunc_30(void *self, int index, struct PlayRequest *req) {
    struct Voice *v = &DAT_0055f5d0[0]->items[index];
    if (req->channels > 1) {
        v->stereo = 1;
    }
    switch (req->mode) {
    case 1:
        v->paused = 1;
        v->loop = 1;
        break;
    case 2:
        v->loop = 1;
        v->playing = 1;
        break;
    case 3:
        v->seek = 1;
        v->paused = 1;
        break;
    case 4:
        v->seek = 1;
        v->position = (unsigned int)floor(req->start);
        v->playing = 1;
        break;
    case 0:
        return;
    default:
        return;
    }
    v->dirty = 1;
}
