#!/usr/bin/python

import sys, os
from PIL import Image


def con(inf, of):
   print(inf, "->", of)
   im = Image.open(inf)
   if im.mode == "RGB":
       pixelSize = 3
   elif im.mode == "RGBA":
       pixelSize = 4
   else:
     print ('not supported pixel mode: "%s"' % (im.mode))
     return

   pixels = im.tostring()
   pixels2 = ""
   pixels3 = []
   for i in range(0, len(pixels) - 1, pixelSize):
       pixels2 += chr(ord(pixels[i + 2]) >> 3 | (ord(pixels[i + 1]) << 3 & 0xe0))
       pixels2 += chr(ord(pixels[i]) & 0xf8 | (ord(pixels[i + 1]) >> 5 & 0x07))
       pixels3.append( ((ord(pixels[i+2])>>3)<<11) | ((ord(pixels[i+1])>>2)<<5) | (ord(pixels[i])>>3))
   with open(of, "a") as out:
      print os.path.basename(of).split('.')[0]
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
    if im.mode == "RGB":
      pixelSize = 3
    elif im.mode == "RGBA":
      pixelSize = 4
    else:
      print ('not supported pixel mode: "%s" in file %s' % (im.mode, f))
      continue
    pixels = im.tostring()
    pixels2 = ""
    for i in range(0, len(pixels) - 1, pixelSize):
      pixels2 += chr(ord(pixels[i + 2]) >> 3 | (ord(pixels[i + 1]) << 3 & 0xe0))
      pixels2 += chr(ord(pixels[i]) & 0xf8 | (ord(pixels[i + 1]) >> 5 & 0x07))
      pixels3 = ((ord(pixels[i])>>3)<<11) | ((ord(pixels[i+1])>>2)<<5) | (ord(pixels[i+2])>>3)
      colors.add(pixels3)
  return colors

def condense(files, outfile, colors):
  with open(outfile, 'wb') as out:
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
      if im.mode == "RGB":
        pixelSize = 3
      elif im.mode == "RGBA":
        pixelSize = 4
      else:
        print ('not supported pixel mode: "%s" in file %s' % (im.mode, f))
        continue
      print ('Adding %s'%f)
      pixels = im.tostring()
      pixels2 = ""
      ss=""
      for i in range(0, len(pixels) - 1, pixelSize):
        pixels2 += chr(ord(pixels[i + 2]) >> 3 | (ord(pixels[i + 1]) << 3 & 0xe0))
        pixels2 += chr(ord(pixels[i]) & 0xf8 | (ord(pixels[i + 1]) >> 5 & 0x07))
        pixels3 = ((ord(pixels[i])>>3)<<11) | ((ord(pixels[i+1])>>2)<<5) | (ord(pixels[i+2])>>3)
        ss += hex(pallet[pixels3])[-1]
      ss = ss.decode('hex')
      s2 = [ord(x) for x in ss]
      out.write("const uint8_t %s_raw[] = {"%(os.path.basename(f).split('.')[0]))
      for i in range(len(s2)):
        if (i%16)==0:
          out.write("\n\t")
        out.write("0x%02X, "%(s2[i]))
      out.write("\n\t};\n\n")


colors = getPallet(sys.argv[1:])
print "Pallet has %d colors"%(len(colors))
condense(sys.argv[1:], 'metroid.h', colors)


