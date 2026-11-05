#!/usr/bin/env python3
"""Original Digi-Elf sequence traces against retail instruction execution.

Runs 395250 dispatch, 393260 MOVE/MOVEEX, 391a10 CTRL, 395070 MUTEKI,
3943c0/393c80 label registration, 3960f0 label selection and 392d20/90/e10
channels. Action playback/completion and sequence-message reentry are controlled
leaves; frame durations use retail float conversion. No private bytes embedded.
"""
import argparse
from pathlib import Path
import struct
import subprocess
import sys
from verify_scriptservices_retail import World, ROOT, BASE
from verify_modelai_retail import AI
sys.path.insert(0,str(ROOT.parent/'scripts'))
import modelctrl_dump as dump
from ee_core import MASK
OWNER, INFO, NODE, WORK = [BASE+0xb0000+i*0x100 for i in range(4)]
CHANNELS=BASE+0xc0000
MOVES=BASE+0xc1000
LABELS=[BASE+0xd0000+i*0x1000 for i in range(3)]
META=BASE+0xe0000
HANDLES={'beModelCtrlCTRL':0x588df8,'beModelCtrlACTION':0x588e08,
         'beModelCtrlMOVE':0x588dd8,'beModelCtrlMOVEEX':0x588da0,
         'beModelCtrlWCHECK':0x588d68,'beModelCtrlMUTEKI':0x588d50,
         'beModelCtrlLABELCTRL':0x588e10,'beModelCtrlLABEL':0x588e20,
         'beModelCtrlJUMP':0x588e00}
