#define _DEFAULT_SOURCE
#include "dw4/audio.h"
#include "dw4/frontaudio.h"
#include "dw4/lobby.h"
#include "dw4/window.h"
#include "dw4/sfp.h"
#include "dw4/simulation.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

static double monotonic_seconds(void)
{struct timespec t;assert(!clock_gettime(CLOCK_MONOTONIC,&t));return (double)t.tv_sec+t.tv_nsec*1e-9;}
int main(int argc, char **argv)
{
    const int16_t mono[] = { 12000, -12000, 6000, -6000 };
    dw4_audio_clip c = {0};
    if (argc > 2 && !strcmp(argv[2], "mute")) dw4_audio_set_muted(1);
    dw4_mount m;
    if (!dw4_window_built()) { puts("audio: SDL2 not built; skipped"); return 0; }
    assert(!dw4_audio_from_mono(mono, 4, 24000, &c));
    assert(c.frames == 8 && c.pcm);
    for (size_t i = 0; i < c.frames; i++) assert(c.pcm[i * 2] == c.pcm[i * 2 + 1]);
    c.loop_start = 2; c.loop_end = 6;
    /* Device lifecycle, sample clock advancement and reset across two movies. */
    for (int i = 0; i < 2; i++) {
        dw4_audio *a = dw4_audio_open();
        assert(a && dw4_audio_seconds(a) == 0);
        dw4_audio_play(a, 0, &c, 1);
        double started=monotonic_seconds();dw4_audio_resume(a);
        usleep(100000);
        double seconds=dw4_audio_seconds(a);
        while(seconds<=0.04 && monotonic_seconds()-started<2){usleep(2000);seconds=dw4_audio_seconds(a);}
        double elapsed=monotonic_seconds()-started;
        /* A busy host may return late from usleep. Compare against measured
         * elapsed time, allowing the dummy device's block scheduling granularity. */
        assert(seconds>0.04 && seconds<elapsed*1.2+0.1);
        dw4_audio_stop(a, 0);
        dw4_audio_close(a);
    }
    dw4_audio_clip_free(&c);
    assert(!dw4_mount_open(&m, argc > 1 ? argv[1] : "../local/extracted"));
    /* The global bank's packed sequence tags select a note, then a waveform.
     * Sequence 7 is a two-event sound and must not be flattened to one note. */
    uint32_t bank_size, wave;
    const uint8_t *bank_data = dw4_mount_entry(&m, 0, 897, &bank_size, NULL);
    dw4_sfp_bank banks[2];
    assert(bank_data && dw4_sfp_scan(bank_data, bank_size, banks, 2) == 1);
    assert(!dw4_sfp_resolve(bank_data, bank_size, banks, 0x000102a9, &wave) && wave == 29);
    assert(!dw4_sfp_resolve(bank_data, bank_size, banks, 0x000802a9, &wave) && wave == 47);
    assert(dw4_sfp_resolve(bank_data, bank_size, banks, 0x000702a9, &wave));
    assert(dw4_sfp_resolve(bank_data, bank_size, banks, 0xffff02a9, &wave));
    assert(dw4_sfp_resolve(bank_data, bank_size, banks, 0x000149a9, &wave));
    assert(dw4_sfp_resolve(bank_data, banks[0].vag_off - 1, banks, 0x000102a9, &wave));
    dw4_frontaudio *front = dw4_frontaudio_open(&m);
    assert(front);
    /* SCSound uses a full service token, and DOWN follows the simulation
     * clock for ten retail frames. A reused voice rejects its old token. */
    dw4_frontaudio_set_clock(front,100000000);
    int type;int64_t token;assert(!dw4_frontaudio_model_play(front,"CURSOR_START",&token,&type) && token>0 && type==3);
    assert(!dw4_frontaudio_model_down(front,token));
    dw4_frontaudio_set_clock(front,183333330);float level=0;
    assert(dw4_frontaudio_voice_clip(front,3,&level)>=0 && level>.49f && level<.51f);
    dw4_frontaudio_set_clock(front,183333330);assert(dw4_frontaudio_voice_clip(front,3,&level)>=0 && level>.49f && level<.51f);
    dw4_frontaudio_set_clock(front,266666660);assert(dw4_frontaudio_voice_clip(front,3,&level)>=0 && level==0);
    int64_t old=token;
    for(unsigned k=0;k<5;k++){
        dw4_frontaudio_set_clock(front,300000000+50000000*k);
        assert(!dw4_frontaudio_model_play(front,"CURSOR_START",&token,&type) && token>old);
    }
    assert(!dw4_frontaudio_model_down(front,old));dw4_frontaudio_set_clock(front,800000000);
    assert(dw4_frontaudio_voice_clip(front,3,&level)>=0 && level==1);
    assert(dw4_frontaudio_model_play(front,"not-a-prepared-sound",&token,&type)<0);
    /* Expected selection cues are from pack 805 beSeData, not button guesses. */
    const char *mapping[][3] = {
        {"j_startmenu02", "LINEUP00", "CURSOR_MOVE2"},
        {"j_startmenu02", "LINEDW01", "CURSOR_MOVE2"},
        {"j_startmenu02", "LINEON00", "CURSOR_START"},
        {"j_optioncursor11", "MOVE", "CURSOR_MOVE2"},
        {"j_optioncursor12", "MOVE", "CURSOR_MOVE"},
        {"j_digifacewin", "CHANGE", "WINDOW_CLOSE2"},
        {"j_chrselmesswin", "LINEON01", "CURSOR_DECIDE"},
        {"j_namecursorus", "NAMEON07", "CURSOR_DECIDE"},
        {"j_namecursorus", "NAMECG07", "CURSOR_MOVE"},
        {"j_mainstatuswin", "LINEON00", "CURSOR_START"},
    };
    for (size_t i = 0; i < sizeof(mapping) / sizeof(mapping[0]); i++) {
        const char *sound = dw4_frontaudio_action_sound(front, mapping[i][0], mapping[i][1]);
        assert(sound && !strcmp(sound, mapping[i][2]));
    }
    assert(!dw4_frontaudio_action_sound(front, "j_startmenu02", "unknown"));
    assert(!dw4_frontaudio_action_sound(front, "unknown", "MOVE"));
    dw4_frontaudio_tick(front, 239);
    dw4_frontaudio_set_clock(front, 1000000000);
    assert(dw4_frontaudio_cue(front, "CURSOR_START"));
    assert(!dw4_frontaudio_cue(front, "CURSOR_START"));
    /* Same simulation time remains suppressed even while the device advances. */
    usleep(60000);
    assert(!dw4_frontaudio_cue(front, "CURSOR_START"));
    assert(dw4_frontaudio_cue(front, "CURSOR_MOVE2")); /* different cue is independent */
    dw4_frontaudio_set_clock(front, 1049999997);
    assert(!dw4_frontaudio_cue(front, "CURSOR_START"));
    dw4_frontaudio_set_clock(front, 1049999998);
    assert(dw4_frontaudio_cue(front, "CURSOR_START"));
    assert(!dw4_frontaudio_cue(front, "not-a-sound"));
    dw4_frontaudio_cue(front, "CURSOR_MOVE");
    dw4_frontaudio_cue(front, "CURSOR_DECIDE");
    dw4_frontaudio_cue(front, "CURSOR_CANCEL");
    usleep(200000);
    dw4_frontaudio_close(front);
    /* The live owner publishes the original sound event through DM. */
    front=dw4_frontaudio_open_session(&m);assert(front);
    dw4_be_state script_state;dw4_be_init(&script_state);
    dw4_scriptengine *scripts=dw4_scriptengine_open(&script_state,
        dw4_frontaudio_script_service,front);assert(scripts);
    uint32_t script_size;
    const uint8_t *script_data=dw4_mount_entry(&m,0,806,&script_size,NULL);
    dw4_igb script_pack={0};
    assert(script_data && !dw4_igb_open(&script_pack,script_data,script_size,0));
    assert(dw4_script_load_pack(dw4_scriptengine_vm(scripts),&script_pack)>0);
    dw4_igb_close(&script_pack);
    assert(!dw4_scriptengine_run(scripts,"func.lua"));
    assert(!dw4_scriptengine_queue_event(scripts,"snd_j_startback.lua"));
    dw4_simulation simulation;dw4_simulation_init(&simulation,scripts,NULL,NULL);
    assert(dw4_simulation_due(&simulation,0)==1);
    dw4_simulation_hold(&simulation,DW4_HOLD_PAUSE,0);
    assert(!dw4_simulation_due(&simulation,1000000000));
    assert(dw4_scriptengine_pending(scripts)==1);
    dw4_simulation_hold(&simulation,0,1000000000);
    assert(dw4_simulation_due(&simulation,1016666667)==1);
    assert(!dw4_simulation_step(&simulation) && !dw4_scriptengine_pending(scripts));
    dw4_scriptengine_close(scripts);dw4_frontaudio_close(front);
    /* Preparing lobby clips must not open a device in the loading worker. */
    const char *driver = getenv("SDL_AUDIODRIVER");
    char *saved_driver = driver ? strdup(driver) : NULL;
    assert(!setenv("SDL_AUDIODRIVER", "dw4-invalid-driver", 1));
    dw4_frontaudio *prepared = dw4_frontaudio_prepare_lobby(&m);
    assert(prepared);
    dw4_frontaudio_cue(prepared, "mlBEEP01"); /* safe before publication */
    dw4_script_value sounds[]={ {DW4_SCRIPT_STRING,0,"SOUND",5},{0},{DW4_SCRIPT_NUMBER,-1,NULL,0},{DW4_SCRIPT_STRING,0,"ONFREEZE",8},{0}},reply;char sound_error[256];
    assert(!dw4_frontaudio_script_service(prepared,"sd",sounds,4,&reply,sound_error,sizeof sound_error));
    sounds[3]=(dw4_script_value){DW4_SCRIPT_STRING,0,"PLAY",4};sounds[4]=(dw4_script_value){DW4_SCRIPT_STRING,0,"CURSOR_NG",9};
    assert(!dw4_frontaudio_script_service(prepared,"sd",sounds,5,&reply,sound_error,sizeof sound_error));
    sounds[3]=(dw4_script_value){DW4_SCRIPT_STRING,0,"OFFREEZE",8};
    assert(!dw4_frontaudio_script_service(prepared,"sd",sounds,4,&reply,sound_error,sizeof sound_error));
    assert(!strcmp(dw4_frontaudio_action_sound(prepared,"i_messwn","OPEN"),"WINDOW_OPEN"));
    assert(!strcmp(dw4_frontaudio_action_sound(prepared,"i_messwn","CLOSE"),"WINDOW_CLOSE"));
    assert(!strcmp(dw4_frontaudio_action_sound(prepared,"i_stcursor01","LINEUP00"),"CURSOR_MOVE"));
    assert(!strcmp(dw4_frontaudio_action_sound(prepared,"i_stfolder","AWINON"),"WINDOW_OPEN"));
    assert(!strcmp(dw4_frontaudio_action_sound(prepared,"i_stmenu01","CLOSE"),"WINDOW_CLOSE"));
    dw4_frontaudio_close(prepared); /* cancellation before publication */
    if (saved_driver) { assert(!setenv("SDL_AUDIODRIVER", saved_driver, 1)); free(saved_driver); }
    else assert(!unsetenv("SDL_AUDIODRIVER"));
    dw4_lobby *lobby = dw4_lobby_open(&m, 0, "Audio");
    assert(lobby && !dw4_lobby_prepare_audio(lobby, &m));
    dw4_lobby_start_audio(lobby);
    dw4_lobby_start_audio(lobby); /* publication is idempotent */
    unsigned ticks = 0, beep_wait = 0;
    int closed48 = 0, seen49 = 0;
    while (!dw4_lobby_intro_done(lobby) && ticks++ < 2000) {
        int page = dw4_lobby_message(lobby);
        if (page == 48) closed48 = 1;
        if (closed48 && page == -1 && !seen49) beep_wait++;
        if (page == 49) seen49 = 1;
        dw4_lobby_tick(lobby, 1); /* also exercise ignored transition input */
    }
    assert(dw4_lobby_intro_done(lobby) && seen49 && beep_wait == 16 + 90 + 16);
    for (unsigned i = 0; i < 60; i++) dw4_lobby_tick(lobby, 1);
    usleep(100000);
    dw4_lobby_close(lobby);
    dw4_mount_close(&m);
    puts("audio: resampling, device clock/reset, menu assets and cleanup ok");
    return 0;
}
