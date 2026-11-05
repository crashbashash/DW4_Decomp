#include "dw4/frontaudio.h"
#include "dw4/audio.h"
#include "dw4/igb.h"
#include "dw4/igfile.h"
#include "dw4/sfp.h"
#include "dw4/stagesound.h"
#include "dw4/voicepool.h"
#include "dw4/ramp.h"
#include "dw4/streamplayer.h"
#include "dw4/script.h"
#include "audio_repeat.h"
#include "audio_level.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

static const char *names[] = { "ST_CHARA", "AM_TITLE", "AM_START", "CURSOR_START",
    "CURSOR_MOVE", "CURSOR_DECIDE", "CURSOR_CANCEL", "WINDOW_OPEN", "WINDOW_CLOSE", "CURSOR_MOVE2", "WINDOW_CLOSE2", "CURSOR_NG" };
/* Room for the longest cue list (the lobby's 13 names), not just the title list below. */
#define NAMES (sizeof(names) / sizeof(names[0]))
#define FA_VOICES 64   /* mixer voices: 0 music, 1 ambience, 3..7 legacy cue voices, 8..11 ADX effect handles, 12..59 sound-bank handles */
#define POOL_ADX_VOICE 8
#define POOL_BANK_VOICE 12
#define POOL (DW4_VOICEPOOL_ADX + DW4_VOICEPOOL_BANK)
#define CLIPS 192   /* a gameplay stage names 76..113 cues; the scene lists use at most 32 */
static const char *lobby_names[] = { "ST_LOBBY", "AM_LOBBY", "mlBEEP01", "CURSOR_START",
    "CURSOR_MOVE", "CURSOR_DECIDE", "CURSOR_CANCEL", "WINDOW_OPEN", "WINDOW_CLOSE", "CURSOR_MOVE2", "WINDOW_CLOSE2", "CURSOR_NG", "ITEM_GET" };
/* The Commander Room (stagML02, sound bank in its own stage pack): start.lua PLAYs ST_COMMA, QS_HURRY, DM_LEOMN or DM_SERAF by
 * progress and AM_LOBBY or AM_OFNI2; the Ophanimon/Seraphimon events switch to DM_OFNI/DM_SERAF/DM_LEOMN, fade them with
 * VOLUMECTL2 and stop them with BGMSTOP; QS_DOIT and ITEM_GET are one-shots. */
static const char *commander_names[] = { "ST_COMMA", "AM_LOBBY", "mlBEEP01", "CURSOR_START",
    "CURSOR_MOVE", "CURSOR_DECIDE", "CURSOR_CANCEL", "WINDOW_OPEN", "WINDOW_CLOSE", "CURSOR_MOVE2", "WINDOW_CLOSE2", "CURSOR_NG", "ITEM_GET",
    "AM_OFNI1", "AM_OFNI2", "DM_LEOMN", "DM_SERAF", "DM_OFNI", "QS_HURRY", "QS_DOIT",
    /* model sounds of the room's own bank: Ophanimon's turn, the gate, the alarm indicator, the recorder and the warp */
    "ofTURN", "mlGATE01", "icOFF2ON", "icON2OFF", "imOPEN01", "plWARP01", "TOPICON", "OBJ_BUTTON_ON", "OBJ_BUTTON_OFF" };
#define LOBBY_REQUIRED 13   /* the shared lobby cue list; the Commander Room's extra tracks may be absent from a bank */
struct dw4_frontaudio {
    dw4_audio *device;
    dw4_script *scripts;
    dw4_audio_clip clip[CLIPS];
    const char *const *names;
    unsigned count, cue_start;
    uint64_t clock_ns;
    int type[CLIPS];
    float gain[CLIPS];
    dw4_audio_repeat repeat[CLIPS];
    struct { char model[48], action[32], sound[48]; int delay; } action[512];
    unsigned naction;
    int music_started;
    int held[CLIPS];   /* dw4_frontaudio_stage_service: PLAYatPAUSE requests waiting for PAUSEOFF */
    unsigned cue_voice;
    struct {unsigned clip;int valid,ducked;int64_t handle;} voice[FA_VOICES];
    uint64_t next_handle;
    int open_set;                  /* prepare_gameplay: the clip set is the stage catalogue, not a fixed scene list */
    unsigned char adx_file[CLIPS]; /* the clip is an ADX file played as an effect (retail memory index -1): ADX handle, stream level */
    int16_t priority[CLIPS];       /* beSoundData._priority */
    dw4_voice_slot pool[POOL];     /* the 4 + 48 retail effect handles (open sets) */
    int64_t pool_request;          /* retail beCri._request: id of the last effect play */
    int bgm_cur;                   /* 1 + clip index of the current BGM (retail beSound._currentBGM), 0 for none */
    unsigned stream_starts;        /* streamed tracks started through SOUND PLAY (inspection) */
    unsigned last_cue_voice;       /* mixer voice of the last cue()/model_play effect */
    struct {int clip;uint64_t due_ns;} retry[2];   /* delayed PLAY of a music/ambience request that found its slot busy (clip + 1, 0 for none) */
    unsigned model_requests, model_unresolved;   /* typed SCSound PLAY requests, and those naming no prepared clip */
    char last_unresolved[DW4_STAGESOUND_NAME];
    char request_log[16][DW4_STAGESOUND_NAME];   /* the first 16 PLAY request names, for flow checks */
    char (*owned)[DW4_STAGESOUND_NAME];
    const char **owned_ptr;
    /* VOLUMECTL2 fades (host policy): per voice, a linear gain multiplier from..to over the given 60 Hz ticks. */
    struct {int active;float from,to,level;uint64_t start_ns,length_ns;int ramp;dw4_ramp rp;uint64_t frames;} fade[FA_VOICES];
    int base_volume;               /* beSoundInfo._baseVolume of the clip set (retail beCri._baseVolume) */
    int16_t volume[CLIPS];         /* beSoundData._volume of each clip */
};
static uint32_t value(const dw4_igb_record *r, unsigned slot)
{
    for (unsigned i = 0; i < r->nvalues; i++)
        if (r->values[i].ordinal == slot) return r->values[i].raw;
    return 0;
}
static uint32_t le32(const uint8_t *p)
{ return p[0] | (uint32_t)p[1] << 8 | (uint32_t)p[2] << 16 | (uint32_t)p[3] << 24; }
static uint32_t be32(const uint8_t *p)
{ return (uint32_t)p[0] << 24 | (uint32_t)p[1] << 16 | (uint32_t)p[2] << 8 | p[3]; }

