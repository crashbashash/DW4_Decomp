/* PS2 save-file codec: item ids, verification, record round trips and retail saves. Headless.
 * Retail samples (private, outside Git) are loaded into player records and stored again: the result must equal the
 * retail file byte for byte. Samples live under $DW4_SAVE_SAMPLES (default ../../local). */
#include "hubtest.h"
#include "dw4/saveimage.h"
#include "dw4/memcard.h"
#include "dw4/savectrl.h"
#include <unistd.h>
#include <sys/stat.h>

static void items_roundtrip(void)
{
    uint32_t id;dw4_item_record back;
    /* The five classes' vfunc_23/24 pairs, all fields at their limits. */
    static const dw4_item_record ok[]={
        {0,0x3FF,1,0x7FF,0xF},{0,0,0,0,0},{1,0x155,0,0x2AA,5},{2,0x10D,1,0x7FF,0},{3,0x2AA,1,0,0},{4,11,0,9,0},{4,0,1,0xF,0}};
    for(size_t i=0;i<sizeof ok/sizeof *ok;i++){
        assert(!dw4_saveimage_item_encode(ok+i,&id) && !dw4_saveimage_item_decode(id,&back));
        assert(!memcmp(&back,ok+i,sizeof back));
    }
    /* Bit placement: record 0..9, equipped bit 10, kind 12..15, pocket 16..19, revision 20..30 (disk revision 16..19). */
    assert(!dw4_saveimage_item_encode(&(dw4_item_record){0,0x10D,1,3,2},&id) && id==(0x10Du|0x400u|0u<<12|2u<<16|3u<<20));
    assert(!dw4_saveimage_item_encode(&(dw4_item_record){3,0x2D,1,0,0},&id) && id==0x342Du); /* equipped chip, #95's 0x34 */
    assert(!dw4_saveimage_item_encode(&(dw4_item_record){4,7,0,9,0},&id) && id==(7u|4u<<12|9u<<16));
    assert(!dw4_saveimage_item_encode(&(dw4_item_record){.kind=-1},&id) && id==0xFFFFFFFFu);
    assert(!dw4_saveimage_item_decode(0xFFFFFFFFu,&back) && back.kind==-1);
    assert(!dw4_saveimage_item_decode(0x5000u,&back) && back.kind==-1); /* kind nibble 5: retail stores NULL */
    /* Unrepresentable fields are refused instead of truncated. */
    assert(dw4_saveimage_item_encode(&(dw4_item_record){5,0,0,0,0},&id)==-1);
    assert(dw4_saveimage_item_encode(&(dw4_item_record){0,0x400,0,0,0},&id)==-1);
    assert(dw4_saveimage_item_encode(&(dw4_item_record){0,0,0,0x800,0},&id)==-1);
    assert(dw4_saveimage_item_encode(&(dw4_item_record){0,0,0,0,0x10},&id)==-1);
    assert(dw4_saveimage_item_encode(&(dw4_item_record){3,0,0,1,0},&id)==-1);
    assert(dw4_saveimage_item_encode(&(dw4_item_record){4,0,0,0x10,0},&id)==-1);
    assert(dw4_saveimage_item_encode(&(dw4_item_record){2,0,0,0,1},&id)==-1);
}
static void expect_same(dw4_property_folder *a,dw4_property_folder *b)
{
    static const char *const numbers[]={"ISUSE","UNIQUE","LEVEL","HP","MHP","MP","MMP","XDATA","BIT","BANKBIT"};
    for(unsigned i=0;i<sizeof numbers/sizeof *numbers;i++){
        int32_t x,y;assert(!dw4_property_number(a,numbers[i],&x) && !dw4_property_number(b,numbers[i],&y) && x==y);
    }
    assert(!strcmp(dw4_property_string(a,"DIGIMONNAME"),dw4_property_string(b,"DIGIMONNAME")));
    dw4_unicode_object u,v;
    assert(!dw4_property_unicode_object(a,"PLAYERNAME",0,&u) && !dw4_property_unicode_object(b,"PLAYERNAME",0,&v));
    if(u.count!=v.count || memcmp(u.codes,v.codes,u.count*2)){fprintf(stderr,"name: %zu codes [%x %x %x] vs %zu codes [%x %x %x]\n",u.count,u.codes[0],u.codes[1],u.codes[2],v.count,v.codes[0],v.codes[1],v.codes[2]);assert(0);}
    static const char *const lists[]={"DEVICEFOLDER","DISKFOLDER","BANKDEVICE","POWERSOCKET","POWERPOCKET","MAINSLOT","MAINPOCKET","SUBSLOT"};
    for(unsigned i=0;i<sizeof lists/sizeof *lists;i++){
        size_t n,m;const dw4_item_record *x=dw4_property_items(a,lists[i],&n),*y=dw4_property_items(b,lists[i],&m);
        assert(n==m && (!n || !memcmp(x,y,n*sizeof *x)));
    }
    static const char *const arrays[]={"POWERSOCKETREF","POWERPOCKETREF","MAINSLOTREF","MAINPOCKETREF","SUBSLOTREF","BASE_COUNTER","BASE_ISUSE","BASE_LEVEL","BASE_EXP","BASE_SKILL","BASE_UPCNT"};
    for(unsigned i=0;i<sizeof arrays/sizeof *arrays;i++){
        size_t n,m;const int32_t *x=dw4_property_array(a,arrays[i],&n),*y=dw4_property_array(b,arrays[i],&m);
        assert(x && y && n==m && !memcmp(x,y,n*sizeof *x));
    }
    static const char *const bytes[]={"BASE_FLAG","BASE_FLAGFOLDER","CARDLIST"};
    for(unsigned i=0;i<3;i++){
        size_t n,m;const uint8_t *x=dw4_property_bytes(a,bytes[i],&n),*y=dw4_property_bytes(b,bytes[i],&m);
        assert(x && y && n==m && !memcmp(x,y,n));
    }
}
static void first_difference(const uint8_t *a,const uint8_t *b,const char *label)
{
    for(size_t i=0;i<DW4_SAVE_IMAGE_SIZE;i++)if(a[i]!=b[i]){fprintf(stderr,"%s: first byte difference at 0x%zx (struct +0x%zx): %02x vs %02x\n",label,i,i%DW4_SAVE_BLOCK_SIZE-8,a[i],b[i]);return;}
}
static void verification(const uint8_t *good)
{
    const char *why=NULL;uint8_t bad[DW4_SAVE_IMAGE_SIZE];
    assert(!dw4_saveimage_verify(good,DW4_SAVE_IMAGE_SIZE,&why));
    assert(dw4_saveimage_verify(good,DW4_SAVE_IMAGE_SIZE-1,&why)==-1 && why);
    assert(dw4_saveimage_verify(NULL,DW4_SAVE_IMAGE_SIZE,&why)==-1);
    memcpy(bad,good,sizeof bad);bad[0x100]^=1;
    assert(dw4_saveimage_verify(bad,sizeof bad,&why)==-1 && strstr(why,"checksum"));
    memcpy(bad,good,sizeof bad);bad[DW4_SAVE_BLOCK_SIZE+0x100]^=1;
    assert(dw4_saveimage_verify(bad,sizeof bad,&why)==-1);
    memcpy(bad,good,sizeof bad);bad[4]=5;
    assert(dw4_saveimage_verify(bad,sizeof bad,&why)==-1 && strstr(why,"version"));
    /* A block that is internally consistent but differs from its mirror is refused. */
    memcpy(bad,good,sizeof bad);bad[0x100]^=1;
    uint32_t sum=0;for(unsigned o=4;o<DW4_SAVE_BLOCK_SIZE;o+=4){uint32_t w;memcpy(&w,bad+o,4);sum+=w;}
    memcpy(bad,&sum,4);
    assert(dw4_saveimage_verify(bad,sizeof bad,&why)==-1 && strstr(why,"mirror"));
}
static void synthesized(dw4_playerrecords *players,dw4_databases *db)
{
    char error[256];
    assert(!dw4_playerrecords_create(players,db,0,"p_dorumon","Codec",error,sizeof error));
    dw4_property_folder *f=dw4_playerrecords_get(players,"GETPLAYER",0);
    /* Give every saved region a distinctive value. */
    int result;
    assert(!dw4_property_set_number(f,"XDATA",1234) && !dw4_property_set_number(f,"BIT",7654321) && !dw4_property_set_number(f,"BANKBIT",42));
    assert(!dw4_playertransactions_device(players,0,DW4_DEVICE_SET,3,0x2D,0,0,&result) && result);
    assert(!dw4_playertransactions_device(players,0,DW4_DEVICE_SET,1,12,5,3,&result) && result);
    assert(!dw4_playertransactions_device(players,0,DW4_DEVICE_SET,2,7,9,0,&result) && result);
    size_t n;assert(!dw4_property_item_count(f,"DEVICEFOLDER",&n) && n==6);
    uint8_t first[DW4_SAVE_IMAGE_SIZE],second[DW4_SAVE_IMAGE_SIZE];
    dw4_saveimage_init(first);
    assert(!dw4_saveimage_store(players,0,0,first) && !dw4_saveimage_verify(first,sizeof first,NULL) && dw4_saveimage_slot_used(first,0) && !dw4_saveimage_slot_used(first,1));
    /* Load into another character; the stored keys must be identical and storing again byte-identical. */
    dw4_playerrecords *other=dw4_playerrecords_open();assert(other);
    assert(!dw4_playerrecords_create(other,db,0,"p_agumon","Other",error,sizeof error));
    assert(!dw4_saveimage_load(other,0,0,first,sizeof first));
    expect_same(f,dw4_playerrecords_get(other,"GETPLAYER",0));
    dw4_saveimage_init(second);
    assert(!dw4_saveimage_store(other,0,0,second) && !memcmp(first,second,sizeof first));
    /* A corrupt image changes nothing. */
    uint8_t bad[DW4_SAVE_IMAGE_SIZE];memcpy(bad,first,sizeof bad);bad[0x200]^=1;
    int32_t before;assert(!dw4_property_number(dw4_playerrecords_get(other,"GETPLAYER",0),"XDATA",&before));
    assert(dw4_saveimage_load(other,0,0,bad,sizeof bad)==-1 && dw4_saveimage_load(other,0,4,first,sizeof first)==-1);
    int32_t after;assert(!dw4_property_number(dw4_playerrecords_get(other,"GETPLAYER",0),"XDATA",&after) && after==before);
    /* Files: atomic write, verified read, a failed write keeps the previous file. */
    char dir[]="/tmp/dw4-saveimage-XXXXXX";assert(mkdtemp(dir));
    char path[300];snprintf(path,sizeof path,"%s/BASLUS-20836savedata",dir);
    uint8_t read[DW4_SAVE_IMAGE_SIZE];
    assert(!dw4_savefile_write(path,first) && !dw4_savefile_read(path,read) && !memcmp(read,first,sizeof read));
    assert(dw4_savefile_write(path,bad)==-1 && !dw4_savefile_read(path,read) && !memcmp(read,first,sizeof read));
    char nodir[320];snprintf(nodir,sizeof nodir,"%s/missing/save",dir);
    assert(dw4_savefile_write(nodir,first)==-1 && dw4_savefile_read(nodir,read)==-1);
    char tmp[320];snprintf(tmp,sizeof tmp,"%s.tmp",path);assert(access(tmp,F_OK)!=0);
    assert(!remove(path));assert(!rmdir(dir));
    /* Unrepresentable data is refused and nothing is written. */
    dw4_item_record big[37];for(unsigned i=0;i<37;i++)big[i]=(dw4_item_record){3,i,0,0,0};
    dw4_playerrecords *c=dw4_playerrecords_snapshot(players);assert(c);
    assert(!dw4_property_set_items(dw4_playerrecords_get(c,"GETPLAYER",0),"DEVICEFOLDER",big,37));
    uint8_t untouched[DW4_SAVE_IMAGE_SIZE];memset(untouched,0xA5,sizeof untouched);
    assert(dw4_saveimage_store(c,0,0,first)==-1 && !memcmp(first,second,sizeof first)); /* the image stays as it was */
    assert(dw4_saveimage_store(players,0,4,second)==-1 && dw4_saveimage_store(players,0,-1,second)==-1);
    (void)untouched;
    dw4_playerrecords_close(c);dw4_playerrecords_close(other);
    verification(first);
    printf("save image: synthesized character round trips byte-for-byte, corruption and failed writes change nothing\n");
}
/* The host memory card: scan, save of several characters, reload, and a damaged file that is never overwritten. */
static void card_session(dw4_playerrecords *players,dw4_databases *db)
{
    char error[256],dir[]="/tmp/dw4-memcard-XXXXXX";assert(mkdtemp(dir));
    dw4_memcard *card=dw4_memcard_open(dir);assert(card && dw4_memcard_ready(card));
    int present[DW4_SAVE_SLOTS]={9,9,9,9},used=-1;
    /* An empty card scans as empty and needs a whole image; a missing directory is not ready. */
    assert(!dw4_memcard_scan(card,present,&used,error,sizeof error) && used==0 && !present[0] && !present[3]);
    assert(dw4_memcard_needed(card)==DW4_SAVE_IMAGE_SIZE);
    char gone[300];snprintf(gone,sizeof gone,"%s/missing",dir);
    dw4_memcard *none=dw4_memcard_open(gone);assert(none && !dw4_memcard_ready(none));
    assert(dw4_memcard_scan(none,present,&used,error,sizeof error)==-1 && present[0]==0);
    dw4_memcard_close(none);
    /* Save player 0 into slot 0 and a second character into slot 2 of the same file. */
    dw4_playerrecords *second=dw4_playerrecords_open();assert(second);
    assert(!dw4_playerrecords_create(second,db,2,"p_agumon","Second",error,sizeof error));
    int32_t nobody[DW4_SAVE_SLOTS]={-1,-1,-1,-1},slot0[DW4_SAVE_SLOTS]={0,-1,-1,-1},slot2[DW4_SAVE_SLOTS]={-1,-1,2,-1};
    assert(dw4_memcard_save(card,players,nobody,error,sizeof error)==-1); /* nothing selected, nothing written */
    assert(dw4_memcard_needed(card)==DW4_SAVE_IMAGE_SIZE);
    assert(!dw4_memcard_save(card,players,slot0,error,sizeof error) && dw4_memcard_needed(card)==0);
    {   /* The previous file survives every later write as <file>.bak (the save-library decision). */
        char cur[320],bak[330];snprintf(cur,sizeof cur,"%s/%s",dir,DW4_MEMCARD_FILE);snprintf(bak,sizeof bak,"%s.bak",cur);
        uint8_t prev[DW4_SAVE_IMAGE_SIZE],kept[DW4_SAVE_IMAGE_SIZE];
        assert(!dw4_savefile_read(cur,prev) && access(bak,F_OK)!=0);   /* the first write had nothing to keep */
        assert(!dw4_memcard_save(card,second,slot2,error,sizeof error));
        assert(!dw4_savefile_read(bak,kept) && !memcmp(prev,kept,sizeof prev));
        uint8_t now[DW4_SAVE_IMAGE_SIZE];assert(!dw4_savefile_read(cur,now) && memcmp(now,prev,sizeof now));
    }
    assert(!dw4_memcard_scan(card,present,&used,error,sizeof error) && used==2 && present[0]==1 && !present[1] && present[2]==1 && !present[3]);
    /* Reload both slots into fresh characters: the stored keys come back identical. */
    dw4_playerrecords *back=dw4_playerrecords_open();assert(back);
    assert(!dw4_playerrecords_create(back,db,0,"p_dorumon","Back",error,sizeof error));
    assert(!dw4_memcard_load(card,back,0,0,error,sizeof error));
    expect_same(dw4_playerrecords_get(players,"GETPLAYER",0),dw4_playerrecords_get(back,"GETPLAYER",0));
    assert(dw4_memcard_load(card,back,0,1,error,sizeof error)==-1 && dw4_memcard_load(card,back,0,4,error,sizeof error)==-1);
    /* "Call Digimon": restore builds a live character of the saved species from a slot, ready to play. */
    dw4_playerrecords *called=dw4_playerrecords_open();assert(called);
    assert(!dw4_memcard_restore(card,called,db,2,2,error,sizeof error));
    expect_same(dw4_playerrecords_get(second,"GETPLAYER",2),dw4_playerrecords_get(called,"GETPLAYER",2));
    int32_t isuse=0;assert(!dw4_property_number(dw4_playerrecords_get(called,"GETPLAYER",2),"ISUSE",&isuse) && isuse==1);
    assert(dw4_memcard_restore(card,called,db,2,1,error,sizeof error)==-1 && strstr(error,"no character"));
    expect_same(dw4_playerrecords_get(second,"GETPLAYER",2),dw4_playerrecords_get(called,"GETPLAYER",2));
    dw4_playerrecords_close(called);
    {   /* A grown character: the saved species' level and EXP come back as current values (BASE2CURRENT after the card load). */
        dw4_playerrecords *grown=dw4_playerrecords_open();assert(grown);
        assert(!dw4_playerrecords_create(grown,db,3,"p_agumon","Grown",error,sizeof error));
        dw4_property_folder *g=dw4_playerrecords_get(grown,"GETPLAYER",3);
        assert(!dw4_property_set_number(g,"LEVEL",17) && !dw4_property_set_number(g,"EXP",1234));
        assert(!dw4_playertransactions_current_to_base(grown,3));
        int32_t slot3[DW4_SAVE_SLOTS]={-1,-1,-1,3};
        assert(!dw4_memcard_save(card,grown,slot3,error,sizeof error));
        dw4_playerrecords *again=dw4_playerrecords_open();assert(again);
        assert(!dw4_memcard_restore(card,again,db,3,3,error,sizeof error));
        int32_t lv=0,xp=0,no=-1;dw4_property_folder *r=dw4_playerrecords_get(again,"GETPLAYER",3);
        assert(!dw4_property_number(r,"LEVEL",&lv) && !dw4_property_number(r,"EXP",&xp) && !dw4_property_number(r,"DIGIMONNO",&no));
        int32_t made=-1;assert(!dw4_property_number(dw4_playerrecords_get(grown,"GETPLAYER",3),"DIGIMONNO",&made));
        assert(lv==17 && xp==1234 && no==made);   /* the species row is rebuilt from the saved model name */
        dw4_playerrecords_close(again);dw4_playerrecords_close(grown);
    }
    /* A damaged file is refused by scan, load and save, and the bytes on disk stay exactly as they were. */
    char file[320];snprintf(file,sizeof file,"%s/%s",dir,DW4_MEMCARD_FILE);
    uint8_t image[DW4_SAVE_IMAGE_SIZE],after[DW4_SAVE_IMAGE_SIZE];assert(!dw4_savefile_read(file,image));
    FILE *f=fopen(file,"r+b");assert(f);fseek(f,0x300,SEEK_SET);fputc(image[0x300]^0x55,f);fclose(f);
    uint8_t damaged[DW4_SAVE_IMAGE_SIZE];f=fopen(file,"rb");assert(f && fread(damaged,1,sizeof damaged,f)==sizeof damaged);fclose(f);
    assert(dw4_memcard_scan(card,present,&used,error,sizeof error)==-1 && strstr(error,"damaged"));
    assert(dw4_memcard_load(card,back,0,0,error,sizeof error)==-1);
    assert(dw4_memcard_save(card,players,slot0,error,sizeof error)==-1);
    f=fopen(file,"rb");assert(f && fread(after,1,sizeof after,f)==sizeof after);fclose(f);
    assert(!memcmp(after,damaged,sizeof after));
    /* SaveCtrl's exit rule. */
    int pos=0;assert(!strcmp(dw4_savectrl_exit_stage(0,&pos),"stagis10") && pos==-1);
    assert(!strcmp(dw4_savectrl_exit_stage(3,&pos),"stagML12") && pos==2);
    char tmp[340];snprintf(tmp,sizeof tmp,"%s.tmp",file);assert(access(tmp,F_OK)!=0);
    {char bakfile[340];snprintf(bakfile,sizeof bakfile,"%s.bak",file);remove(bakfile);}
    assert(!remove(file) && !rmdir(dir));
    dw4_memcard_close(card);dw4_playerrecords_close(second);dw4_playerrecords_close(back);
    /* The native save library directory: $XDG_DATA_HOME/dw4/saves, else ~/.local/share/dw4/saves. */
    {
        char base[]="/tmp/dw4-xdg-XXXXXX",lib[400],want[420];
        assert(mkdtemp(base));assert(!setenv("XDG_DATA_HOME",base,1));
        snprintf(want,sizeof want,"%s/dw4/saves",base);
        assert(!dw4_memcard_default_directory(lib,sizeof lib,0) && !strcmp(lib,want) && access(lib,F_OK)!=0);
        assert(!dw4_memcard_default_directory(lib,sizeof lib,1) && !strcmp(lib,want) && !access(lib,W_OK));
        assert(!dw4_memcard_default_directory(lib,sizeof lib,1));      /* creating it again is fine */
        dw4_memcard *lcard=dw4_memcard_open(lib);assert(lcard && dw4_memcard_ready(lcard));
        assert(!dw4_memcard_save(lcard,players,slot0,error,sizeof error));
        char lfile[500];snprintf(lfile,sizeof lfile,"%s/%s",lib,DW4_MEMCARD_FILE);assert(!access(lfile,R_OK));
        dw4_memcard_close(lcard);remove(lfile);
        char up[420];snprintf(up,sizeof up,"%s/dw4/saves",base);rmdir(up);snprintf(up,sizeof up,"%s/dw4",base);rmdir(up);rmdir(base);
        assert(!unsetenv("XDG_DATA_HOME"));assert(!setenv("HOME","/home/example",1));
        assert(!dw4_memcard_default_directory(lib,sizeof lib,0) && !strcmp(lib,"/home/example/.local/share/dw4/saves"));
        char tiny[8];assert(dw4_memcard_default_directory(tiny,sizeof tiny,0)==-1);   /* too small: refused, not truncated */
    }
    printf("memory card: scan, two-character save, reload, .bak backup, XDG library directory, damaged-file refusal and the SaveCtrl exit rule pass\n");
}
/* Every used slot of a retail-written file loads into its player and stores back; the unused slots are zero. */
static int retail_sample(dw4_databases *db,const char *path,const char *label)
{
    uint8_t original[DW4_SAVE_IMAGE_SIZE],again[DW4_SAVE_IMAGE_SIZE];
    FILE *probe=fopen(path,"rb");if(!probe)return 0; /* sample absent: skipped explicitly by the caller */
    fclose(probe);
    if(dw4_savefile_read(path,original)){fprintf(stderr,"%s: retail file does not verify\n",label);assert(0);}
    static const char *const starters[]={"p_dorumon","p_agumon","p_vmon","p_girumon"};
    dw4_playerrecords *players=dw4_playerrecords_open();assert(players);
    dw4_saveimage_init(again);char error[256],desc[160]="";unsigned used=0;
    for(int slot=0;slot<DW4_SAVE_SLOTS;slot++){
        if(!dw4_saveimage_slot_used(original,slot))continue;
        assert(!dw4_playerrecords_create(players,db,slot,starters[slot],"Retail",error,sizeof error));
        assert(!dw4_saveimage_load(players,slot,slot,original,sizeof original));
        dw4_property_folder *f=dw4_playerrecords_get(players,"GETPLAYER",slot);int32_t level;
        assert(!dw4_property_number(f,"LEVEL",&level));
        size_t n=0;dw4_property_item_count(f,"DEVICEFOLDER",&n);
        char one[48];snprintf(one,sizeof one,"%s%s L%d %zu items",used?", ":"",dw4_property_string(f,"DIGIMONNAME"),level,n);
        strncat(desc,one,sizeof desc-strlen(desc)-1);
        assert(!dw4_saveimage_store(players,slot,slot,again));used++;
    }
    if(memcmp(original,again,sizeof original)){first_difference(original,again,label);assert(0);}
    {   /* Call Digimon on the retail file: every used slot restores (evolved species included) with its saved level. */
        char dir[]="/tmp/dw4-retailcall-XXXXXX";assert(mkdtemp(dir));
        char file[320];snprintf(file,sizeof file,"%s/%s",dir,DW4_MEMCARD_FILE);assert(!dw4_savefile_write(file,original));
        dw4_memcard *card=dw4_memcard_open(dir);assert(card);
        for(int slot=0;slot<DW4_SAVE_SLOTS;slot++){
            if(!dw4_saveimage_slot_used(original,slot))continue;
            dw4_playerrecords *r=dw4_playerrecords_open();assert(r);
            if(dw4_memcard_restore(card,r,db,0,slot,error,sizeof error)){fprintf(stderr,"%s slot %d restore: %s\n",label,slot,error);assert(0);}
            dw4_property_folder *g=dw4_playerrecords_get(r,"GETPLAYER",0),*o=dw4_playerrecords_get(players,"GETPLAYER",slot);int32_t a=0,b=0;
            assert(!dw4_property_number(g,"LEVEL",&a) && !dw4_property_number(o,"LEVEL",&b) && a==b);
            assert(!strcmp(dw4_property_string(g,"DIGIMONNAME"),dw4_property_string(o,"DIGIMONNAME")));
            dw4_playerrecords_close(r);
        }
        dw4_memcard_close(card);unlink(file);rmdir(dir);
    }
    printf("save image: retail %s (%u character%s: %s) loads and stores back byte-identical\n",label,used,used==1?"":"s",desc);
    dw4_playerrecords_close(players);return 1;
}
int main(int argc,char **argv)
{
    items_roundtrip();
    dw4_mount mount;assert(!dw4_mount_open(&mount,argc>1?argv[1]:"../local/extracted"));
    dw4_playerrecords *players=dw4_playerrecords_open();dw4_be_state state;dw4_be_init(&state);
    struct boot host={players,dw4_scriptservices_open()};assert(players && host.sd);
    assert(dw4_scriptservices_register(host.sd,0,"GAMERAM",NULL,-1,1,dw4_playerrecords_service,players));
    dw4_scriptengine *e=dw4_scriptengine_open(&state,binding,&host);dw4_filelist *fl=dw4_filelist_open(&mount);assert(e && fl);
    dw4_scriptengine_filelist(e,fl);
    assert(!dw4_filelist_begin(fl,e,"stagIS10",1));assert(!dw4_filelist_shared(fl));
    dw4_stageobjects *objects=dw4_stageobjects_open();assert(objects);
    assert(!dw4_filelist_route_assets(fl,dw4_stageobjects_route,objects));
    assert(!dw4_filelist_bind_layers(fl,dw4_stageobjects_bind_layers,objects));
    char error[512];dw4_databases *db=dw4_databases_open(objects,error,sizeof error);assert(db);
    synthesized(players,db);
    card_session(players,db);
    const char *dir=getenv("DW4_SAVE_SAMPLES");if(!dir)dir="../../local";
    /* Files the retail game wrote itself (a fresh save, two level-up saves, resaves of multi-character images). */
    static const char *const samples[][2]={
        {"first","testing/save-dumps/first/BASLUS-20836savedata/BASLUS-20836savedata"},
        {"second","testing/save-dumps/second/BASLUS-20836savedata/BASLUS-20836savedata"},
        {"fresh","testing/save-experiments/fresh.raw"},
        {"world1-gate","testing/veryhard-v0.7.0-20261015/world1-gate.savedata"},
        {"resaved-two","ps2-box-research/retail-resaved-box2.bin"},
        {"resaved-three","ps2-box-creation/retail-resaved3.bin"}};
    unsigned found=0;
    for(unsigned i=0;i<sizeof samples/sizeof *samples;i++){
        char path[512];snprintf(path,sizeof path,"%s/%s",dir,samples[i][1]);
        found+=retail_sample(db,path,samples[i][0]);
    }
    if(!found)printf("save image: retail samples unavailable, skipped\n");
    dw4_databases_close(db);dw4_stageobjects_close(objects);dw4_scriptengine_close(e);dw4_filelist_close(fl);
    dw4_scriptservices_close(host.sd);dw4_playerrecords_close(players);dw4_mount_close(&mount);
    return 0;
}
