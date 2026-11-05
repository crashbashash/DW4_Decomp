#!/usr/bin/env python3
"""Compare the recovered title tick with execution of retail MIPS instructions.

No game bytes are embedded. Loads the user's ELF; stubs only the documented
engine boundary. This verifies state writes and ordered engine calls, not pixels,
engine implementations, initial object allocation, or byte-matched compilation.
"""
import argparse
import ctypes as C
import hashlib
import itertools
from pathlib import Path
import random
import struct
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
MASK = (1 << 64) - 1
CTRL, OPTION, PAD = 0x01002000, 0x01003000, 0x01004000
SELF, INFO, COMMON = 0x01000000, 0x01001000, 0x01009000


def sx(n, bits):
    n &= (1 << bits) - 1
    return n - (1 << bits) if n >> (bits - 1) else n


class Retail:
    """The small integer R5900 subset actually used by the recovered tick.

    Delay slots execute before the branch/call. Word arithmetic and lw sign extend
    to the EE's 64-bit scalar registers; sq/lq preserve the unused high half as zero.
    Unknown instructions/callees and writes outside the supplied objects fail closed.
    """
    def __init__(self, image):
        self.image = image
        self.covered = set()

    def read(self, address, size):
        if 0x100000 <= address and address + size <= 0x554b00:
            return int.from_bytes(self.image[address-0x100000+0x80:address-0x100000+0x80+size], 'little')
        return sum(self.mem.get(address+i, 0) << (i*8) for i in range(size))

    def write(self, address, size, value):
        if not (SELF <= address < 0x01010000 or 0x01f00000 <= address < 0x02000000 or address == 0x554e70):
            raise AssertionError(f'unexpected write {address:#x}')
        for i in range(size):
            self.mem[address+i] = (value >> (8*i)) & 255
        if address in (COMMON+0x10c, COMMON+0x20c):
            field = 0x518328 if address == COMMON+0x10c else 0x518338
            self.events.append((18, COMMON, field, sx(value,32), 0))
        if address == 0x554e70:
            assert value == 1
            self.events.append((19,0,0,0,0))

    def call(self, address):
        r = self.r
        args = [sx(r[i],32) for i in range(4,9)]
        if address == 0x3022c0:
            r[2] = {0x518348: CTRL, 0x518350: 0x01005000, 0x518360: 0x01006000, 0x5184a0: OPTION}[args[2]]
            return
        if address == 0x39b810:
            r[2] = PAD
            return
        if address == 0x3a9220:
            r[2] = COMMON + {0x518328:0x100,0x518338:0x200}[args[1]]
            return
        # (event code, number of meaningful arguments after receiver, query index)
        hooks = {
            0x3e44f0:(0,0,0), 0x3e4280:(1,0,1), 0x3e44d0:(2,0,2),
            0x3e4480:(3,2,3), 0x3e3b80:(4,4,0), 0x3e4030:(5,4,0),
            0x3e42a0:(6,4,0), 0x3ebe00:(7,2,0), 0x3ec050:(8,1,0),
            0x38d860:(9,3,0), 0x38e5d0:(10,1,0), 0x38e670:(11,2,0),
            0x38f830:(12,1,0), 0x38f250:(13,1,0), 0x38e060:(14,1,0),
            0x38e5f0:(15,4,0), 0x38f220:(16,1,4), 0x38f800:(17,1,5),
        }
        if address not in hooks:
            raise AssertionError(f'unhandled callee {address:#x}')
        code,n,query = hooks[address]
        self.events.append(tuple([code]+args[1:1+n]+[0]*(4-n)))
        r[2] = self.answers[query] if query else 0

    def step(self, pc, delay=False):
        self.covered.add(pc)
        w = self.read(pc,4)
        op,rs,rt,rd,sh,fn = w>>26,(w>>21)&31,(w>>16)&31,(w>>11)&31,(w>>6)&31,w&63
        imm = sx(w,16)
        r = self.r
        dest = None
        call = False
        if op == 0:
            if fn == 0: r[rd] = sx((r[rt]&0xffffffff)<<sh,32)&MASK
            elif fn == 8: dest = r[rs]&0xffffffff
            elif fn in (0x21,0x2d): r[rd] = (sx(r[rs]+r[rt],32) if fn==0x21 else r[rs]+r[rt])&MASK
            elif fn == 0x25: r[rd] = r[rs] | r[rt]
            elif fn == 0x3c: r[rd] = (r[rt] << (sh+32))&MASK
            elif fn == 0x3e: r[rd] = r[rt] >> (sh+32)
            elif fn == 0x3f: r[rd] = (sx(r[rt],64) >> (sh+32))&MASK
            else: raise AssertionError(f'R opcode {w:#x} at {pc:#x}')
        elif op in (2,3):
            dest = ((pc+4)&0xf0000000)|((w&0x3ffffff)<<2)
            if op==3: r[31]=pc+8;call=True
        elif op in (1,4,5,6,7):
            if op == 1:
                assert rt in (0,1), f'unsupported REGIMM {w:#x} at {pc:#x}'
            take = {1:lambda:sx(r[rs],64)>=0 if rt==1 else sx(r[rs],64)<0,
                    4:lambda:r[rs]==r[rt],5:lambda:r[rs]!=r[rt],
                    6:lambda:sx(r[rs],64)<=0,7:lambda:sx(r[rs],64)>0}[op]()
            dest = pc+4+(imm<<2) if take else pc+8
        elif op == 9: r[rt]=sx(r[rs]+imm,32)&MASK
        elif op == 0x19: r[rt]=(r[rs]+imm)&MASK
        elif op == 0xf: r[rt]=sx((w&0xffff)<<16,32)&MASK
        elif op == 0xc: r[rt]=r[rs]&(w&0xffff)
        elif op == 0xd: r[rt]=r[rs]|(w&0xffff)
        elif op == 0xa: r[rt]=int(sx(r[rs],64)<imm)
        elif op == 0xb: r[rt]=int(r[rs]<(imm&MASK))
        elif op in (0x23,0x24,0x37,0x1e):
            size={0x23:4,0x24:1,0x37:8,0x1e:16}[op]
            v=self.read((r[rs]+imm)&0xffffffff,size)
            r[rt]=(sx(v,32) if op==0x23 else v)&MASK
        elif op in (0x2b,0x28,0x3f,0x1f):
            self.write((r[rs]+imm)&0xffffffff,{0x2b:4,0x28:1,0x3f:8,0x1f:16}[op],r[rt])
        else: raise AssertionError(f'opcode {w:#x} at {pc:#x}')
        r[0]=0
        if dest is not None:
            assert not delay, f'branch in delay slot at {pc:#x}'
            self.step(pc+4,True)
            if call:
                self.call(dest)
                return pc+8
            return dest
        return pc+4

    def tick(self, ctrl, option, pad, run, answers):
        self.mem={};self.events=[];self.answers=answers
        for off,val in [(20,0x01008000),(32,0x01007000)]: self.write(SELF+off,4,val)
        self.write(INFO+40,4,0x0100a000)
        self.write(INFO+24,4,run)
        for i,val in enumerate(ctrl): self.write(CTRL+24+i*4,4,val)
        for i,val in enumerate(option): self.write(OPTION+20+i*4,4,val)
        for off,val in zip((28,32,72,76),pad): self.write(PAD+off,4,val)
        self.r=[0]*32;self.r[4]=SELF;self.r[5]=INFO
        self.r[28]=0x55c870;self.r[29]=0x01fff000;self.r[31]=0xfffffff0
        pc=0x3f2ef0
        for _ in range(10000):
            if pc==0xfffffff0: break
            pc=self.step(pc)
        else: raise AssertionError('retail tick did not return')
        return ([sx(self.read(CTRL+24+i*4,4),32) for i in range(6)],
                [sx(self.read(OPTION+20+i*4,4),32) for i in range(9)],self.events)


