#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include "dw4/audio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int default_muted;
void dw4_audio_set_muted(int muted) { default_muted = muted != 0; }

#ifdef DW4_ENABLE_SDL2
#include <SDL.h>
#define VOICES 64   /* music, ambience, the legacy cue voices and the 4 + 48 effect handles of the gameplay pool */
struct dw4_audio {
    SDL_AudioDeviceID device;
    struct { const dw4_audio_clip *clip; size_t pos; float gain; } voice[VOICES];
    uint64_t frames, stamp;
    unsigned quantum;
    int muted;
};
static void mix(void *userdata, Uint8 *stream, int len)
{
    dw4_audio *a = userdata;
    int16_t *out = (int16_t *)stream;
    unsigned i, v, n = (unsigned)len / 4;
    memset(stream, 0, (size_t)len);
    for (i = 0; i < n; i++) {
        float left = 0, right = 0;
        for (v = 0; v < VOICES; v++) {
            const dw4_audio_clip *c = a->voice[v].clip;
            size_t p = a->voice[v].pos;
            if (!c) continue;
            if (c->loop_end && p >= c->loop_end) p = c->loop_start;
            if (p >= c->frames) { a->voice[v].clip = NULL; continue; }
            left += c->pcm[p * 2] * a->voice[v].gain;
            right += c->pcm[p * 2 + 1] * a->voice[v].gain;
            a->voice[v].pos = p + 1;
        }
        out[i * 2] = (int16_t)(left > 32767 ? 32767 : left < -32768 ? -32768 : left);
        out[i * 2 + 1] = (int16_t)(right > 32767 ? 32767 : right < -32768 ? -32768 : right);
    }
    if (a->muted) memset(stream, 0, (size_t)len);
    a->frames += n;
    a->quantum = n;
    a->stamp = SDL_GetPerformanceCounter();
}
dw4_audio *dw4_audio_open(void)
{
    dw4_audio *a;
    SDL_AudioSpec want = {0};
    if (SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) {
        fprintf(stderr, "audio: unavailable: %s\n", SDL_GetError());
        return NULL;
    }
    a = calloc(1, sizeof(*a));
    if (!a) { SDL_QuitSubSystem(SDL_INIT_AUDIO); return NULL; }
    a->muted = default_muted;
    want.freq = 48000; want.format = AUDIO_S16SYS; want.channels = 2;
    want.samples = 512; want.callback = mix; want.userdata = a;
    a->device = SDL_OpenAudioDevice(NULL, 0, &want, NULL, 0);
    if (!a->device) {
        fprintf(stderr, "audio: unavailable: %s\n", SDL_GetError());
        free(a); SDL_QuitSubSystem(SDL_INIT_AUDIO); return NULL;
    }
    return a;
}
void dw4_audio_resume(dw4_audio *a) { if (a) SDL_PauseAudioDevice(a->device, 0); }
void dw4_audio_play(dw4_audio *a, unsigned v, const dw4_audio_clip *c, float gain)
{
    if (!a || v >= VOICES) return;
    SDL_LockAudioDevice(a->device);
    a->voice[v].clip = c; a->voice[v].pos = 0; a->voice[v].gain = gain;
    SDL_UnlockAudioDevice(a->device);
}
void dw4_audio_stop(dw4_audio *a, unsigned v) { dw4_audio_play(a, v, NULL, 0); }
int dw4_audio_voice_gain(dw4_audio *a,unsigned v,float gain)
{
    if(!a || v>=VOICES)return 0;
    SDL_LockAudioDevice(a->device);int active=a->voice[v].clip!=NULL;
    if(active)a->voice[v].gain=gain;
    SDL_UnlockAudioDevice(a->device);return active;
}
int dw4_audio_voice_active(dw4_audio *a, unsigned v)
{
    int active;
    if (!a || v >= VOICES) return 0;
    SDL_LockAudioDevice(a->device);
    active = a->voice[v].clip != NULL;
    SDL_UnlockAudioDevice(a->device);
    return active;
}
double dw4_audio_seconds(dw4_audio *a)
{
    double t = 0;
    if (!a) return 0;
    SDL_LockAudioDevice(a->device);
    if (a->stamp) {
        double delta = (double)(SDL_GetPerformanceCounter() - a->stamp) / SDL_GetPerformanceFrequency();
        double block = (double)a->quantum / 48000;
        /* Interpolate within the last submitted buffer. Hardware latency beyond
         * this SDL buffer is backend-dependent, so this is a media clock estimate. */
        t = (double)(a->frames - a->quantum) / 48000 + (delta < block ? delta : block);
    }
    SDL_UnlockAudioDevice(a->device);
    return t;
}
void dw4_audio_close(dw4_audio *a)
{
    if (!a) return;
    SDL_CloseAudioDevice(a->device); /* joins callback before releasing clips */
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
    free(a);
}
int dw4_audio_from_mono(const int16_t *pcm, size_t frames, int rate, dw4_audio_clip *c)
{
    SDL_AudioCVT cvt;
    memset(c, 0, sizeof(*c));
    if (frames > 16u * 1024u * 1024u || rate <= 0 ||
        SDL_BuildAudioCVT(&cvt, AUDIO_S16SYS, 1, rate, AUDIO_S16SYS, 2, 48000) < 0)
        return -1;
    cvt.len = (int)(frames * 2);
    cvt.buf = malloc((size_t)cvt.len * cvt.len_mult);
    if (!cvt.buf) return -1;
    memcpy(cvt.buf, pcm, (size_t)cvt.len);
    if (SDL_ConvertAudio(&cvt) < 0) { free(cvt.buf); return -1; }
    c->pcm = (int16_t *)cvt.buf; c->frames = (size_t)cvt.len_cvt / 4;
    return 0;
}
#else
dw4_audio *dw4_audio_open(void) { fprintf(stderr, "audio: SDL2 backend not built\n"); return NULL; }
void dw4_audio_resume(dw4_audio *a) { (void)a; }
void dw4_audio_close(dw4_audio *a) { (void)a; }
void dw4_audio_play(dw4_audio *a, unsigned v, const dw4_audio_clip *c, float g)
{ (void)a; (void)v; (void)c; (void)g; }
void dw4_audio_stop(dw4_audio *a, unsigned v) { (void)a; (void)v; }
int dw4_audio_voice_gain(dw4_audio *a,unsigned v,float gain) { (void)a;(void)v;(void)gain;return 0; }
int dw4_audio_voice_active(dw4_audio *a, unsigned v) { (void)a; (void)v; return 0; }
double dw4_audio_seconds(dw4_audio *a) { (void)a; return 0; }
static void wav_u32(uint8_t *p,uint32_t v)
{for(unsigned i=0;i<4;i++)p[i]=(uint8_t)(v>>(8*i));}
int dw4_audio_from_mono(const int16_t *p, size_t f, int r, dw4_audio_clip *c)
{
    memset(c,0,sizeof *c);
    if(!p || !f || f>16u*1024u*1024u || r<=0 || r>536870911)return -1;
    size_t bytes=44+4*f;uint8_t *wav=calloc(bytes,1);if(!wav)return -1;
    memcpy(wav,"RIFF",4);wav_u32(wav+4,(uint32_t)bytes-8);memcpy(wav+8,"WAVEfmt ",8);
    wav_u32(wav+16,16);wav[20]=1;wav[22]=2;wav_u32(wav+24,(uint32_t)r);wav_u32(wav+28,(uint32_t)r*4);
    wav[32]=4;wav[34]=16;memcpy(wav+36,"data",4);wav_u32(wav+40,(uint32_t)f*4);
    for(size_t i=0;i<f;i++)for(unsigned channel=0;channel<2;channel++){wav[44+4*i+2*channel]=(uint8_t)p[i];wav[45+4*i+2*channel]=(uint8_t)((uint16_t)p[i]>>8);}
    int result=dw4_audio_decode_blob(wav,bytes,c);free(wav);return result;
}
#endif

