#!/usr/bin/python

import sys, os
from PIL import Image


def con(inf, of):
   print(inf, "->", of)
   im = Image.open(inf)
   pixels = im.getdata()
   pixels3 = []
   for i in range(0, len(pixels) - 1):
       pixels3.append( ((ord(pixels[i+2])>>3)<<11) | ((ord(pixels[i+1])>>2)<<5) | (ord(pixels[i])>>3))
   with open(of, "a") as out:
      print (os.path.basename(of).split('.')[0])
      out.write("const uint16_t %s_raw[] = {"%(os.path.basename(inf).split('.')[0]))
      for i in range(len(pixels3)):
        if (i%16)==0:
          out.write("\n\t")
        out.write("0x%04X, "%(pixels3[i]))
      out.write("\n\t};\n\n")

def getPallet(files):
  colors = set()
  for f in files:
    im = Image.open(f)
    pixels = im.getdata()
    for i in range(0, len(pixels) - 1):
      pixels3 = ((pixels[i][0]>>3)<<11)| ((pixels[i][1]>>2)<<5) | (pixels[i][2]>>3)
      colors.add(pixels3)
  return colors

def condense(files, outfile, colors):
  with open(outfile, 'w') as out:
    out.write("const uint16_t pallet[] = { ")      
    pallet = {}
    i=0
    for c in colors:
      pallet[c]=i
      i+=1
      out.write("0x%04X, "%(c))
    out.write("};\n\n")
    for f in files:
      im = Image.open(f)
      print ('Adding %s'%f)
      pixels = im.getdata()
      s2 = []
      for i in range(0, len(pixels) - 1):
        pixels3 = ((pixels[i][0]>>3)<<11)| ((pixels[i][1]>>2)<<5) | (pixels[i][2]>>3)
        s2.append(pallet[pixels3])
      out.write("const uint8_t %s_raw[] = {"%(os.path.basename(f).split('.')[0]))
      for i in range(len(s2)):
        if (i%16)==0:
          out.write("\n\t")
        out.write("0x%02X, "%(s2[i]))
      out.write("\n\t};\n\n")


colors = getPallet(sys.argv[1:])
print ("Pallet has %d colors"%(len(colors)))
condense(sys.argv[1:], 'doom.h', colors)