/* beSoundInfo._fnameList -> igNamedObjectList._data -> named object IDs. */
static int filename(dw4_igb *g, uint32_t list, unsigned index, char *out, size_t cap)
{
    dw4_igb_record r;
    uint32_t off, len, block;
    const uint8_t *p;
    if (dw4_igb_ref(g, list, &off, NULL) != 2 || !dw4_igb_decode(g, off, &r)) return -1;
    block = value(&r, 4);
    dw4_igb_record_free(&r);
    p = dw4_igb_block(g, block, &len);
    if (!p || index >= len / 4 || dw4_igb_ref(g, le32(p + index * 4), &off, NULL) != 2 ||
        !dw4_igb_decode(g, off, &r)) return -1;
    if (!r.name) { dw4_igb_record_free(&r); return -1; }
    snprintf(out, cap, "%s", r.name);
    dw4_igb_record_free(&r);
    return 0;
}
/* beSeInfoData._actionList -> beSeDataList._data -> beSeData records. */
static void actions(dw4_frontaudio *a, dw4_igb *g, const dw4_igb_record *model)
{
    uint32_t off, size;
    dw4_igb_record list;
    if (!model->name || dw4_igb_ref(g, value(model, 4), &off, NULL) != 2 ||
        !dw4_igb_decode(g, off, &list)) return;
    const uint8_t *ids = dw4_igb_block(g, value(&list, 4), &size);
    dw4_igb_record_free(&list);
    if (!ids || size % 4) return;
    for (unsigned i = 0; i < size / 4 && a->naction < 512; i++) {
        dw4_igb_record r;
        if (dw4_igb_ref(g, le32(ids + i * 4), &off, NULL) != 2 ||
            !dw4_igb_decode(g, off, &r)) continue;
        if (!strcmp(r.class_name, "beSeData") && r.name) {
            const char *sound = NULL;
            for (unsigned j = 0; j < r.nvalues; j++)
                if (r.values[j].ordinal == 3) sound = r.values[j].str;
            if (sound) {
                unsigned k = a->naction++;
                snprintf(a->action[k].model, sizeof a->action[k].model, "%s", model->name);
                snprintf(a->action[k].action, sizeof a->action[k].action, "%s", r.name);
                snprintf(a->action[k].sound, sizeof a->action[k].sound, "%s", sound);
                a->action[k].delay = (int16_t)value(&r, 4);
            }
        }
        dw4_igb_record_free(&r);
    }
}
static int resident(const uint8_t *p, size_t n, const dw4_sfp_bank *bank,
                    unsigned index, dw4_audio_clip *c)
{
    dw4_sfp_entry e[256];
    unsigned ne = dw4_sfp_entries(p, n, bank, e, 256);
    size_t count;
    int16_t *mono;
    int rc;
    if (ne > 256 || index >= ne) return -1;
    count = (size_t)(e[index].end - e[index].start) / 16 * 28;
    mono = malloc(count * sizeof(*mono));
    if (!mono) return -1;
    count = dw4_vag_decode(p + bank->vag_off + e[index].start,
                          e[index].end - e[index].start, mono, count);
    rc = dw4_audio_from_mono(mono, count, (int)bank->rate, c);
    free(mono);
    return rc;
}
static int load(const dw4_mount *mnt, dw4_igb *g, uint32_t list,
                const dw4_igb_record *r, dw4_audio_clip *c, const char *label)
{
    char file[128];
    uint32_t size = 0;
    const uint8_t *p;
    int pt, entry;
    if (filename(g, list, value(r, 5), file, sizeof(file))) return -1;
    if (sscanf(file, "[%d.%d]", &pt, &entry) == 2) {
        size_t start, end;
        p = dw4_mount_entry(mnt, pt, entry, &size, NULL);
        if (!p || size < 0x38 || p[0] != 0x80 || p[1] != 0 ||
            dw4_audio_decode_blob(p, size, c)) return -1;
        /* The shipped streamed tracks are ADX v4. Loop fields follow the
         * channel histories; retain the intro and repeat only the authored loop. */
        if (p[18] == 4 && p[19] == 0 && p[7] <= 2 &&
            ((unsigned)p[2] * 256 + p[3] + 4) >= 0x38 + 6 && be32(p + 0x24)) {
            unsigned rate = be32(p + 8);
            if (rate) {
                start = (uint64_t)be32(p + 0x28) * 48000 / rate;
                end = (uint64_t)be32(p + 0x30) * 48000 / rate;
                if (start < end && end <= c->frames) { c->loop_start = start; c->loop_end = end; }
            }
        }
        printf("  %s audio: %s -> %s, %zu frames, loop %zu..%zu\n",
               label, r->name, file, c->frames, c->loop_start, c->loop_end);
        return 0;
    }
    const char *base = strrchr(file, '/');
    dw4_sfp_bank banks[32];
    unsigned nb;
    base = base ? base + 1 : file;
    if (!strcasecmp(base, "allse.sfp")) {
        p = dw4_mount_data(mnt, "sbiallse.igb", &size);
        if (!p || (nb = dw4_sfp_scan(p, size, banks, 32)) != 1) return -1;
    } else {
        p = g->data; size = (uint32_t)g->size;
        nb = dw4_sfp_scan(p, size, banks, 32);
        if (nb > 32) return -1;
        dw4_sfp_bank_names(g, banks, nb);
        unsigned i;
        for (i = 0; i < nb; i++) if (!strcasecmp(base, banks[i].name)) break;
        if (i == nb) return -1;
        banks[0] = banks[i];
    }
    uint32_t wave;
    if (dw4_sfp_resolve(p, size, &banks[0], value(r, 6), &wave) ||
        resident(p, size, &banks[0], wave, c)) return -1;
    printf("  %s audio: %s -> %s sequence %u, waveform %u, %zu frames\n",
           label, r->name, base, value(r, 6) >> 16, wave, c->frames);
    return 0;
}
static dw4_frontaudio *prepare(dw4_mount *mnt, const char *stage,
                               const char *const *clip_names, unsigned count,
                               unsigned cue_start, const char *label)
{
    dw4_frontaudio *a = calloc(1, sizeof(*a));
    dw4_ref refs[8];
    unsigned nr;
    if (!a) return NULL;
    a->names = clip_names; a->count = count; a->cue_start = cue_start;
    nr = dw4_igfile_stage_refs(mnt, stage, refs, 8);
    for (unsigned i = 0; i < nr && i < 8; i++) {
        uint32_t size, list = 0;
        int base_volume = 0;
        const uint8_t *p = dw4_mount_entry(mnt, refs[i].pt, refs[i].entry, &size, NULL);
        dw4_igb g;
        if (!p || dw4_igb_open(&g, p, size, 0)) continue;
        if (dw4_igb_refs_open(&g)) { dw4_igb_close(&g); continue; }
        for (uint32_t off = g.chain2_off, n = 0; n < g.chain2_n; n++) {
            dw4_igb_record r;
            if (!dw4_igb_decode(&g, off, &r)) break;
            if (!strcmp(r.class_name, "beSoundInfo")) {
                list = value(&r, 7);
                base_volume = (int16_t)value(&r, 9);
                a->base_volume = base_volume;
            }
            if (!strcmp(r.class_name, "beSeInfoData")) actions(a, &g, &r);
            off = r.end; dw4_igb_record_free(&r);
        }
        if (list) for (uint32_t off = g.chain2_off, n = 0; n < g.chain2_n; n++) {
            dw4_igb_record r;
            if (!dw4_igb_decode(&g, off, &r)) break;
            if (!strcmp(r.class_name, "beSoundData") && r.name)
                for (unsigned k = 0; k < a->count; k++)
                    if (!strcmp(r.name, a->names[k]) && !a->clip[k].pcm) {
                        a->type[k] = (int16_t)value(&r, 4);
                        int stream = a->type[k] == 1 || a->type[k] == 2;
                        int volume = base_volume + (int16_t)value(&r, 8);
                        a->volume[k] = (int16_t)value(&r, 8);
                        a->gain[k] = stream ? dw4_audio_stream_gain(volume) : 1;
                        if (load(mnt, &g, list, &r, &a->clip[k], label))
                            fprintf(stderr, "%s audio: cannot load %s\n", label, a->names[k]);
                        else if (stream)
                            printf("  %s level: %s -> %d, gain %.6f\n", label, r.name, volume, a->gain[k]);
                    }
            off = r.end; dw4_igb_record_free(&r);
        }
        dw4_igb_close(&g);
        if (list) break;
    }
    for (unsigned k = 0; cue_start == 2 && k < 3; k++) if (!a->clip[k].pcm) {
        fprintf(stderr, "%s audio: missing %s\n", label, a->names[k]);
        dw4_frontaudio_close(a); return NULL;
    }
    return a;
}
dw4_frontaudio *dw4_frontaudio_prepare_lobby(dw4_mount *mnt){return dw4_frontaudio_prepare_lobby_stage(mnt,NULL);}
dw4_frontaudio *dw4_frontaudio_prepare_lobby_stage(dw4_mount *mnt,const char *stage)
{
    /* Terminal, Central and Shop share the Terminal bank's lobby cues; the Commander Room has its own bank and music. */
    int commander=stage && !strcasecmp(stage,"stagML02");
    dw4_frontaudio *a=commander?prepare(mnt,"stagml02.igb",commander_names,sizeof commander_names/sizeof *commander_names,2,"lobby"):
        prepare(mnt,"stagml11.igb",lobby_names,sizeof lobby_names/sizeof *lobby_names,2,"lobby");
    if(!a)return NULL;
    /* Borrow only menu SE metadata; lobby preparation must not decode title
     * music or start another device. */
    dw4_frontaudio *menu=prepare(mnt,"stagis10.igb",names+3,NAMES-3,0,"menu");
    if(!menu){dw4_frontaudio_close(a);return NULL;}
    for(unsigned k=3;k<a->count;k++)if(!a->clip[k].pcm){
        for(unsigned j=0;j<menu->count;j++)if(!strcmp(a->names[k],menu->names[j])){
            a->clip[k]=menu->clip[j];menu->clip[j]=(dw4_audio_clip){0};a->type[k]=menu->type[j];a->gain[k]=menu->gain[j];break;
        }
        if(!a->clip[k].pcm && k<LOBBY_REQUIRED){fprintf(stderr,"lobby menu audio: missing %s\n",a->names[k]);dw4_frontaudio_close(menu);dw4_frontaudio_close(a);return NULL;}
    }
    dw4_frontaudio_close(menu);return a;
}
dw4_frontaudio *dw4_frontaudio_prepare_stage(dw4_mount *mnt,const char *stage,const char *const *clip_names,unsigned count)
{return count && count<=CLIPS?prepare(mnt,stage,clip_names,count,CLIPS,"stage"):NULL;}   /* cue_start past every clip: no cues */
/* A gameplay stage's whole sound set from its catalogue (dw4/stagesound.h): every resident effect (types 3 and 4) and every
 * streamed track (types 1 and 2), named as the stage's records name them. Streams play on the music voice, or the ambience voice for
 * an AM_ name; effects take the cue voices. A cue that fails to decode stays silent (traced on stderr) and does not fail the stage. */