def bits(f):return struct.unpack('<I',struct.pack('<f',f))[0]
def f32(f):return struct.unpack('<f',struct.pack('<f',f))[0]
class Actor(World):
    def __init__(self,image,pack,name):
        super().__init__(image)
        self.pack=pack;self.name=name;self.now=0;self.events=[];self.wait=False
        self.playing=None;self.deadline=0;self.pending=None;self.query_name=None;self.query_result=None
        self.descend={0x395250,0x393260,0x392d20,0x392d90,0x392e10,
                      0x391a10,0x395070,0x3943c0,0x393c80,0x3960f0}
        self.rows={};self.seq={};self.commands={};self.action={}
        info=next(i for i in range(pack.cnt) if pack.cls(i)=='beModelCtrlInfo' and pack.rname(i)==name)
        bank=next(i for i in range(pack.cnt) if pack.cls(i)=='beAction2Info' and pack.rname(i)==name)
        for i in pack.list_ids(pack.fields(bank)['_dataList']):
            waits=[pack.fields(c)['_waitTime'] for c in pack.list_ids(pack.fields(i)['_comList']) if pack.cls(c)=='beAction2WAITCHECK']
            self.action[pack.rname(i)]=waits[0] if waits else None
        seqinfo=next(i for i in pack.list_ids(pack.fields(info)['slot5']) if pack.cls(i)=='beModelCtrlInfoDataSeq')
        for j,i in enumerate(pack.list_ids(pack.fields(seqinfo)['_dataList'])):
            seqname=pack.rname(i);sp=BASE+0xf0000+j*0x1000
            self.seq[seqname]=sp;self.rows[seqname]=pack.list_ids(pack.fields(i)['_comList'])
            ptrs=[]
            for c in self.rows[seqname]:
                cp=BASE+0x120000+c*64
                self.commands[cp]=c;ptrs.append(cp)
                self.w(cp,4,META);self.w(cp+8,4,self.token(pack.rname(c)))
                for off,key in ((12,'_value'),(16,'_frame'),(20,'_playTime'),(24,'_isSeqStop'),(28,'_stopValue'),(32,'_stopFrame')):
                    val=pack.fields(c).get(key,0);self.w(cp+off,4,bits(val) if isinstance(val,float) else val)
                if pack.cls(c)=='beModelCtrlLABELCTRL':self.w(cp+12,4,self.token(pack.fields(c)['_seqName']))
                if pack.cls(c)=='beModelCtrlMUTEKI':self.w(cp+12,4,bits(pack.fields(c)['_frame']))
            self.w(sp+12,4,sp+0x100);self.list(sp+0x100,ptrs)
        self.w(META+0x58,4,META+0x100)
        for h in HANDLES.values():self.w(h,4,h)
        self.list(MOVES,[CHANNELS+i*44 for i in range(4)]);self.w(WORK+200,4,MOVES)
        for i,p in enumerate(LABELS):self.list(p,[]);self.w(WORK+36+i*4,4,p)
        self.convert=AI(image);self.convert.descend.update(range(0x22e000,0x231100,4))
    def string(self,p):
        if 0x100000<=p<0x554b00:
            chars=[]
            while self.read(p,1):chars.append(self.read(p,1));p+=1
            return bytes(chars).decode('ascii')
        return super().string(p)
    def step(self,pc,delay=False):
        if pc==0x3952d4:
            c=self.commands[self.r[16]&0xffffffff];kind=self.pack.cls(c)
            if kind!='beModelCtrlLABEL' or not self.read(WORK+32,4):
                self.events.append(f'TRACE {self.name} {self.now} {self.current} {kind} {self.pack.rname(c)}')
        return super().step(pc,delay)
    def call(self,e,a):
        a=[x&0xffffffff for x in a]
        if e==0x38f8f0:return self.token(self.query_name)
        if e==0x38f150:self.query_result=a[1];return 0
        if e==META+0x100:return HANDLES.get(self.pack.cls(self.commands[a[0]]),0)
        if e==0x3a7d80:return 1 # elapsed movement timer already exists
        if e==0x391fe0:
            name=self.pack.rname(self.commands[a[3]])
            if name!=self.playing:
                self.playing=name;frames=self.action[name]
                self.deadline=None if frames is None else (self.now>>18<<18)+self.convert.duration(bits(frames))
            return 1
        if e==0x394b30:self.wait=True;return 0
        if e==0x394ae0:
            self.pending=self.pack.rname(self.commands[a[2]]);return 1
        if e==0x1cafc0:
            needle=self.read(a[1],4)
            try:return self.values(a[0]).index(needle)
            except ValueError:return -1
        if e==0x1ca620:
            self.list(a[0],self.values(a[0])+[self.read(a[1],4)]);return 0
        return super().call(e,a)
    def start(self,seq):
        self.current=seq;self.wait=False
        self.w(WORK+20,4,self.token(seq));self.w(WORK+24,4,self.seq[seq]);self.w(WORK+32,4,0)
        offset=self.invoke(0x3960f0,OWNER,WORK);assert offset!=0xffffffff
        self.w(WORK+28,4,offset);self.w(WORK+60,4,0)
        self.w(CHANNELS+3*44+8,1,0);self.w(CHANNELS+3*44+28,4,0)
        for i in range(3):
            if self.read(CHANNELS+i*44+32,1):self.invoke(0x392d90,CHANNELS+i*44)
        self.dispatch()
    def dispatch(self):
        self.invoke(0x395250,OWNER,INFO,NODE,WORK)
        if self.pending:
            seq=self.pending;self.pending=None;self.start(seq)
    def query(self,name=None,active=1,has_work=True):
        self.query_name=name;self.query_result=None;self.ee_reset()
        self.w(NODE+20,1,active);self.r[19]=NODE;self.r[20]=OWNER;self.r[16]=WORK if has_work else 0
        self.r[29]=0x1fff000;self.r[28]=0x55c870
        self.run_until(0x397100 if name is None else 0x397118,0x398be8)
        return self.query_result
    def tick(self,ns,previous):
        delta=bits(f32(f32((ns//100-previous//100)*100)/16666667.0))
        for i in (3,0,1,2):
            self.ee_reset();self.r[4]=CHANNELS+i*44;self.r[29]=0x1fff000;self.r[31]=0xfffffff0;self.f[12]=delta
            self.run_until(0x392e10,0xfffffff0)
        self.now=ns
        if self.wait and (self.deadline is None or (ns>>18<<18)>self.deadline):self.wait=False;self.dispatch()
        return bytes(self.read(CHANNELS+i,1) for i in range(176)).hex()
class Transform(World):
    # The matrix builder/assignment and rotation refresh are service leaves.
    # Execute the retail message gate and degree conversion around those leaves.
    def __init__(self,image,pos,rot,active):
        super().__init__(image);self.pos=pos;self.rot=rot;self.assigned=None;self.rotations=[]
        self.w(NODE+20,1,active);self.w(INFO+16,4,META);self.w(META,4,META+0x100)
        self.w(META+0x100+0x94,4,META+0x200);self.w(WORK+200,4,MOVES)
        self.list(MOVES,[CHANNELS+i*44 for i in range(4)])
        for i in range(176):self.w(CHANNELS+i,1,(i*19+7)&255)
    def call(self,e,a):
        a=[x&0xffffffff for x in a]
        if e==0x38f560:
            for i,v in enumerate(self.rot if a[2] else self.pos):self.w(a[0]+i*4,4,bits(v))
            return 0
        if e==0x190380:return 0
        if e==0x1909b0:
            self.assigned=[self.read(a[1]+i*4,4) for i in range(3)];return 0
        if e==0x191670:self.rotations.append(self.f[12]);return 0
        if e in (META+0x200,0x3956e0):return 0
        return super().call(e,a)
    def apply(self):
        before=bytes(self.read(CHANNELS+i,1) for i in range(176))
        self.ee_reset();self.r[19]=NODE;self.r[20]=OWNER;self.r[16]=WORK;self.r[17]=INFO
        self.r[18]=INFO;self.r[29]=0x1fff000;self.r[28]=0x55c870
        self.run_until(0x3978b8,0x398be8)
        assert before==bytes(self.read(CHANNELS+i,1) for i in range(176))
        return self.assigned
class Aim(World):
    """Retail AIMAP lookup/acquisition; Lua and timer refresh are controlled leaves."""
    def __init__(self,image,pack,target):
        super().__init__(image);self.target=target;self.callbacks=0;self.refreshes=0
        self.descend={0x394920}
        info=next(i for i in range(pack.cnt) if pack.cls(i)=='beModelCtrlInfo' and pack.rname(i)=='n_digilff')
        group=next(i for i in pack.list_ids(pack.fields(info)['slot5']) if pack.cls(i)=='beModelCtrlInfoDataAIM')
        self.mapids=pack.list_ids(pack.fields(group)['_aIMapList'])
        self.maps=[BASE+0x150000+i*0x100 for i in range(len(self.mapids))]
        self.names=[pack.rname(i) for i in self.mapids]
        self.maplist=BASE+0x154000;self.lookup=BASE+0x158000;self.aiwork=BASE+0x159000
        self.list(self.maplist,self.maps);self.w(self.lookup+16,4,self.maplist)
        for p,i in zip(self.maps,self.mapids):
            self.w(p+44,4,self.token(pack.fields(i)['_targetType'].rstrip('\0')))
        self.w(WORK+80,4,self.aiwork);self.w(INFO+8,4,self.token('n_digilff'))
        self.w(META+8,4,self.token('MAP01'))
    def string(self,p):
        if 0x100000<=p<0x554b00:
            chars=[]
            while self.read(p,1):chars.append(self.read(p,1));p+=1
            return bytes(chars).decode('ascii')
        return super().string(p)
    def call(self,e,a):
        a=[v&0xffffffff for v in a]
        if e==0x3022c0:
            if a[0]==self.maplist:return self.maps[self.names.index(self.string(a[2]))]
            assert self.string(a[2])=='AIM'
            return self.lookup
        if e==0x394400:
            assert a[:2]==[OWNER,NODE]
            assert [self.string(v) for v in a[2:5]]==['aim','WPos','n_digilff']
            assert a[5:]==[0,0,0]
            p=self.read(0x58a218,4);assert p
            for i,v in enumerate(self.target):self.w(p+i*4,4,bits(v))
            self.callbacks+=1;return 0
        if e==0x3a8580:
            assert a[0]==NODE and self.string(a[1])=='AITIMER',(a[0],self.string(a[1]))
            self.refreshes+=1;return 0
        return super().call(e,a)
    def apply(self):
        self.invoke(0x394920,OWNER,INFO,NODE,WORK,META)
        assert self.read(0x58a218,4)==0 and self.callbacks==self.refreshes==1
        return self.read(self.aiwork+12,4),[self.read(self.aiwork+16+i*4,4) for i in range(3)]
def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--elf',type=Path,default=ROOT.parent.parent / 'local/extracted/SLUS_208.36')
    ap.add_argument('--roms',type=Path,default=ROOT.parent.parent / 'local/extracted')
    ap.add_argument('--tool',type=Path,default=ROOT/'build/test_actorctrl');args=ap.parse_args()
    ii,ids=dump.load_igb(None)
    pack=dump.Pack(ii,ids,dump.afs_entry(args.roms/'NDMW.AFS',820),str(ROOT.parent / 'data/reflection.json'))
    native=subprocess.check_output([str(args.tool),str(args.roms),'--trace'],text=True).splitlines()
    image=args.elf.read_bytes();checks=0
    for name,seq in [('n_digilff','SQ_WALK02'),('n_digilfm','SQ_WALK03')]:
        w=Actor(image,pack,name);w.start(seq);previous=0
        assert w.query(seq,active=0)==0 and w.query(seq,has_work=False)==0
        queries={int(row.split()[2]):list(map(int,row.split()[3:])) for row in native if row.startswith('QUERY '+name+' ')}
        states=[s for s in native if s.startswith('STATE '+name+' ')]
        for row in states:
            _,_,ns,value=row.split();ns=int(ns)
            got=w.tick(ns,previous);assert value==got,(name,ns,value,got);previous=ns;checks+=1
            assert queries[ns]==[w.query(),w.query(seq),w.query('SQ_MISSING')],(name,ns)
        w.start('SQ_WAIT02')
        events=[s for s in native if s.startswith('TRACE '+name+' ')]
        assert events==w.events,(events,w.events)
    control=Actor(image,pack,'n_digilff');control.name='control'
    controls={int(s.split()[1]):(int(s.split()[2]),int(s.split()[3],16)) for s in native if s.startswith('CONTROL ')}
    for i,seq in enumerate(('SQ_WAIT','SQ_TALK','SQ_WAIT02')):
        control.now=i*1000000000;control.start(seq)
        assert controls[i]==(control.read(WORK+60,4),control.read(WORK+124,4))
    assert control.events==[s for s in native if s.startswith('TRACE control ')]
    placements=[((60,10,-10),(0,117,0)),((63.12,10,-55.8),(0,78.8,0)),
                ((69.11,10,-13.79),(0,-90,0)),((240,40,-150),(0,0,0)),((258.187,40,174),(0,180,0))]
    for row in (s for s in native if s.startswith('TRANS ')):
        fields=row.split();active,index=map(int,fields[1:3]);position,rotation=placements[index]
        w=Transform(image,position,rotation,active);assigned=w.apply()
        values=[int(v,16) for v in fields[3:]]
        assert values==([bits(v) for v in position+rotation] if active else [0]*6)
        assert assigned==([bits(v) for v in position] if active else None)
        if active:
            # 3c8efa35 is the degree-to-radian multiplier in retail case 24.
            from ee_core import f_mul
            assert w.read(WORK+132,4)==f_mul(bits(rotation[1]),0x3c8efa35)
    aimrows=[s.split() for s in native if s.startswith('AIM ')]
    assert len(aimrows)==128
    for row in aimrows:
        _,iteration,hp,index,x,y,z,*metadata=row
        target=tuple(map(float,(x,y,z)));w=Aim(image,pack,target)
        selected,got=w.apply()
        assert selected==int(index)==1 and got==[bits(v) for v in target]
        r=pack.rec(w.mapids[selected]);q=r['off']+8;raw=[]
        # igb_inst's readable float values round to four decimals. Compare the
        # descriptor-selected raw words instead, including the rotation limit.
        for ty,ordinal,width in pack.dirs[r['classIndex']]['trips']:
            if ty==4:q+=4+struct.unpack_from('<I',pack.blob,q)[0]
            else:
                if ordinal in (3,4,5,6):raw.append(struct.unpack_from('<I',pack.blob,q)[0])
                q+=(width+3)&~3
        assert [int(v,16) for v in metadata]==raw
    print('Actor retail: 128 AIMAP lookups, WPos callback selectors/target publication and timer-removal calls passed')
    print('Actor retail: original CTRL/MUTEKI and label-section stop traces passed')
    print('Actor retail: 10 MOVETRANS active/inactive placements and retained-channel gates passed')
    print(f'Actor retail: original female/male arrival command traces and {checks} complete channel states and {checks*3} numeric queries passed')
if __name__=='__main__':main()