class Event(C.Structure):
    _fields_=[('code',C.c_int),('args',C.c_int*4)]


def verify(elf,random_cases):
    image=elf.read_bytes()
    if image[:4] != b'\x7fELF' or hashlib.sha1(image[0x80:0x454b80]).hexdigest() != 'ffad4dab663cb290190bdfa34a8016d616a1652a':
        raise ValueError('expected the unmodified SLUS-20836 retail ELF section')
    oracle=Retail(image)
    with tempfile.TemporaryDirectory(prefix='dw4-menu-') as tmp:
        library=Path(tmp)/'title.so'
        subprocess.run(['cc','-std=c99','-Wall','-Wextra','-Werror','-shared','-fPIC','-O2',
                        str(ROOT/'recovered/frontend/title-menu.c'),
                        str(ROOT/'recovered/frontend/title-menu-test.c'),'-o',str(library)],check=True)
        fn=C.CDLL(str(library)).title_test_tick
        fn.argtypes=[C.POINTER(C.c_int32),C.POINTER(C.c_int32),C.POINTER(C.c_uint32),C.c_int,
                     C.POINTER(C.c_int),C.POINTER(Event)]
        count=0
        def check(ctrl,option,pad,run,answers):
            nonlocal count
            expected=oracle.tick(ctrl,option,pad,run,answers)
            a=(C.c_int32*6)(*ctrl);b=(C.c_int32*9)(*option);p=(C.c_uint32*4)(*pad)
            q=(C.c_int*6)(*answers);out=(Event*128)()
            n=fn(a,b,p,run,q,out)
            actual=(list(a),list(b),[(e.code,*e.args) for e in out[:n]])
            assert actual==expected, (ctrl,option,pad,run,answers,expected,actual)
            count+=1
        # Every explicit state/phase and recognized input independently; then mixed
        # inputs, option variants and asynchronous answers using a fixed seed.
        inputs=[0,8,0x10,0x20,0x40,0x80,0x2000,0x4000,0x4010,0x6000]
        states=itertools.product((0,1,2,3,4,5,6,7,8,9),(0,1,2,3,4,50),(0,1,2,3),(0,1,1000,1001,1002,1003))
        for st in states:
            for pressed in inputs:
                for done in (0,1):
                    check([0,0,*st],[0,0,0,0,1,1,0,1,1],[0,0,pressed,0],1,[0,done,done,done,done,COMMON])
        # Exercise every option row and regional language choice at each option
        # phase. This also covers the hidden US language row's skip behavior.
        for language,row,country,camera,light in itertools.product(range(3),range(4),range(7),range(2),range(2)):
            option=[language,row,0,camera,light,0,camera,light,country]
            for phase,step in ((0,0),(0,1),(1,0),(1,1),(2,0),(2,3),(50,2)):
                for pressed in (0,0x10,0x20,0x40,0x80,0x2000,0x4000):
                    check([0,0,4,phase,step,0],option,[0,0,pressed,0],1,[0,1,1,1,1,COMMON])
        rng=random.Random(0x3f2ef0)
        for _ in range(random_cases):
            ctrl=[rng.randrange(2),rng.randrange(4),rng.choice((0,1,2,4,7,8)),rng.choice((0,1,2,3,50)),rng.randrange(4),rng.choice((0,1,1000,1001,1002,1003))]
            opt=[rng.randrange(3),rng.randrange(4),rng.randrange(2),rng.randrange(2),rng.randrange(2),rng.randrange(2),rng.randrange(2),rng.randrange(2),rng.randrange(7)]
            pad=[rng.randrange(16),rng.randrange(16),rng.choice(inputs),rng.choice(inputs)]
            check(ctrl,opt,pad,rng.randrange(2),[0,*[rng.randrange(2) for _ in range(4)],COMMON])
        print(f'{count} retail-vs-C ticks agree: state writes and ordered engine calls; {len(oracle.covered)} retail instructions exercised')
        return oracle.covered


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--elf',type=Path,default=ROOT/'orig/SLUS-20836/SLUS_208.36')
    parser.add_argument('--random-cases',type=int,default=10000)
    args=parser.parse_args()
    verify(args.elf,args.random_cases)

if __name__=='__main__': main()