dw4_frontaudio *dw4_frontaudio_prepare_gameplay(dw4_mount *mnt,const char *stage)
{
    dw4_stagesound *cat=dw4_stagesound_open(mnt,stage);
    dw4_frontaudio *a;
    unsigned n=0;
    if(!cat)return NULL;
    a=calloc(1,sizeof *a);
    if(!a){dw4_stagesound_close(cat);return NULL;}
    a->owned=calloc(CLIPS,sizeof *a->owned);a->owned_ptr=calloc(CLIPS,sizeof *a->owned_ptr);
    if(!a->owned||!a->owned_ptr){free(a->owned);free(a->owned_ptr);free(a);dw4_stagesound_close(cat);return NULL;}
    a->names=a->owned_ptr;a->cue_start=0;a->open_set=1;
    for(unsigned i=0;i<POOL;i++){a->pool[i].adx=i<DW4_VOICEPOOL_ADX;a->pool[i].bank=i>=DW4_VOICEPOOL_ADX;}
    for(unsigned i=0;i<dw4_stagesound_count(cat) && n<CLIPS;i++){
        const dw4_stagesound_entry *e=dw4_stagesound_at(cat,i);
        int stream=e->type==1 || e->type==2;
        if(!stream && e->type!=3 && e->type!=4)continue;
        if(dw4_stagesound_find(cat,e->name)!=e)continue;   /* the first record of a name owns it */
        snprintf(a->owned[n],sizeof a->owned[n],"%s",e->name);a->owned_ptr[n]=a->owned[n];
        a->type[n]=e->type;
        a->adx_file[n]=e->file[0]=='[';
        a->priority[n]=(int16_t)e->priority;
        a->volume[n]=(int16_t)e->volume;a->base_volume=e->base_volume;
        /* Streams and effects whose file is an ADX entry are set to _volume + _baseVolume by the same level setter (FUN_003a6f70);
         * sound-bank effects play at full level (127) in retail, with _volume kept as the handle maximum. */
        a->gain[n]=stream||a->adx_file[n]?dw4_audio_stream_gain(e->base_volume+e->volume):1;
        if(dw4_stagesound_decode(cat,mnt,e,&a->clip[n],"gameplay"))fprintf(stderr,"gameplay audio: cannot load %s\n",e->name);
        else if(stream || a->adx_file[n])printf("  gameplay level: %s -> %d, gain %.6f\n",e->name,e->base_volume+e->volume,a->gain[n]);
        n++;
    }
    a->count=n;
    for(unsigned pk=0;pk<8;pk++){
        dw4_igb *g=dw4_stagesound_pack_igb(cat,pk);
        if(!g)continue;
        for(uint32_t off=g->chain2_off,k=0;k<g->chain2_n;k++){
            dw4_igb_record r;
            if(!dw4_igb_decode(g,off,&r))break;
            if(!strcmp(r.class_name,"beSeInfoData"))actions(a,g,&r);
            off=r.end;dw4_igb_record_free(&r);
        }
    }
    dw4_stagesound_close(cat);
    return a;
}
/* A demo stage's SOUND requests (stagML14 chunk 3): PLAYatPAUSE readies a named clip held, ISALLREADY reports the readied clips
 * decoded, PAUSEOFF starts it on its own voice; the DM queue owns the authored delays. A clip that failed to decode stays silent
 * (preparation logs it) and does not hold the script. */
