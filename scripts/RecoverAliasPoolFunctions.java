/* Reviewed missing igAliasMemoryPool methods.
 * Run on the existing analyzed project with -noanalysis, then regenerate its
 * functions dump using dump_functions.py. No game bytes are changed.
 * Extents were checked against retail objdump including return delay slots.
 */
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.symbol.SourceType;

public class RecoverAliasPoolFunctions extends GhidraScript {
    public void run() throws Exception {
        // Entry, exclusive end, raw vtable5313a0 byte offset, first instruction.
        long[][] rows = {
            {0x2d0ae0,0x2d0b00,220,0x8c990000L},
            {0x2d0b00,0x2d0b68,224,0x27bdffd0L},
            {0x2d0c00,0x2d0c10,236,0x8c990000L},
            {0x2d0c10,0x2d0ccc,260,0x27bdffb0L},
            {0x2d0d80,0x2d0d98,264,0x8c990000L},
            {0x2d0da0,0x2d0e2c,340,0x27bdffc0L},
            {0x2d0e30,0x2d0e44,336,0x8c8400b4L},
            {0x2d0e50,0x2d1018,348,0x27bdff20L}
        };
        var manager=currentProgram.getFunctionManager();
        for(long[] row:rows) {
            var start=toAddr(row[0]);
            if(Integer.toUnsignedLong(getInt(toAddr(0x5313a0+row[2])))!=row[0]
               || Integer.toUnsignedLong(getInt(start))!=row[3])
                throw new IllegalStateException("retail evidence differs at "+start);
            var body=new AddressSet(start,toAddr(row[1]-1));
            var existing=manager.getFunctionAt(start);
            if(existing!=null) {
                if(!existing.getBody().equals(body))
                    throw new IllegalStateException("existing body differs at "+start);
                continue;
            }
            for(long p=row[0];p<row[1];p+=4)
                if(manager.getFunctionContaining(toAddr(p))!=null)
                    throw new IllegalStateException("function overlaps at "+toAddr(p));
            if(!disassemble(start))throw new IllegalStateException("disassembly failed at "+start);
            manager.createFunction(String.format("FUN_%08x",row[0]),start,body,SourceType.ANALYSIS);
            println("Classified alias method "+start+".."+toAddr(row[1]));
        }
    }
}