void dw4_audio_clip_free(dw4_audio_clip *c)
{ if (c) { free(c->pcm); memset(c, 0, sizeof(*c)); } }

int dw4_audio_decode(const char *path, dw4_audio_clip *c)
{
    char cmd[4096];
    FILE *pipe;
    size_t cap = 0, used = 0;
    uint8_t *pcm = NULL, chunk[16384];
    int status, failed = 0;
    memset(c, 0, sizeof(*c));
    /* Only private mkstemp paths are passed by runtime callers. */
    if (!path || strchr(path, '\'') || strlen(path) > 3000) return -1;
    snprintf(cmd, sizeof(cmd), "ffmpeg -v error -nostdin -i '%s' -map 0:a:0 "
             "-ac 2 -ar 48000 -f s16le - 2>/dev/null", path);
    pipe = popen(cmd, "r");
    if (!pipe) return -1;
    for (;;) {
        size_t n = fread(chunk, 1, sizeof(chunk), pipe);
        if (!n) break;
        /* Bounded preroll: the longest retail track fits comfortably in 128 MiB.
         * Keep draining on failure so pclose cannot deadlock on a full pipe. */
        if (failed) continue;
        if (used + n > 128u * 1024u * 1024u) { failed = 1; continue; }
        if (used + n > cap) {
            size_t next = cap ? cap * 2 : sizeof(chunk);
            void *p = realloc(pcm, next);
            if (!p) { failed = 1; continue; }
            pcm = p; cap = next;
        }
        memcpy(pcm + used, chunk, n); used += n;
    }
    failed |= ferror(pipe) != 0;
    status = pclose(pipe);
    if (failed || status || !used || used % 4) { free(pcm); return -1; }
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    for (size_t i = 0; i < used; i += 2) {
        uint8_t tmp = pcm[i]; pcm[i] = pcm[i + 1]; pcm[i + 1] = tmp;
    }
#endif
    c->pcm = (int16_t *)pcm; c->frames = used / 4;
    return 0;
}

int dw4_audio_decode_blob(const uint8_t *data, size_t size, dw4_audio_clip *c)
{
    char path[] = "/tmp/dw4audioXXXXXX";
    int fd = mkstemp(path), rc = -1;
    size_t done = 0;
    memset(c, 0, sizeof(*c));
    if (fd < 0) return -1;
    while (done < size) {
        ssize_t n = write(fd, data + done, size - done);
        if (n <= 0) break;
        done += (size_t)n;
    }
    close(fd);
    if (done == size) rc = dw4_audio_decode(path, c);
    unlink(path);
    return rc;
}
