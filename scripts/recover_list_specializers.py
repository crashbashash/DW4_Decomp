"""Recover reviewed native list field-adder callbacks without reanalysis.

Registrar literal/stack arguments and the complete contiguous prologue/epilogue
prove two 192-byte callback bodies in previously unclaimed gaps. Refuse overlap.
"""
from ghidra.program.model.address import AddressSet
from ghidra.program.model.symbol import SourceType
ROWS=((0x2bd830,0x2bd7c8,0x2442d830,0x585b60),(0x2cac20,0x2cabb8,0x2442ac20,0x586880))
def main():
    space=currentProgram.getAddressFactory().getDefaultAddressSpace();memory=currentProgram.getMemory();manager=currentProgram.getFunctionManager()
    def word(va):return int(memory.getInt(space.getAddress(va)))&0xffffffff
    tx=currentProgram.startTransaction('Reviewed list field specializers');ok=False
    try:
        for va,site,literal,handle in ROWS:
            expected={site:literal,site+8:0xffa20000,va:0x27bdffc0,va+0x0c:0x3c010058,va+0x20:0x8c310000|(handle&0xffff),va+0x24:0x0c0bf7c8,va+0x78:0x0c0bf7a8,va+184:0x03e00008,va+188:0x27bd0040}
            for address,value in expected.items():
                if word(address)!=value:raise ValueError('unexpected instruction at %#x'%address)
            start=space.getAddress(va);end=space.getAddress(va+191);existing=manager.getFunctionAt(start)
            if existing:
                body=existing.getBody()
                if int(body.getNumAddresses())!=192 or int(body.getMinAddress().getOffset())!=va or int(body.getMaxAddress().getOffset())!=va+191:raise ValueError('existing span differs')
                continue
            for i in range(192):
                if manager.getFunctionContaining(space.getAddress(va+i)) is not None:raise ValueError('overlap at %#x'%va)
            if manager.createFunction('FUN_%08x'%va,start,AddressSet(start,end),SourceType.USER_DEFINED) is None:raise ValueError('create failed')
            print('created reviewed list specializer %#x / 192 bytes'%va)
        ok=True
    finally:currentProgram.endTransaction(tx,ok)
main()
