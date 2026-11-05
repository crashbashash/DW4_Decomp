#include "dw4/titlehost.h"
#include "../src/arenalist.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static void tick(dw4_title_host *h, unsigned dir, unsigned pressed)
{
    Dw4TitleInput p = {dir, 0, pressed, 0};
    dw4_title_host_tick(h, &p, 1);
    assert(!h->error);
}
static int ready(const dw4_title_host *h, int state)
{
    if (h->ctrl._st0 != state) return 0;
    if (state == 1) return h->ctrl._st1 == 2 && h->ctrl._st2 == 1 && h->ctrl._st3 == 0;
    if (state == 2) return h->ctrl._st1 == 1 && h->ctrl._st2 == 1;
    return h->ctrl._st1 == 1 && h->ctrl._st2 == 0;
}
static void wait_ready(dw4_title_host *h, int state)
{
    int n = 500;
    while (!ready(h, state) && n--) tick(h, 0, 0);
    assert(ready(h, state));
}
static void menu(dw4_title_host *h)
{
    wait_ready(h, 1);
    tick(h, 0, 0x4000); /* Cross must not stand in for Start. */
    assert(ready(h, 1));
    tick(h, 0, 8);
    wait_ready(h, 2);
}
static void count_logo_action(void *p,int action)
{
    int *counts=p;
    assert(action==LOGO_OPEN || action==LOGO_CLOSE);
    ++counts[action==LOGO_CLOSE];
}
static void logo_waits(void)
{
    dw4_logo_seq s={0};int counts[2]={0},i;
    dw4_logo_hooks hooks={counts,count_logo_action,NULL};
    dw4_logo_start(&s,LOGO_SQ_OPEN,&hooks);
    assert(s.wait && s.refs==1 && s.index==2 && counts[0]==1);
    for(i=0;i<100;++i) {
        dw4_logo_tick(&s,0,&hooks);
        assert(s.sequence==LOGO_SQ_OPEN && s.wait && !s.removed);
    }
    dw4_logo_tick(&s,256,&hooks); /* Action uses full result, not low byte. */
    assert(s.sequence==LOGO_SQ_WAIT && !s.wait && !s.refs && !s.removed);
    dw4_logo_tick(&s,-1,&hooks);
    assert(s.sequence==LOGO_SQ_WAIT && counts[0]==1);
    dw4_logo_start(&s,LOGO_SQ_CLOSE,&hooks);
    dw4_logo_tick(&s,0,&hooks);
    dw4_logo_start(&s,LOGO_SQ_OPEN,&hooks); /* interruption retains exactly one string ref */
    assert(s.wait && s.refs==1 && counts[0]==2 && counts[1]==1);
    dw4_logo_tick(&s,2,&hooks);
    assert(s.sequence==LOGO_SQ_WAIT && !s.removed && !s.wait);
    dw4_logo_start(&s,LOGO_SQ_CLOSE,&hooks);
    dw4_logo_tick(&s,-256,&hooks);
    assert(s.sequence==LOGO_SQ_ERAS && s.removed && !s.wait && !s.refs);
    dw4_logo_start(&s,LOGO_SQ_OPEN,&hooks);
    assert(!s.removed && s.wait && s.refs==1 && !s.error);
    dw4_logo_seq bad={0};
    dw4_logo_start(&bad,123,&hooks);
    assert(bad.error); /* no successful completion for unsupported sequences */
}
static void action2_arena_records(void)
{
    dw4_arena *a=dw4_session_arena();unsigned before=dw4_arena_live(a,DW4_REGION_PERSISTENT);
    for(int i=0;i<128;i++){
        dw4_action2_host h;dw4_action2_host_init(&h);assert(!h.error);
        dw4_action2_record r=dw4_action2_host_records(&h);
        beAction2InfoRam *ram=DW4_ARENA_OBJ(a,beAction2InfoRam,r.ram);
        beAction2InfoWork *work=DW4_ARENA_OBJ(a,beAction2InfoWork,r.work);
        beAction2Data *data=DW4_ARENA_OBJ(a,beAction2Data,r.data);
        assert(r.arena==a && ram->_work==(int32_t)r.work.off && ram->_node==(int32_t)r.node.off);
        assert(ram->_parentInfo==(int32_t)r.info.off && ram->_parentManager==(int32_t)r.manager.off);
        dw4_action2_component c={DW4_A2_WAITCHECK,"Frame",0x41200000,0,""};
        dw4_action2_host_start_program(&h,&c,1,0);assert(!h.error && work->_waitSt0==1);
        assert(!dw4_action2_host_set_name(&h,"TEST") && !strcmp(dw4_action2_host_name(&h),"TEST"));
        assert(work->_comData==(int32_t)r.data.off && al_count(a,data->_comList)==1);
        int32_t child=al_words(a,data->_comList)[0];
        assert(dw4_arena_object_is(a,al_handle(child),dw4_metaobject_find("beAction2WAITCHECK")->vtable));
        beBaseInfoRamTimer *timer=DW4_ARENA_OBJ(a,beBaseInfoRamTimer,r.timer);
        assert(!strcmp(al_text(a,timer->_name),"WAIT"));timer->_endTime=0;
        assert(!dw4_action2_host_tick(&h,0));assert(dw4_action2_host_tick(&h,262144));
        dw4_action2_host_start_program(&h,&c,1,0);work->_waitSt0=0;
        assert(dw4_action2_host_tick(&h,0));
        beModelCtrlNode2 *node=DW4_ARENA_OBJ(a,beModelCtrlNode2,r.node);
        node->_timeScale=.5f;assert(dw4_action2_host_node_time(&h,1048576)==524288);
        dw4_action2_host_motion(&h,262144,1048576,0);
        igAnimationState *motion=DW4_ARENA_OBJ(a,igAnimationState,r.motion);
        igAnimation *animation=DW4_ARENA_OBJ(a,igAnimation,r.animation);
        assert(motion->_timeBias==-262144 && animation->_duration==1048576);
        /* Quantized starts wrap like EE words, including the signed minimum. */
        dw4_action2_host_motion(&h,INT64_MIN,1048576,0);assert(motion->_timeBias==INT64_MIN);
        dw4_action2_host_motion(&h,INT64_MAX,1048576,0);assert(motion->_timeBias==INT64_MIN+262144);
        dw4_action2_component all[DW4_A2_MAX_COMPONENTS+1];
        for(unsigned j=0;j<DW4_A2_MAX_COMPONENTS+1;j++)all[j]=c;
        dw4_action2_host_start_program(&h,all,DW4_A2_MAX_COMPONENTS,0);
        assert(!h.error && al_count(a,data->_comList)==DW4_A2_MAX_COMPONENTS);
        dw4_action2_host_start_program(&h,&c,1,0);
        igObjectList *list=DW4_ARENA_OBJ(a,igObjectList,al_handle(data->_comList));
        int32_t *entries=dw4_arena_at(a,al_handle(list->_data),DW4_A2_MAX_COMPONENTS*4);
        for(unsigned j=1;j<DW4_A2_MAX_COMPONENTS;j++)assert(!entries[j]);
        work->_isFreeze=1;assert(!dw4_action2_host_tick(&h,1000000000));
        work->_isFreeze=0;assert(dw4_action2_host_tick(&h,1000000000));
        dw4_action2_host_start_program(&h,all,DW4_A2_MAX_COMPONENTS+1,0);
        assert(h.error && al_count(a,data->_comList)==1);
        dw4_action2_host_close(&h);assert(dw4_arena_live(a,DW4_REGION_PERSISTENT)==before);
    }
}
static void action2_clock_waits(void)
{
    dw4_title_host h={0};int i;
    dw4_title_host_close(&h);
    dw4_title_host_init(&h,0,1);dw4_title_host_set_clock(&h,0);
    h.api.model_start(&h,0,T_j_startlogo,T_SQ_OPEN,1);
    for(i=0;i<100;++i)h.api.model_tick(&h);
    assert(!h.api.opening_done(&h)); /* Simulation ticks cannot complete a held clock. */
    dw4_title_host_set_clock(&h,1907LL<<18);h.api.model_tick(&h);
    assert(!h.api.opening_done(&h));
    dw4_title_host_set_clock(&h,1908LL<<18);h.api.model_tick(&h);
    assert(h.api.opening_done(&h) && h.logo_action.done);
    h.api.model_close(&h,0,T_j_startlogo,T_SQ_CLOSE,1);
    dw4_title_host_set_clock(&h,3815LL<<18);h.api.model_tick(&h);
    assert(!h.api.closing_done(&h));
    dw4_title_host_set_clock(&h,3816LL<<18);h.api.model_tick(&h);
    assert(h.api.closing_done(&h) && !h.api.model_exists(&h,0,T_j_startlogo));
    /* Large absolute clocks lose precision before subtraction: 1907 raw ticks
     * can complete; no elapsed-tick approximation may replace that arithmetic. */
    dw4_title_host_close(&h);
    dw4_title_host_init(&h,0,1);
    int64_t start=((1LL<<25)+1)<<18;
    dw4_title_host_set_clock(&h,start);h.api.model_tick(&h);
    h.api.model_start(&h,0,T_j_startlogo,T_SQ_OPEN,1);
    dw4_title_host_set_clock(&h,start+(1907LL<<18));h.api.model_tick(&h);
    assert(h.api.opening_done(&h) && !h.error);
    dw4_title_host_close(&h);
}
/* Integration expectations independent of the reference's field layout. */
static void clock_lifecycle(void)
{
    dw4_title_host h={0};int i;
    dw4_title_host_close(&h);
    dw4_title_host_init(&h,0,1);
    dw4_title_host_set_clock(&h,0);
    h.api.model_start(&h,0,T_j_startlogo,T_SQ_OPEN,1);
    dw4_title_host_set_clock(&h,200000000);h.api.model_tick(&h);
    assert(h.clock_ns==200000000 && !h.api.opening_done(&h));
    dw4_clock_host_pause(&h.clock);dw4_clock_host_pause(&h.clock);
    dw4_title_host_set_clock(&h,9200000000LL);
    for(i=0;i<100;i++)h.api.model_tick(&h);
    assert(h.clock_ns==200000000 && !h.api.opening_done(&h));
    dw4_clock_host_resume(&h.clock);dw4_clock_host_resume(&h.clock);
    dw4_clock_host_scale(&h.clock,0x20000);
    dw4_title_host_set_clock(&h,9600000000LL);h.api.model_tick(&h);
    assert(h.clock_ns==400000000 && !h.api.opening_done(&h));
    /* Presentation queries neither sample the source nor advance world time. */
    dw4_title_host_set_clock(&h,9900000000LL);
    for(i=0;i<100;i++) {
        const dw4_title_model *m=dw4_title_host_model(&h,T_j_startlogo);
        (void)dw4_title_model_time(m);(void)dw4_title_model_alpha(m);
        assert(dw4_clock_host_world(&h.clock)==400000000);
    }
    h.api.model_tick(&h);
    assert(h.clock_ns==550000000 && h.api.opening_done(&h) && !h.error);
    dw4_clock_host_scale(&h.clock,0);
    dw4_title_host_set_clock(&h,10000000000LL);h.api.model_tick(&h);
    assert(h.clock_ns==550000000);
    dw4_clock_host_scale(&h.clock,-0x40000);
    dw4_title_host_set_clock(&h,10100000000LL);h.api.model_tick(&h);
    assert(h.clock_ns==450000000);
    dw4_title_host_close(&h);
}
/* Visual playback must keep advancing during MOVE (which only waits),
 * loop while idle, and preserve the US window while fading it out. */
