"""Create three reviewed object-base leaf callbacks in the analysed Ghidra program.

Run without analysis, then regenerate function/symbol snapshots with their owning
scripts. Each entry is proven by literal registrar arguments and exact leaf words;
this script refuses overlap and rolls back on any failed check.
"""
from ghidra.program.model.address import AddressSet
from ghidra.program.model.symbol import SourceType
ROWS=((0x135530,(0x3c010058,0x03e00008,0x8c227198)),
      (0x2ff4a0,(0x03e00008,0x0000102d)),
      (0x2ff560,(0x3c010058,0x03e00008,0x8c227198)))

def main():
    space=currentProgram.getAddressFactory().getDefaultAddressSpace()
    memory=currentProgram.getMemory();manager=currentProgram.getFunctionManager()
    tx=currentProgram.startTransaction('Reviewed object-base callback leaves');ok=False
    try:
        for va,words in ROWS:
            start=space.getAddress(va);end=space.getAddress(va+4*len(words)-1)
            for i,word in enumerate(words):
                if int(memory.getInt(space.getAddress(va+i*4)))&0xffffffff!=word:raise ValueError('unexpected instruction at %#x'%(va+i*4))
            existing=manager.getFunctionAt(start)
            if existing:
                body=existing.getBody()
                if (int(body.getNumAddresses())!=len(words)*4 or int(body.getMinAddress().getOffset())!=va or int(body.getMaxAddress().getOffset())!=va+len(words)*4-1):raise ValueError('existing extent differs at %#x'%va)
                continue
            for i in range(len(words)*4):
                if manager.getFunctionContaining(space.getAddress(va+i)) is not None:raise ValueError('function overlap at %#x'%va)
            fn=manager.createFunction('FUN_%08x'%va,start,AddressSet(start,end),SourceType.USER_DEFINED)
            if fn is None:raise ValueError('failed to create %#x'%va)
            print('created reviewed callback %#x / %d bytes'%(va,len(words)*4))
        ok=True
    finally:currentProgram.endTransaction(tx,ok)

main()