int dw4_frontaudio_stage_service(void *user,const char *method,const dw4_script_value *args,size_t n,dw4_script_value *result,char *error,size_t cap)
{
    dw4_frontaudio *a=user;*result=(dw4_script_value){0};
    if(!a || n<4 || args[3].type!=DW4_SCRIPT_STRING || !args[3].string)goto bad;
    const char *key=args[3].string;
    if(!strcmp(method,"querySD") && n==4 && !strcmp(key,"ISALLREADY")){*result=(dw4_script_value){DW4_SCRIPT_NUMBER,1,NULL,0};return 0;}
    if(strcmp(method,"sd") || n!=5 || args[4].type!=DW4_SCRIPT_STRING || !args[4].string ||
       (strcmp(key,"PLAYatPAUSE") && strcmp(key,"PAUSEOFF")))goto bad;
    for(unsigned k=0;k<a->count;k++)if(!strcmp(args[4].string,a->names[k])){
        if(!strcmp(key,"PLAYatPAUSE")){a->held[k]=1;return 0;}
        if(!a->held[k]){snprintf(error,cap,"stage audio PAUSEOFF %s without PLAYatPAUSE",a->names[k]);return -1;}
        a->held[k]=0;
        if(a->clip[k].pcm){
            if(a->device)dw4_audio_play(a->device,k,&a->clip[k],a->gain[k]);
            a->voice[k].clip=k;a->voice[k].valid=1;a->voice[k].ducked=0;a->fade[k].level=1;
        }
        return 0;
    }
bad:snprintf(error,cap,"unsupported stage audio %s",method);return -1;
}
int dw4_frontaudio_stage_playing(const dw4_frontaudio *a,const char *name)
{
    if(!a || !name)return 0;
    for(unsigned k=0;k<a->count && k<8;k++)if(!strcmp(name,a->names[k]))return a->voice[k].valid && a->clip[k].pcm;
    return 0;
}
void dw4_frontaudio_start_lobby(dw4_frontaudio *a)
{
    if (!a || a->device) return;
    a->device = dw4_audio_open();
    if (!a->device) return;
    dw4_audio_play(a->device, 0, &a->clip[0], a->gain[0]);
    dw4_audio_play(a->device, 1, &a->clip[1], a->gain[1]);
    dw4_audio_resume(a->device);
}
int dw4_frontaudio_start_scripted(dw4_frontaudio *a)
{
    if(!a)return -1;
    if(!a->device)a->device=dw4_audio_open();
    if(!a->device)return -1;
    dw4_audio_resume(a->device);return 0;
}
/* Transfer the live mixer only after destination preparation succeeds. Stop
 * borrowed old clips before that scene can be freed, then publish the original
 * destination PLAY requests recorded during CPU preparation. */
int dw4_frontaudio_adopt_device(dw4_frontaudio *to,dw4_frontaudio *from)
{
    if(!to || !from || to==from || to->device)return -1;
    if(!from->device)return -1;
    for(unsigned v=0;v<FA_VOICES;v++)dw4_audio_stop(from->device,v);
    to->device=from->device;from->device=NULL;
    for(unsigned v=0;v<FA_VOICES;v++)if(to->voice[v].valid) {
        unsigned k=to->voice[v].clip;
        dw4_audio_play(to->device,v,&to->clip[k],to->voice[v].ducked?0:to->gain[k]*to->fade[v].level);
    }
    dw4_audio_resume(to->device);return 0;
}
/* SOUND BGMSTOP <name> and VOLUMECTL2 "<name>/F<from>/F<to>/F<ticks>" (the Commander Room's event music). Their engine receivers
 * are not recovered; this host policy stops the voice that plays the named clip, or ramps its gain multiplier linearly from..to
 * over the ticks of the 60 Hz session clock. A clip that is not playing is ignored: its voice is silent either way. */