static void option_joints(void)
{
    dw4_title_host h={0};
    dw4_title_host_close(&h);
    dw4_title_host_init(&h, 0, 1);
    h.api.model_start(&h, 0, T_j_optionwin02, T_SQ_BOPEN, 0);
    h.api.model_start(&h, 0, T_j_optioncursor11, T_SQ_OPEN, 0);
    for (int i = 0; i < 15; ++i) h.api.model_tick(&h);
    const dw4_title_model *win = dw4_title_host_model(&h, T_j_optionwin02);
    const dw4_title_model *cur = dw4_title_host_model(&h, T_j_optioncursor11);
    assert(dw4_title_model_alpha(win) == 128 && win->joint_first == 170);
    assert(cur->loop && cur->joint_first == 0);
    for (int i = 0; i < 7; ++i) h.api.model_tick(&h);
    long long before = dw4_title_model_time(cur);
    h.api.model_play(&h, 0, T_j_optioncursor11, T_SQ_MOVE, 0);
    assert(dw4_title_model_time(cur) == before);
    h.api.model_tick(&h);
    assert(dw4_title_model_time(cur) > before);
    h.api.model_play(&h, 0, T_j_optioncursor11, T_SQ_LINESL03, 0);
    assert(cur->joint_first == 270 && cur->joint_last == 329 && cur->loop);
    h.api.model_start(&h, 0, T_j_optioncursor12, T_SQ_LINELF01, 0);
    for (int i = 0; i < 10; ++i) h.api.model_tick(&h);
    const dw4_title_model *arrows = dw4_title_host_model(&h, T_j_optioncursor12);
    assert(arrows->joint_first == 50 && arrows->joint_last == 60 && arrows->loop);
    before = dw4_title_model_time(win);
    h.api.model_close(&h, 0, T_j_optionwin02, T_SQ_CLOSE, 0);
    assert(dw4_title_model_time(win) == before && dw4_title_model_alpha(win) == 128);
    h.api.model_close(&h, 0, T_j_optioncursor11, T_SQ_LINEON03, 0);
    assert(cur->joint_first == 440 && cur->joint_last == 455);
    for (int i = 0; i < 15; ++i) h.api.model_tick(&h);
    assert(!cur->active && !win->active);
    dw4_title_host_close(&h);
}

