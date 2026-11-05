#!/usr/bin/env python3
"""STATUS skill refresh and item colors against retail instruction slices."""
from native_shared import build_shared
import ctypes as C
import itertools
import subprocess
import tempfile
from pathlib import Path
from verify_statusviews_retail import Command, IO
from verify_statusctrl_retail import Retail, ROOT, BASE, NODE

class Item(C.Structure):
    _fields_=[(n,C.c_int32) for n in ('kind','record','equipped','revision','pocket')]
class Content(Retail):
    def call(self,e,a):
        a=[x&0xffffffff for x in a]
        if e==0x38e5d0:self.category=self.string(a[1]);self.args=[];return 0
        if e==0x38f830:self.args.append(self.string(a[1]));return 0
        if e in (0x38e5f0,0x38f250,0x38e060):
            if e==0x38e060 and self.category=='TEXTCTL':self.events.append((self.string(a[1]),*self.args))
            return 0
        if e==0x236f80:return BASE+0x198000
        if e==0x3a9340:return BASE+0x190100
        if e==0x12a78c:return len(self.string(a[0]) or '')
        if e==0x30b3c0:
            self.buffer=self.string(a[1]) or '';self.putbuffer(a[0]);return 0
        if e==0x30b460:
            text=self.string(a[1]) or '';pos=a[2]
            self.buffer=self.buffer[:pos]+text+self.buffer[pos:];self.putbuffer(a[0]);return 0
        if e==0x38f4b0:
            self.args.append(tuple(self.read(a[1]+i*4,4) for i in range(3)));return 0
        if e==0x38f800:return BASE+0x190000
        if e==0x3a9340:return BASE+0x190100
        if e==0x3a9580:return self.token('Technique' if getattr(self,'flag_mode',False) and self.string(a[2])=='TXT' else 'Explanation')
        if e==0x447cb0:return self.token('Explanation' if self.string(a[2])=='NAME' else 'Technique')
        if e==0x3f5920:self.events.append(('SCRIPT',C.c_int32(a[2]).value));return 0
        if e==0x129e60:
            data=(self.string(a[1])%C.c_int32(a[2]).value).encode()+b'\0'
            for i,b in enumerate(data):self.w(a[0]+i,1,b)
            return len(data)-1
        return super().call(e,a)
    def string(self,p):
        p&=0xffffffff
        if not p:return None
        out=[]
        while self.read(p,1):out.append(self.read(p,1));p+=1
        return bytes(out).decode('latin1')
    def putbuffer(self,p):
        data=self.buffer.encode('latin1')+b'\0'
        for i,b in enumerate(data):self.w(BASE+0x199000+i,1,b)
        self.w(p+8,4,BASE+0x199000);self.w(p+12,4,len(data)-1)
    def device(self,items,enabled,page,pages,selected,bank,rows,desc):
        self.events=[];self.category=None;self.inventory=True;self.descend={0x447d00}
        for off,val in [(48,selected),(84,page),(88,pages),(96,bank),(112,BASE+0x19a000)]:self.w(NODE+off,4,val)
        self.w(BASE+0x198048,4,BASE+0x19b000);self.w(BASE+0x19b004,4,1000)
        self.w(BASE+0x19010c,4,BASE+0x194000)
        self.list(BASE+0x194000,[BASE+0x195000+i*32 for i in range(len(items))])
        for j,item in enumerate(items):
            for off,val in zip((8,12,16,20,24),item):self.w(BASE+0x195000+j*32+off,4,val)
        self.list(BASE+0x19a000,enabled,1)
        self.invoke(0x418ac0,NODE,rows,desc);self.descend=set();return self.events
    def number(self,variant,value,width):
        self.events=[];self.category=None
        self.w(NODE+44,4,variant)
        self.invoke(0x4402e0,NODE,value,width,self.token('font%03d'));return self.events
    def flag(self,indices,selected,rows,desc):
        self.events=[];self.category=None;self.flag_mode=True
        self.w(NODE+84,4,BASE+0x191000);self.list(BASE+0x191000,indices)
        self.w(NODE+48,4,selected)
        self.invoke(0x41aaa0,NODE,rows,desc)
        self.flag_mode=False;return self.events
    def refresh(self,used,levels,mode,page,pages,selected,rows,desc):
        self.events=[];self.category=None;self.inventory=False
        self.w(NODE+100,4,BASE+0x191000);self.w(BASE+0x19101c,4,BASE+0x192000)
        order=[i for i,v in enumerate(used) if v&255]
        if 3 in order:order.remove(3);order.insert(0,3)
        self.list(BASE+0x192000,[BASE+0x193000+i*32 for i in range(len(order))])
        for j,i in enumerate(order):
            p=BASE+0x193000+j*32
            for off,val in [(8,i),(12,self.token('Species')),(16,levels[i])]:self.w(p+off,4,val)
        for off,val in [(48,selected),(84,page),(88,pages),(96,mode)]:self.w(NODE+off,4,val)
        self.w(BASE+0x19010c,4,BASE+0x194000);self.list(BASE+0x194000,[BASE+0x195000+i*32 for i in range(6)])
        self.invoke(0x420230,NODE,int(rows),int(desc));return self.events