static int music_control(dw4_frontaudio *a,const char *op,const char *value,char *error,size_t cap)
{
    char name[48];float from=1,to=1,ticks=0;
    const char *slash=strchr(value,'/');size_t len=slash?(size_t)(slash-value):strlen(value);
    if(!len || len>=sizeof name){snprintf(error,cap,"SOUND %s: bad clip name",op);return -1;}
    memcpy(name,value,len);name[len]=0;
    if(!strcmp(op,"VOLUMECTL2") && (!slash || sscanf(slash,"/F<%f>/F<%f>/F<%f>",&from,&to,&ticks)!=3 || ticks<0)){
        snprintf(error,cap,"SOUND VOLUMECTL2 %s: expected NAME/F<from>/F<to>/F<ticks>",value);return -1;
    }
    for(unsigned v=0;v<FA_VOICES;v++){
        if(!a->voice[v].valid || strcmp(a->names[a->voice[v].clip],name))continue;
        if(!strcmp(op,"BGMSTOP")){if(a->device)dw4_audio_stop(a->device,v);a->voice[v].valid=0;a->fade[v].active=0;continue;}
        unsigned k=a->voice[v].clip;
        a->fade[v].active=1;a->fade[v].from=from;a->fade[v].to=to;a->fade[v].level=from;a->fade[v].start_ns=a->clock_ns;
        a->fade[v].length_ns=(uint64_t)((double)ticks*1e9/60);a->fade[v].ramp=0;
        if(a->type[k]==1 || a->type[k]==2){
            /* Streams follow the retail ease-table ramp (beSound::vfunc_34 case 10 -> FUN_0037cf30 -> FUN_003a7590). */
            uint32_t fb,tb,db;float dv=ticks;memcpy(&fb,&from,4);memcpy(&tb,&to,4);memcpy(&db,&dv,4);
            memset(&a->fade[v].rp,0,sizeof a->fade[v].rp);a->fade[v].rp.base=a->volume[k];
            int level=dw4_ramp_start(&a->fade[v].rp,a->base_volume,fb,tb,db);
            float full=dw4_audio_stream_gain(a->base_volume+a->volume[k]),g=dw4_audio_stream_gain(level);
            a->fade[v].ramp=1;a->fade[v].frames=0;a->fade[v].level=full>0?g/full:from;
            if(a->device && !a->voice[v].ducked)dw4_audio_voice_gain(a->device,v,a->gain[k]*a->fade[v].level);
            continue;
        }
        if(a->device && !a->voice[v].ducked)dw4_audio_voice_gain(a->device,v,a->gain[a->voice[v].clip]*from);
    }
    return 0;
}
static void fades(dw4_frontaudio *a)
{
    for(unsigned v=0;v<FA_VOICES;v++)if(a->fade[v].active && a->voice[v].valid && a->fade[v].ramp){
        /* Retail ramp (FUN_003a7590/3a7890): one step per 60 Hz frame, level in 0.1 dB from base + volume. */
        uint64_t t=a->clock_ns>a->fade[v].start_ns?a->clock_ns-a->fade[v].start_ns:0,frames=t*60/1000000000ULL;
        unsigned k=a->voice[v].clip;
        int level=0,steps=0;
        while(a->fade[v].frames<frames && a->fade[v].rp.mode){
            level=dw4_ramp_step(&a->fade[v].rp,a->base_volume);a->fade[v].frames++;steps++;
        }
        if(steps && (a->type[k]==1 || a->type[k]==2) && a->fade[v].to==0.0f && level<-209){
            /* beCri::vfunc_27: a stream whose fade to 0 drops below -209 (0.1 dB) is stopped. */
            if(a->device)dw4_audio_stop(a->device,v);
            a->voice[v].valid=0;a->fade[v].active=0;a->fade[v].ramp=0;
            continue;
        }
        if(steps){
            float g=level<=-999?0:dw4_audio_stream_gain(level),full=dw4_audio_stream_gain(a->base_volume+a->volume[k]);
            a->fade[v].level=full>0?g/full:0;
            if(a->device && !a->voice[v].ducked)dw4_audio_voice_gain(a->device,v,a->gain[k]*a->fade[v].level);
        }
        if(!a->fade[v].rp.mode)a->fade[v].active=0;
    }
    for(unsigned v=0;v<FA_VOICES;v++)if(a->fade[v].active && a->voice[v].valid && !a->fade[v].ramp){
        uint64_t t=a->clock_ns>a->fade[v].start_ns?a->clock_ns-a->fade[v].start_ns:0;
        float f=a->fade[v].length_ns && t<a->fade[v].length_ns?(float)t/(float)a->fade[v].length_ns:1;
        a->fade[v].level=a->fade[v].from+(a->fade[v].to-a->fade[v].from)*f;
        if(a->device && !a->voice[v].ducked)dw4_audio_voice_gain(a->device,v,a->gain[a->voice[v].clip]*a->fade[v].level);
        if(f>=1)a->fade[v].active=0;
    }
}
int dw4_frontaudio_voice_clip(const dw4_frontaudio *a,unsigned voice,float *level)
{
    if(!a || voice>=FA_VOICES || !a->voice[voice].valid)return -1;
    if(level)*level=a->fade[voice].level;
    return (int)a->voice[voice].clip;
}
const char *dw4_frontaudio_clip_name(const dw4_frontaudio *a,int clip){return a && clip>=0 && (unsigned)clip<a->count?a->names[clip]:NULL;}
/* Native service for the original title model's sound event. */
#define FRAME_NS 16666667ULL
/* Retail stream player for a gameplay set (FUN_0037c2c0 + beSound case 2): a request for a busy slot fades the playing track down over 10
 * frames (if no ramp runs) and is retried 11 frames later; otherwise the track starts at volume + base. Without a device the request is
 * only recorded (private preparation), as before. Returns 0. */
