#/usr/bin/python

import math
from pylab import *

#Given a requested pad spacing and number of pads, it makes 2 rows in a circle
#equalspace determines interior row spacing from equidistant from outer row pads
#or spacing as a simple distance from radius
#changing sizing will mess with the marker size sadly (wtf)...
equalspace = 1
spacing = 100
pads = 30
pad_size = 200

#adjust for marker/pad size
spacing = spacing + pad_size

if pads > 12:
  row1 = pads/2
  row2 = pads/2
else:
  row1 = pads
  row2 = 0


space = 2.0*math.pi/row1
circ1 = (spacing)*row1
#radius = circ1/(2.0*math.pi)
#make radius by pad spacing calc, not arc division
radius = math.sqrt(math.pow(spacing, 2.0)/((1-math.cos(space))*2))

#solve for interior pad based on half space in radius and space deep
if equalspace:
  radius2 = radius+math.sqrt((math.pow(spacing, 2.0)-math.pow(spacing/2.0,2.0)))
else:
  radius2 = radius+spacing

print "spacing %f" % spacing
print "radius %f" % radius
print "radius2 %f" % radius2

a = 0
b = 0
angle = 0
pad = 1
print "Total number of pads %d, row 1 %d, row 2 %d." %(pads, row1, row2)


for x in range(0, row1):
  a = radius*math.cos(x*space)
  b = radius*math.sin(x*space)
  plot(a,b, 'bo', markersize=pad_size/6)
  #simple rads to deg converter
  angle = (57.2957795*x*space)
  print "Pad %d: %f, %f, %f" % (pad, a,b, angle)

  if pad == pads:
    continue
  pad = pad + 1

  if row2 != 0:
    a = radius2*math.cos(x*space+(space/2.0))
    b = radius2*math.sin(x*space+(space/2.0))
    plot(a,b, 'bo', markersize=pad_size/6)
    angle = (57.2957795*(x*space+(space/2.0)))
    print "Pad %d: %f, %f, %f" % (pad, a,b, angle)
    pad = pad + 1

show()
