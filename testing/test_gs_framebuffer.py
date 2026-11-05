#!/usr/bin/env python3
"""PSMCT32 framebuffer words against GS block/column address tables."""
import sys
from pathlib import Path
import numpy as np
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
from gs_shade_raster import frame_pixels

# Factual block and column maps from PCSX2's GS/GSTables.cpp. Keeping the
# column table independent of the decoder's bit expression catches row-major
# inner words and swapped X/Y bits, including interior pixels, not only x=y=0.
blocks=((0,1,4,5,16,17,20,21),(2,3,6,7,18,19,22,23),
        (8,9,12,13,24,25,28,29),(10,11,14,15,26,27,30,31))
columns=((0,1,4,5,8,9,12,13),(2,3,6,7,10,11,14,15),
         (16,17,20,21,24,25,28,29),(18,19,22,23,26,27,30,31),
         (32,33,36,37,40,41,44,45),(34,35,38,39,42,43,46,47),
         (48,49,52,53,56,57,60,61),(50,51,54,55,58,59,62,63))
words=np.arange(1024*1024,dtype='<u4')
points=[(x,y) for y in range(32) for x in range(64)]
points += [(64,0),(127,31),(0,32),(639,447),(128,64),(256,128)]
count=0
for fbp in (0,140):
    frame=frame_pixels(words.tobytes(),fbp,10)
    for x,y in points:
        address=(fbp+(y//32)*10+x//64)*2048+blocks[(y%32)//8][(x%64)//8]*64+columns[y%8][x%8]
        assert list(frame[y,x])==[address&255,(address>>8)&255,(address>>16)&255]
        count+=1
print(f'GS framebuffer: {count} primary-table pixel addresses pass, including every interior word, page boundaries and both buffer bases')