static void arm_fade(dw4_frontaudio *a,unsigned v,float from,float to,float frames)
{
    uint32_t fb,tb,db;memcpy(&fb,&from,4);memcpy(&tb,&to,4);memcpy(&db,&frames,4);
    unsigned k=a->voice[v].clip;
    memset(&a->fade[v].rp,0,sizeof a->fade[v].rp);a->fade[v].rp.base=a->volume[k];
    dw4_ramp_start(&a->fade[v].rp,a->base_volume,fb,tb,db);
    a->fade[v].active=1;a->fade[v].ramp=1;a->fade[v].frames=0;a->fade[v].from=from;a->fade[v].to=to;a->fade[v].start_ns=a->clock_ns;
}
static int stream_play(dw4_frontaudio *a,unsigned k)
{
    unsigned v=a->type[k]==1?0:1;
    if(a->type[k]==1 && a->bgm_cur==(int)k+1)return 0;   /* the current BGM is not restarted */
    int playing=a->device?dw4_audio_voice_active(a->device,v):0;
    int fade_running=a->fade[v].active && a->fade[v].ramp && a->fade[v].rp.mode;
    dw4_stream_decision d;
    dw4_stream_decide(a->type[k],-1,playing?1:0,fade_running,a->clip[k].pcm!=NULL,0,a->volume[k],a->base_volume,a->pool_request,&d);
    for(int i=0;d.ops[i];i++){
        if(d.ops[i]==DW4_STREAM_FADE)arm_fade(a,v,1.0f,0.0f,10.0f);
    }
    if(playing && !d.seq){   /* busy: the dispatcher enqueues the PLAY again with an 11-frame delay */
        a->retry[v].clip=(int)k+1;a->retry[v].due_ns=a->clock_ns+11*FRAME_NS;
        return 0;
    }
    a->retry[v].clip=0;
    if(a->device && !d.seq)return 0;   /* the file did not start */
    a->pool_request=d.seq?d.seq:a->pool_request+1;
    if(a->device)dw4_audio_play(a->device,v,&a->clip[k],a->gain[k]);
    a->voice[v].handle=0;a->voice[v].clip=k;a->voice[v].valid=1;a->voice[v].ducked=0;a->fade[v].active=0;a->fade[v].ramp=0;a->fade[v].level=1;
    if(a->type[k]==1)a->bgm_cur=(int)k+1;
    a->stream_starts++;
    return 0;
}
/* Count a sound PLAY request (typed SCSound or script SOUND PLAY) and remember the last name that matched no prepared clip. */
static void note_request(dw4_frontaudio *a,const char *name,int resolved);
static void note_request(dw4_frontaudio *a,const char *name,int resolved)
{
    if(a->model_requests<16)snprintf(a->request_log[a->model_requests],sizeof a->request_log[0],"%s",name?name:"");
    a->model_requests++;
    if(!resolved){a->model_unresolved++;snprintf(a->last_unresolved,sizeof a->last_unresolved,"%s",name?name:"");}
}
int dw4_frontaudio_script_service(void *user, const char *method, const dw4_script_value *args,
                        size_t n, dw4_script_value *result, char *error, size_t cap)
{
    dw4_frontaudio *a = user;
    (void)result;
    if (!a) { snprintf(error,cap,"title audio unavailable"); return -1; }
    if(!strcmp(method,"sd") && n==4 && args[3].type==DW4_SCRIPT_STRING &&
       (!strcmp(args[3].string,"ONFREEZE") || !strcmp(args[3].string,"OFFREEZE"))){
        int freeze=!strcmp(args[3].string,"ONFREEZE");
        for(unsigned v=0;v<FA_VOICES;v++)if(a->voice[v].valid && a->type[a->voice[v].clip]==4){
            if(freeze){if(dw4_audio_voice_gain(a->device,v,0))a->voice[v].ducked=1;}
            else if(a->voice[v].ducked){dw4_audio_voice_gain(a->device,v,a->gain[a->voice[v].clip]);a->voice[v].ducked=0;}
        }return 0;
    }
    /* BGMSTOP, ENVSTOP and SESTOP read no cue name (beSound::vfunc_34 cases 6, 7, 8): they stop the BGM handle, the ambience handle and
     * the effect handles; only BGMSTOP clears the current BGM (finding #2763). */
    if(!strcmp(method,"sd") && n>=4 && args[3].type==DW4_SCRIPT_STRING &&
       (!strcmp(args[3].string,"BGMSTOP") || !strcmp(args[3].string,"ENVSTOP") || !strcmp(args[3].string,"SESTOP"))){
        unsigned first=0,last=0;
        if(!strcmp(args[3].string,"BGMSTOP")){first=last=0;a->bgm_cur=0;}
        else if(!strcmp(args[3].string,"ENVSTOP"))first=last=1;
        else if(a->open_set){first=POOL_ADX_VOICE;last=POOL_BANK_VOICE+DW4_VOICEPOOL_BANK-1;}
        else {first=3;last=7;}
        for(unsigned v=first;v<=last;v++){
            if(a->device)dw4_audio_stop(a->device,v);
            a->voice[v].valid=0;a->fade[v].active=0;
            if(a->open_set && v>=POOL_ADX_VOICE){unsigned i=v<POOL_BANK_VOICE?v-POOL_ADX_VOICE:DW4_VOICEPOOL_ADX+(v-POOL_BANK_VOICE);a->pool[i].play_id=0;}
        }
        return 0;
    }
    if(!strcmp(method,"sd") && n==5 && args[3].type==DW4_SCRIPT_STRING && args[4].type==DW4_SCRIPT_STRING && args[4].string &&
       (!strcmp(args[3].string,"BGMSTOP") || !strcmp(args[3].string,"VOLUMECTL2")))
        return music_control(a,args[3].string,args[4].string,error,cap);
    /* The Commander Room's first Ophanimon scene readies its music held (PLAYatPAUSE DM_OFNI), waits for querySD ISALLREADY
     * and releases it with PAUSEOFF on the first message, as the digivolution demo does (dw4_frontaudio_stage_service). The clip
     * is decoded during preparation, so it is always ready. */
    if((a->cue_start==2 || a->open_set) && !strcmp(method,"querySD") && n==4 && args[3].type==DW4_SCRIPT_STRING && !strcmp(args[3].string,"ISALLREADY")){
        *result=(dw4_script_value){DW4_SCRIPT_NUMBER,1,NULL,0};return 0;
    }
    /* ISREADY <name> (beSound case 12, FUN_0037dd10): 1 when the named stream or effect is ready, which it is here once decoded (the default of
     * the retail function when the name matches no live handle); the boss intros wait on it after PLAYatPAUSE (DMchkSD "==0" waits while it is 0). */
    if(a->open_set && !strcmp(method,"querySD") && n==5 && args[3].type==DW4_SCRIPT_STRING && !strcmp(args[3].string,"ISREADY")){
        *result=(dw4_script_value){DW4_SCRIPT_NUMBER,1,NULL,0};return 0;
    }
    int release=0;
    if((a->cue_start==2 || a->open_set) && !strcmp(method,"sd") && n==5 && args[3].type==DW4_SCRIPT_STRING && args[4].type==DW4_SCRIPT_STRING && args[4].string &&
       (!strcmp(args[3].string,"PLAYatPAUSE") || !strcmp(args[3].string,"PAUSEOFF"))){
        for(unsigned k=0;k<a->count;k++)if(!strcmp(args[4].string,a->names[k])){
            if(!strcmp(args[3].string,"PLAYatPAUSE")){a->held[k]=1;return 0;}
            if(!a->held[k]){snprintf(error,cap,"lobby audio PAUSEOFF %s without PLAYatPAUSE",a->names[k]);return -1;}
            a->held[k]=0;release=1;break;
        }
    }
    const char *tag=NULL;
    if(release)tag=args[4].string;
    if(!strcmp(method,"sd") && n>=4 && args[3].type==DW4_SCRIPT_STRING && !strcmp(args[3].string,"PLAY")){
        if(n==5 && args[4].type==DW4_SCRIPT_STRING)tag=args[4].string;
        else if(n==4 && args[1].type==DW4_SCRIPT_STRING)tag=args[1].string;
    }
    if(tag){
        unsigned found=0;
        for(unsigned k=0;k<a->count;k++)if(!strcmp(tag,a->names[k]) && a->clip[k].pcm)found=1;
        note_request(a,tag,found);
        for(unsigned k=0;k<a->count;k++)if(!strcmp(tag,a->names[k]) && a->clip[k].pcm){
            /* Streamed tracks past the first two (the Commander Room's alternative music and ambience) replace the music
             * (voice 0) or ambience (voice 1) voice instead of taking a one-shot cue voice. */
            unsigned v=k;
            if(a->open_set){
                if(a->type[k]!=1 && a->type[k]!=2){dw4_frontaudio_cue(a,tag);return 0;}
                return stream_play(a,k);   /* retail stream player: current-BGM check, busy slot -> fade-down + delayed retry (#2762, #2768) */
            }else if(k>=a->cue_start){
                if(a->cue_start!=2 || (a->type[k]!=1 && a->type[k]!=2)){dw4_frontaudio_cue(a,tag);return 0;}
                v=strncmp(tag,"AM_",3)?0:1;
            }
            dw4_audio_play(a->device,v,&a->clip[k],a->gain[k]);a->voice[v].handle=0;a->voice[v].clip=k;a->voice[v].valid=1;a->voice[v].ducked=0;a->fade[v].active=0;a->fade[v].level=1;
            return 0;
        }
    }
    snprintf(error, cap, "unsupported title audio command: %s %s %s", method,
        n>=4 && args[3].type==DW4_SCRIPT_STRING && args[3].string?args[3].string:"",
        n>=5 && args[4].type==DW4_SCRIPT_STRING && args[4].string?args[4].string:"");
    return -1;
}
static int load_sound_script(dw4_frontaudio *a, dw4_mount *mnt)
{
    uint32_t size;
    const uint8_t *blob = dw4_mount_entry(mnt, 0, 806, &size, NULL);
    dw4_igb g = {0};
    a->scripts = dw4_script_open(dw4_frontaudio_script_service, a);
    if (!a->scripts || !blob || dw4_igb_open(&g, blob, size, 0)) return -1;
    int rc = dw4_script_load_pack(a->scripts, &g);
    dw4_igb_close(&g);
    return rc < 0 ? -1 : 0;
}
static dw4_frontaudio *open_title(dw4_mount *mnt, int own_script)
{
    dw4_audio *device = dw4_audio_open();
    if (!device) return NULL;
    dw4_frontaudio *a = prepare(mnt, "stagis10.igb", names, NAMES, 3, "menu");
    if (!a) { dw4_audio_close(device); return NULL; }
    a->device = device;
    dw4_audio_play(a->device, 1, &a->clip[1], a->gain[1]);
    if (own_script && (load_sound_script(a, mnt) || dw4_script_run(a->scripts, "snd_j_startback.lua"))) {
        fprintf(stderr, "title Lua audio: %s\n", dw4_script_error(a->scripts));
        dw4_frontaudio_close(a); return NULL;
    }
    dw4_audio_resume(a->device);
    return a;
}
dw4_frontaudio *dw4_frontaudio_open(dw4_mount *mnt) { return open_title(mnt,1); }
dw4_frontaudio *dw4_frontaudio_open_session(dw4_mount *mnt) { return open_title(mnt,0); }
/* The title tracks and cues decode in about two seconds: the engine runs that part on a worker while the opening movie plays
 * (dw4_loadjob) and attaches the output device when the movie returns. */