def main():
    elf=ROOT.parent.parent/'local/extracted/SLUS_208.36'
    if not elf.exists():print('STATUS content: private ELF unavailable, skipped');return
    w=Content(elf.read_bytes());total=colors=devices=flag_traces=numbers=0
    with tempfile.TemporaryDirectory() as td:
        stub=Path(td)/'db.c';stub.write_text('''#include "dw4/statuscontent.h"
const dw4_database *dw4_databases_get(const dw4_databases *d,const char *n){(void)d;(void)n;return (const dw4_database *)1;}
const char *dw4_database_string(const dw4_database *d,int32_t r,const char *k){(void)d;(void)r;return !strcmp(k,"TXT")?"Technique":"Explanation";}
const char *dw4_databases_shinka_name(void *d,int32_t r){(void)d;(void)r;return "Species";}
int dw4_playerstats_item_attribute(void *d,const dw4_item_record *i,const char *k,int32_t *o){(void)d;(void)i;(void)k;(void)o;return -1;} /* XDATA chip content only */
int dw4_playerstats_form(const dw4_databases *d,const dw4_property_folder *f,int32_t sp,int32_t o[16]){(void)d;(void)f;(void)sp;(void)o;return -1;} /* Evolve preview only */
int dw4_database_number(const dw4_database *d,int32_t r,const char *k,int32_t *o){(void)d;(void)r;(void)k;(void)o;return -1;} /* shop and sell lists only */
int dw4_playerstats_item_price(void *d,const dw4_item_record *i,int s,int32_t *o){(void)d;(void)i;(void)s;(void)o;return -1;} /* shop goods and sell lists only */
'''.replace('#include "dw4/statuscontent.h"','#include "dw4/statuscontent.h"\n#include <string.h>'))
        so=Path(td)/'content.so'
        build_shared(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'include'),str(ROOT/'src/statuscontent.c'),str(ROOT/'src/playerrecords.c'),str(stub),'-lm','-o',str(so)],check=True)
        lib=C.CDLL(str(so));lib.dw4_playerrecords_open.restype=C.c_void_p
        lib.dw4_playerrecords_close.argtypes=[C.c_void_p];lib.dw4_playerrecords_get.argtypes=[C.c_void_p,C.c_char_p,C.c_int32];lib.dw4_playerrecords_get.restype=C.c_void_p
        lib.dw4_property_set_array.argtypes=[C.c_void_p,C.c_char_p,C.POINTER(C.c_int32),C.c_size_t]
        lib.dw4_property_set_items.argtypes=[C.c_void_p,C.c_char_p,C.POINTER(Item),C.c_size_t]
        lib.dw4_statuscontent_skill.argtypes=[C.c_void_p,C.c_void_p]+[C.c_int32]*7+[IO,C.c_void_p]
        lib.dw4_statuscontent_device.argtypes=[C.c_void_p,C.POINTER(Item),C.c_size_t,C.POINTER(C.c_uint8)]+[C.c_int]*6+[IO,C.c_void_p]
        lib.dw4_statuscontent_number.argtypes=[C.c_int,C.c_int32,C.c_int,IO,C.c_void_p]
        lib.dw4_statuscontent_flag.argtypes=[C.c_void_p,C.POINTER(C.c_int32),C.c_size_t,C.c_int,C.c_int,C.c_int,IO,C.c_void_p]
        lib.dw4_statuscontent_item_color.argtypes=[C.POINTER(Item),C.POINTER(C.c_float)]
        p=lib.dw4_playerrecords_open();f=lib.dw4_playerrecords_get(p,b'GETPLAYER',0)
        try:
            levels=[1,-1,999,10,31,37,108,228,2147483647,-2147483648,50,60,70,80,90,100]
            assert not lib.dw4_property_set_array(f,b'BASE_LEVEL',(C.c_int32*16)(*levels),16)
            assert not lib.dw4_property_set_items(f,b'WAZALIST',(Item*6)(*[Item(9,i,0,0,0) for i in range(6)]),6)
            for mask in (0,1,8,15,255,511,65535):
                used=[(mask>>i)&1 for i in range(16)]
                assert not lib.dw4_property_set_array(f,b'BASE_ISUSE',(C.c_int32*16)(*used),16)
                for mode,page,pages,selected,rows,desc in itertools.product(range(3),range(2),range(1,3),range(-1,9),range(2),range(2)):
                    if page>=pages or (rows and mode!=0) or (mode==0 and selected>=8) or (mode==2 and selected>=6):continue
                    expected=w.refresh(used,levels,mode,page,pages,selected,rows,desc);events=[]
                    @IO
                    def io(u,ptr):
                        c=ptr.contents
                        dec=lambda x:x.decode() if x else None
                        if c.op==7:events.append(('TEXTSET',dec(c.group),dec(c.name),dec(c.value)))
                        elif c.op==4:events.append(('SWITCH',dec(c.group),dec(c.name),dec(c.value)))
                        elif c.op==3:events.append(('SCRIPT',c.slot))
                        else:raise AssertionError(c.op)
                        return 0
                    rc=lib.dw4_statuscontent_skill(p,1,0,mode,page,pages,selected,rows,desc,io,None)
                    assert rc==0 and events==expected,(mask,mode,page,pages,selected,rows,desc,rc,events,expected)
                    total+=1
            for count,page,selected,bank,rows,desc in itertools.product((0,1,12,13,25,36),range(3),(0,11),range(2),range(2),range(2)):
                items=[(i%4,276 if i%7==0 else 31 if i%7==1 else i,i%2,(i*101)-1,i%6) for i in range(count)]
                flags=[i%2 for i in range(12)];events=[]
                expected=w.device(items,flags,page,3,selected,bank,rows,desc)
                @IO
                def io(u,ptr):
                    c=ptr.contents;dec=lambda x:x.decode('latin1') if x else None
                    key={7:'TEXTSET',4:'SWITCH',6:dec(c.key)}[c.op]
                    val=dec(c.value)
                    if key=='COLOR':
                        val=tuple(int.from_bytes(C.c_float(float(x)),'little') for x in val[2:-1].split(','))
                    event=(key,dec(c.group),dec(c.name))
                    events.append(event+(val,) if val is not None else event);return 0
                rc=lib.dw4_statuscontent_device(1,(Item*count)(*[Item(*i) for i in items]),count,(C.c_uint8*12)(*flags),page,3,selected,bank,rows,desc,io,None)
                assert rc==0 and events==expected,(count,page,selected,bank,rows,desc,rc,events,expected)
                devices+=1
            for count in range(13):
                indices=list(range(12-count,12))
                for selected,rows,desc in itertools.product(range(max(count,1)),range(2),range(2)):
                    expected=w.flag(indices,selected,rows,desc);events=[]
                    @IO
                    def io(u,ptr):
                        c=ptr.contents;dec=lambda x:x.decode() if x else None
                        events.append(({7:'TEXTSET',4:'SWITCH'}[c.op],dec(c.group),dec(c.name),dec(c.value)));return 0
                    rc=lib.dw4_statuscontent_flag(1,(C.c_int32*count)(*indices),count,selected,rows,desc,io,None)
                    assert rc==0 and events==expected,(indices,selected,rows,desc,rc,events,expected)
                    flag_traces+=1
            for variant,value,width in itertools.product(range(4),(0,1,9,10,99,100,999,1000,999999,1000000,9999999),range(8)):
                expected=w.number(variant,value,width);events=[]
                @IO
                def io(u,ptr):
                    c=ptr.contents;dec=lambda x:x.decode() if x else None
                    events.append(({7:'TEXTSET',4:'SWITCH'}[c.op],dec(c.group),dec(c.name),dec(c.value)));return 0
                rc=lib.dw4_statuscontent_number(variant,value,width,io,None)
                assert rc==0 and events==expected,(variant,value,width,rc,events,expected)
                numbers+=1
            for kind,record,revision in itertools.product(range(10),[0,31,44,276],[-2147483648,-1,0,1,30,31,100,101,500,501,999,1000,2147483647]):
                item=Item(kind,record,0,revision,0);rgb=(C.c_float*3)();lib.dw4_statuscontent_item_color(C.byref(item),rgb)
                for off,val in [(8,kind),(12,record),(20,revision)]:w.w(BASE+0x196000+off,4,val)
                w.invoke(0x447d00,BASE+0x197000,BASE+0x196000)
                got=[int.from_bytes(C.c_float(v),'little') for v in rgb]
                expected=[w.read(BASE+0x197000+i*4,4) for i in range(3)]
                assert got==expected,(item.kind,record,revision,got,expected);colors+=1
        finally:lib.dw4_playerrecords_close(p)
    print(f'STATUS content: {total} skill page/description traces and {devices} DEVICE traces and {flag_traces} FLAG refresh traces and {numbers} number traces and {colors} item color cases match retail; database/property leaves controlled')
if __name__=='__main__':main()