static const char *last_model, *last_action;
static unsigned sound_events, start_events;
static void capture_sound(void *unused, const char *model, const char *action)
{
    (void)unused;
    last_model = model; last_action = action; sound_events++;
    if (!strcmp(model, "j_startmenu01") && !strcmp(action, "LINEON00")) start_events++;
}
static void selection_sounds(void)
{
    dw4_title_host h={0};
    dw4_title_host_close(&h);
    dw4_title_host_init(&h, 0, 1);
    h.sound_action = capture_sound;
    menu(&h);
    assert(start_events == 1);
    tick(&h, 4, 0);
    assert(!strcmp(last_model, "j_startmenu02") && !strcmp(last_action, "LINEDW01"));
    unsigned before = sound_events;
    tick(&h, 0, 0x4000); /* moving menu ignores confirm */
    assert(sound_events == before);
    wait_ready(&h, 2);
    tick(&h, 0, 0x4000); wait_ready(&h, 4);
    tick(&h, 2, 0);
    assert(!strcmp(last_model, "j_optioncursor12") && !strcmp(last_action, "MOVE"));
    wait_ready(&h, 4);
    tick(&h, 4, 0);
    assert(!strcmp(last_model, "j_optioncursor11") && !strcmp(last_action, "MOVE"));
    dw4_title_host_close(&h);
}

