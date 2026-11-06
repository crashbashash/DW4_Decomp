"""Review the two parent-publication callback leaves used by list registrars."""
from ghidra.program.model.address import AddressSet
from ghidra.program.model.symbol import SourceType
ROWS=((0x143720,0x8c226788,0x2cabe4,0x24e73720),(0x130c00,0x8c225b60,0x36a1e8,0x24e70c00))
def main():
    space=currentProgram.getAddressFactory().getDefaultAddressSpace();memory=currentProgram.getMemory();manager=currentProgram.getFunctionManager()
    def word(va):return int(memory.getInt(space.getAddress(va)))&0xffffffff
    tx=currentProgram.startTransaction('Reviewed list parent callback leaves');ok=False
    try:
        for va,load,site,literal in ROWS:
            if tuple(word(va+i*4) for i in range(3))!=(0x3c010058,0x03e00008,load) or word(site)!=literal:raise ValueError('unexpected callback %#x'%va)
            start=space.getAddress(va);end=space.getAddress(va+11);existing=manager.getFunctionAt(start)
            if existing:
                body=existing.getBody()
                if int(body.getNumAddresses())!=12 or int(body.getMinAddress().getOffset())!=va or int(body.getMaxAddress().getOffset())!=va+11:raise ValueError('existing extent differs')
                continue
            for i in range(12):
                if manager.getFunctionContaining(space.getAddress(va+i)) is not None:raise ValueError('overlap')
            if manager.createFunction('FUN_%08x'%va,start,AddressSet(start,end),SourceType.USER_DEFINED) is None:raise ValueError('create failed')
            print('created reviewed list parent callback %#x /12 bytes'%va)
        ok=True
    finally:currentProgram.endTransaction(tx,ok)
main()
