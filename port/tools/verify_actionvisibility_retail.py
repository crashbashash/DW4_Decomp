#!/usr/bin/env python3
"""Execute retail HIDE and active ACTION switch-bit fragments.

The surrounding message receiver, allocation and component selection are not
executed. These fragments establish the bit lifecycle used by native model
presentation; actual STATUS root checks separately exercise that integration.
"""
import itertools
from verify_scriptservices_retail import World, ROOT, BASE

class Removal(World):
    def call(self,entry,args):
        if entry==0x3a8760:
            self.reset_requests.append(args[0]&0xffffffff);return 0
        if entry==0x2ff820:
            self.released.append(args[0]&0xffffffff);return 0
        return super().call(entry,args)


def main():
    image = (ROOT.parent.parent / "local/extracted/SLUS_208.36").read_bytes()
    w = World(image)
    listing, words, work, act, info, switch = [BASE + 0x280000 + i * 0x1000 for i in range(6)]
    stack = 0x1fff000
    count = 0
    for slot, initial in itertools.product(range(128), (0, 0xffffffff, 0x55555555, 0xaaaaaaaa)):
        w.w(listing + 8, 4, 4)
        w.w(listing + 16, 4, words)
        w.w(act + 8, 4, slot)
        w.w(act + 12, 4, info)
        w.w(info + 28, 4, switch)
        w.w(switch + 32, 4, listing)
        for j in range(4):
            w.w(words + j * 4, 4, initial)
        w.ee_reset()
        w.r[18] = act
        w.run_until(0x376990, 0x376db8)
        expected = [initial] * 4
        expected[slot // 32] &= ~(1 << (slot % 32))
        assert [w.read(words + j * 4, 4) for j in range(4)] == expected
        w.ee_reset()
        w.r[22], w.r[23], w.r[29] = slot, listing, stack
        w.w(stack + 0xbc, 4, work)
        w.w(work + 16, 1, 99)
        w.run_until(0x378268, 0x3782b0)
        expected[slot // 32] |= 1 << (slot % 32)
        assert [w.read(words + j * 4, 4) for j in range(4)] == expected
        assert w.read(work + 16, 1) == 0
        count += 1
    print(f"Action2 visibility: {count} original HIDE/active-ACTION switch-bit pairs pass; "
          "all four words checked, receiver/allocation/component leaves outside fragment scope")
    w=Removal(image);node,attrs,array=BASE+0x287000,BASE+0x288000,BASE+0x289000
    removals=0
    for size,refs in itertools.product((0,1,7,8,9,16,17),(1,2,0x10000001)):
        w.reset_requests=[];w.released=[]
        w.w(act+44,4,node);w.w(node+136,4,attrs)
        w.w(attrs+8,4,size);w.w(attrs+16,4,array)
        pointers=[BASE+0x290000+i*32 if i%3 else 0 for i in range(size)]
        for i,pointer in enumerate(pointers):
            w.w(array+i*4,4,pointer)
            if pointer:w.w(pointer+4,4,refs)
        # Preserve canaries beyond the original count, including unrolled clears.
        for i in range(size,size+8):w.w(array+i*4,4,0xdeadbeef)
        w.w(listing+8,4,4);w.w(listing+16,4,words)
        for i in range(4):w.w(words+i*4,4,0xffffffff)
        w.w(act+56,4,work);w.w(work+4,4,2);w.w(act+20,1,1)
        w.ee_reset();w.r[17],w.r[22],w.r[23]=act,63,listing
        w.run_until(0x377d38,0x377f20)
        assert w.read(attrs+8,4)==0
        assert [w.read(array+i*4,4) for i in range(size)]==[0]*size
        assert [w.read(array+i*4,4) for i in range(size,size+8)]==[0xdeadbeef]*8
        assert [w.read(pointer+4,4) for pointer in pointers if pointer]==[refs-1]*sum(bool(p) for p in pointers)
        assert w.released==([p for p in pointers if p] if (refs-1)&0x7fffff==0 else [])
        assert [w.read(words+i*4,4) for i in range(4)]==[0xffffffff,0x7fffffff,0xffffffff,0xffffffff]
        assert w.read(work+4,4)==1 and w.read(act+56,4)==0 and w.read(act+20,1)==0
        assert w.reset_requests==[act]
        removals+=1
    print(f'Action2 REMOVE: {removals} original default-attribute releases/clears, switch/Work retirement and inactive writes pass; allocation/reset leaves controlled')


if __name__ == "__main__":
    main()
