#!/usr/bin/env python3
"""Verify a saved clock -> manager dispatcher -> logo Action2 update chain.

Reads EE RAM offline. This proves topology in the supplied snapshot, not how
many callbacks occurred between snapshots or where a game-pause request starts.
"""
import argparse
import json
from system_clock_probe import _extract, SYS_CLOCK


def inspect(state, clock=SYS_CLOCK):
    ram=_extract(state)
    def read(a,n=4):
        if not 0x100000<=a<=len(ram)-n:raise ValueError(f'out-of-range pointer {a:#x}')
        return int.from_bytes(ram[a:a+n],'little')
    def virtual(obj,slot):
        v=read(obj)
        if not 0x100000<=v<0x554b00:raise ValueError(f'invalid vtable {v:#x}')
        return read(v+slot)
    def items(lst):
        count=read(lst+8);capacity=read(lst+12);data=read(lst+16)
        if not count<=capacity<=100000:raise ValueError('invalid list bounds')
        return [read(data+4*i) for i in range(count)]
    def name(act):
        p=read(read(act+0xc)+8)
        read(p)
        end=ram.find(b'\0',p,min(p+256,len(ram)))
        if end<0:raise ValueError('unterminated action name')
        return ram[p:end].decode('ascii')
    assert read(clock)==0x52c990, 'not the captured igInsightCore class'
    source=read(clock+0x30);dispatcher=read(clock+0xc)
    assert virtual(source,0x68)==0x330af0
    assert virtual(source,0x94)==0x32dab0
    assert virtual(dispatcher,0x5c)==0x237ec0
    managers=items(read(read(dispatcher+8)+8))
    found=[]
    for mi,manager in enumerate(managers):
        if virtual(manager,0x74)!=0x378bc0 or virtual(manager,0x84)!=0x3778d0:continue
        assert read(manager+0xc)==clock
        parent=read(manager+0x10)
        enabled=bool(read(parent+0x2c,1)&int(read(parent+0x2d,1)==0))
        enabled=enabled and bool(read(manager+0x1c,1)) and not read(parent+0x2e,1)
        for gi,group in enumerate(items(read(manager+0x18))):
            for ai,act in enumerate(items(read(group+0x18))):
                if name(act)=='j_startlogo':
                    found.append(dict(manager=hex(manager),manager_index=mi,
                                      group_index=gi,action_index=ai,action=hex(act),
                                      gate_open=enabled,update=hex(virtual(manager,0x84))))
    if not found:raise ValueError('no logo action in the verified dispatcher path')
    return dict(clock=hex(clock),class_name='igInsightCore',source=hex(source),
                sample_ns=read(clock+0x38,8),clock_ns=read(clock+0x50,8),
                scheduler=hex(dispatcher),manager_count=len(managers),logo_actions=found)


def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('state')
    ap.add_argument('--clock',type=lambda s:int(s,0),default=SYS_CLOCK)
    a=ap.parse_args()
    print(json.dumps(inspect(a.state,a.clock),indent=2))
if __name__=='__main__':main()