void *dw4_frontaudio_prepare_work(void *mnt){return prepare((dw4_mount *)mnt,"stagis10.igb",names,NAMES,3,"menu");}
dw4_frontaudio *dw4_frontaudio_open_session_prepared(dw4_frontaudio *a)
{
    if (!a) return NULL;
    dw4_audio *device = dw4_audio_open();
    if (!device) { dw4_frontaudio_close(a); return NULL; }
    a->device = device;
    dw4_audio_play(a->device, 1, &a->clip[1], a->gain[1]);
    dw4_audio_resume(a->device);
    return a;
}
void dw4_frontaudio_set_clock(dw4_frontaudio *a, uint64_t clock_ns)
{
    if (!a) return;
    a->clock_ns = clock_ns;
    fades(a);
    for (unsigned v = 0; v < 2; v++)
        if (a->retry[v].clip && clock_ns >= a->retry[v].due_ns) {
            unsigned k = (unsigned)a->retry[v].clip - 1;
            a->retry[v].clip = 0;
            stream_play(a, k);
            fades(a);
        }
}
void dw4_frontaudio_tick(dw4_frontaudio *a, unsigned frame)
{
    /* Retail title Lua: ST_CHARA PLAYatPAUSE followed by PAUSEOFF at tick 239. */
    if (a && a->device && a->cue_start == 3 && !a->music_started && frame >= 239) {
        dw4_audio_play(a->device, 0, &a->clip[0], a->gain[0]); a->music_started = 1;
    }
}
int dw4_frontaudio_cue(dw4_frontaudio *a, const char *name)
{
    if (!a || !a->device || !name) return 0;
    for (unsigned k = a->cue_start; k < a->count; k++) if (!strcmp(name, a->names[k])) {
        if (!a->clip[k].pcm) return 0;
        int se = a->type[k] == 3 || a->type[k] == 4;
        if (se && !dw4_audio_repeat_allowed(&a->repeat[k], a->clock_ns)) return 0;
        if (a->open_set) {
            /* Retail beCri: the first idle handle of the right kind, else reuse by priority (FUN_0037c130). */
            int steal=0,kind=a->adx_file[k]?1:0;
            for(unsigned i=0;i<POOL;i++){
                unsigned pv=i<DW4_VOICEPOOL_ADX?POOL_ADX_VOICE+i:POOL_BANK_VOICE+(i-DW4_VOICEPOOL_ADX);
                if(a->pool[i].play_id && !dw4_audio_voice_active(a->device,pv)){a->pool[i].play_id=0;a->voice[pv].valid=0;}
            }
            int i=dw4_voicepool_pick(a->pool,POOL,kind,a->priority[k],a->pool_request,&steal);
            if(i<0)return 0;
            unsigned pv=(unsigned)i<DW4_VOICEPOOL_ADX?POOL_ADX_VOICE+(unsigned)i:POOL_BANK_VOICE+((unsigned)i-DW4_VOICEPOOL_ADX);
            if(steal)dw4_audio_stop(a->device,pv);
            dw4_audio_play(a->device,pv,&a->clip[k],a->gain[k]);
            a->voice[pv].handle=0;a->voice[pv].clip=k;a->voice[pv].valid=1;a->voice[pv].ducked=0;a->fade[pv].active=0;a->fade[pv].level=1;
            a->pool[i].play_id=++a->pool_request;a->pool[i].priority=a->priority[k];
            if (se) dw4_audio_repeat_started(&a->repeat[k], a->clock_ns);
            a->last_cue_voice=pv;
            return 1;
        }
        unsigned voice=3+a->cue_voice++%5;a->last_cue_voice=voice;
        dw4_audio_play(a->device,voice,&a->clip[k],a->gain[k]);a->voice[voice].handle=0;a->voice[voice].clip=k;a->voice[voice].valid=1;a->voice[voice].ducked=0;a->fade[voice].active=0;a->fade[voice].level=1;
        if (se) dw4_audio_repeat_started(&a->repeat[k], a->clock_ns);
        if (a->cue_start == 2) printf("  lobby audio cue: %s\n", name);
        return 1;
    }
    return 0;
}
const char *dw4_frontaudio_action_sound(const dw4_frontaudio *a, const char *model, const char *action)
{
    if (!a || !model || !action) return NULL;
    for (unsigned k = 0; k < a->naction; k++)
        if (!strcmp(model, a->action[k].model) && !strcmp(action, a->action[k].action) &&
            a->action[k].delay == 0) return a->action[k].sound;
    return NULL;
}
void dw4_frontaudio_action(dw4_frontaudio *a, const char *model, const char *action)
{
    const char *sound = dw4_frontaudio_action_sound(a, model, action);
    if (!sound) return;
    {   /* count the request like a PLAY: the sound table named a cue; does a prepared clip answer to it? */
        int found = 0;
        for (unsigned k = 0; k < a->count; k++) if (!strcmp(sound, a->names[k]) && a->clip[k].pcm) found = 1;
        note_request(a, sound, found);
    }
    dw4_frontaudio_cue(a, sound);
}
int dw4_frontaudio_model_play(dw4_frontaudio *a,const char *name,int64_t *handle,int *type)
{
    if(!handle || !type)return -1;
    *handle=0;*type=0;if(!a || !name)return -1;
    unsigned k=0;while(k<a->count && strcmp(name,a->names[k]))k++;
    if(k==a->count || !a->clip[k].pcm){note_request(a,name,0);return -1;}
    if(a->type[k]==3 || a->type[k]==4)note_request(a,name,1);   /* stream PLAY is counted by the script service it calls */
    *type=a->type[k];
    if(a->type[k]==3 || a->type[k]==4){
        if(!dw4_frontaudio_cue(a,name))return 0;
        unsigned v=a->last_cue_voice;
        /* Positive signed tokens are opaque service handles, never pointers.
         * Do not reuse one after overflow while this media owner is live. */
        if(a->next_handle==INT64_MAX)return -1;
        *handle=a->voice[v].handle=(int64_t)++a->next_handle;return 0;
    }
    /* Stream PLAY has no retained SCSound handle. */
    dw4_script_value args[]={{DW4_SCRIPT_STRING,0,"SOUND",5},{0},{DW4_SCRIPT_NUMBER,-1,NULL,0},
        {DW4_SCRIPT_STRING,0,"PLAY",4},{DW4_SCRIPT_STRING,0,name,strlen(name)}},result={0};char error[128];
    return dw4_frontaudio_script_service(a,"sd",args,5,&result,error,sizeof error);
}
const char *dw4_frontaudio_current_bgm(const dw4_frontaudio *a){return a && a->bgm_cur>0?a->names[a->bgm_cur-1]:NULL;}
unsigned dw4_frontaudio_stream_starts(const dw4_frontaudio *a){return a?a->stream_starts:0;}
float dw4_frontaudio_clip_gain(const dw4_frontaudio *a,const char *name)
{
    for(unsigned k=0;a && name && k<a->count;k++)if(!strcmp(name,a->names[k]))return a->gain[k];
    return -1;
}
const char *dw4_frontaudio_request_name(const dw4_frontaudio *a,unsigned index){return a && index<a->model_requests && index<16?a->request_log[index]:NULL;}
void dw4_frontaudio_model_stats(const dw4_frontaudio *a,unsigned *requests,unsigned *unresolved,const char **last)
{
    if(requests)*requests=a?a->model_requests:0;
    if(unresolved)*unresolved=a?a->model_unresolved:0;
    if(last)*last=a && a->model_unresolved?a->last_unresolved:NULL;
}
int dw4_frontaudio_model_down(dw4_frontaudio *a,int64_t handle)
{
    if(!a)return -1;
    for(unsigned v=0;v<FA_VOICES;v++)if(a->voice[v].valid && a->voice[v].handle==handle){
        a->fade[v].active=1;a->fade[v].from=1;a->fade[v].to=0;a->fade[v].level=1;
        a->fade[v].start_ns=a->clock_ns;a->fade[v].length_ns=10*16666666ULL;
        return 0;
    }
    return 0; /* An ended/replaced voice makes the old handle inert. */
}
void dw4_frontaudio_close(dw4_frontaudio *a)
{
    if (!a) return;
    dw4_script_close(a->scripts);
    dw4_audio_close(a->device);
    for (unsigned k = 0; k < CLIPS; k++) dw4_audio_clip_free(&a->clip[k]);
    free(a->owned); free(a->owned_ptr);
    free(a);
}