int main(void)
{
    selection_sounds();
    option_joints();
    clock_lifecycle();
    logo_waits();
    action2_arena_records();
    action2_clock_waits();
    dw4_title_host h={0};
    int n, before;
    dw4_title_host_close(&h);
    dw4_title_host_init(&h, 0, 1);
    menu(&h);
    tick(&h, 1, 0); wait_ready(&h, 2); assert(h.ctrl._gameMenuCnt == 0);
    tick(&h, 1 | 4, 0x4000); wait_ready(&h, 2); /* Up precedes Down and confirm. */
    assert(h.ctrl._gameMenuCnt == 0 && h.ctrl._gameMenuNext == 0);
    tick(&h, 4, 0); assert(h.ctrl._gameMenuCnt == 1);
    tick(&h, 0, 0x4000); assert(h.ctrl._gameMenuNext == 0); /* input during movement ignored */
    wait_ready(&h, 2);
    tick(&h, 4, 0); wait_ready(&h, 2); assert(h.ctrl._gameMenuCnt == 1);
    tick(&h, 0, 0x4000); wait_ready(&h, 4);
    assert(h.option._ctrlPos == 0 && h.camera == 0 && h.light == 1);
    tick(&h, 0, 0x4000); assert(h.option._dispComConf == 0); /* Cross does not toggle */
    tick(&h, 2, 0); assert(h.option._dispComConf == 1 && h.camera == 0);
    wait_ready(&h, 4);
    assert(h.text & (1u << 3));
    tick(&h, 4, 0); wait_ready(&h, 4); assert(h.option._ctrlPos == 1);
    tick(&h, 4, 0); wait_ready(&h, 4); assert(h.option._ctrlPos == 3);
    tick(&h, 4, 0); assert(h.option._ctrlPos == 3);
    tick(&h, 0, 0x2000); assert(h.camera == 0); /* Circle commits only after close */
    before = h.frame;
    wait_ready(&h, 2);
    assert(h.frame - before >= 30 && h.camera == 1 && h.light == 1);
    assert(h.ctrl._gameMenuCnt == 0 && h.text == 0);
    /* Cancel menu, re-enter, and revisit settings with committed values. */
    tick(&h, 0, 0x2000); wait_ready(&h, 1); menu(&h);
    tick(&h, 4, 0); wait_ready(&h, 2); tick(&h, 0, 0x4000); wait_ready(&h, 4);
    assert(h.option._dispComConf == 1 && h.option._ctrlPos == 0);
    tick(&h, 4, 0); wait_ready(&h, 4); tick(&h, 4, 0); wait_ready(&h, 4);
    tick(&h, 0, 0x4000); wait_ready(&h, 2);
    tick(&h, 0, 0x4000);
    for (n = 0; n < 200 && !h.handoff; ++n) tick(&h, 0, 0);
    assert(h.handoff && h.nargs == 2 && h.args[0] == 1 && h.args[1] == 1);
    /* Queue independence, no immediate completion, and close removes a model. */
    dw4_title_host_close(&h);
    dw4_title_host_init(&h, 0, 1);
    h.api.model_start(&h, 0, T_j_startlogo, T_SQ_OPEN, 1);
    h.api.model_close(&h, 0, T_j_optionwin02, T_SQ_CLOSE, 1);
    assert(!h.api.opening_done(&h) && !h.api.closing_done(&h));
    for (n = 0; n < 15; ++n) h.api.model_tick(&h);
    assert(!h.api.opening_done(&h) && h.api.closing_done(&h));
    assert(!h.api.model_exists(&h, 0, T_j_optionwin02));
    for (n = 0; n < 15; ++n) h.api.model_tick(&h);
    assert(!h.api.opening_done(&h)); /* phase-zero provisional clock: frame 30 is too early */
    h.api.model_tick(&h);assert(h.api.opening_done(&h));
    h.api.model_play(&h, 0, T_j_startmenu02, T_SQ_LINEON00, 1);
    h.api.model_close(&h, 0, T_j_startmenu01, T_SQ_LINEON00, 1);
    for (n = 0; n < 15; ++n) h.api.model_tick(&h);
    assert(h.api.opening_done(&h) && !h.api.closing_done(&h));
    h.api.model_tick(&h); assert(h.api.closing_done(&h));
    /* A replacement does not erase its predecessor's queued request. The
     * newest pending entry blocks an older completed one until the next poll. */
    dw4_title_host_close(&h);
    dw4_title_host_init(&h, 0, 1);
    h.api.model_play(&h, 0, T_j_startmenu02, T_SQ_OPEN, 1);
    h.api.model_play(&h, 0, T_j_startmenu02, T_SQ_LINEDW01, 1);
    for (n = 0; n < 19; ++n) h.api.model_tick(&h);
    assert(!h.api.opening_done(&h));
    assert(h.common_model.api.peek(&h.common_model,DW4_CM_BASE+0x108,4)==2);
    h.api.model_tick(&h); assert(h.api.opening_done(&h));
    /* Wait is exactly low-byte 1. Re-entry reuses released records. */
    for(n=0;n<300;++n) {
        h.api.model_play(&h,0,T_j_startmenu02,T_SQ_OPEN,2);
        assert(h.api.opening_done(&h));
        h.api.model_play(&h,0,T_j_startmenu02,T_SQ_OPEN,257);
        assert(!h.api.opening_done(&h));
        h.model[2].query_sequence=0;
        h.api.model_tick(&h); assert(h.api.opening_done(&h));
    }
    /* Capacity failure must stop the screen, not overwrite either queue. */
    dw4_title_host_close(&h);
    dw4_title_host_init(&h,0,1);
    for(n=0;n<DW4_CM_CAPACITY;++n) h.api.model_play(&h,0,T_j_startlogo,T_SQ_OPEN,1);
    assert(!h.common_model.error);
    h.api.model_play(&h,0,T_j_startlogo,T_SQ_OPEN,1);
    assert(h.common_model.error && !h.api.opening_done(&h) && !h.api.closing_done(&h));
    /* Attract sequence expires from model state, not a controller timeout. */
    dw4_title_host_close(&h);
    dw4_title_host_init(&h, 0, 1); wait_ready(&h, 1);
    for (n = 0; n < 1900 && !h.next_stage; ++n) tick(&h, 0, 0);
    assert(h.next_stage == T_stagIS09 && !h.handoff);
    dw4_title_host_close(&h);
    dw4_title_host_init(&h, 0, 1);
    h.api.model_start(&h, 0, T_j_startlogo, 0x123456, 1);
    assert(h.error && !h.api.opening_done(&h) && !h.api.closing_done(&h));
    puts("title controller: waits, priority, clamp, confirm/cancel, re-entry, settings commit, handoff and attract pass");
    dw4_title_host_close(&h);
    return 0;
}
