#/usr/bin/python

import math
#8x8,16,23,31
r = 31
d = 8

circ = 2*r*math.pi
number = int(math.floor(circ/d+.25))
space = 2.0*math.pi/number

a = 0
b = 0
angle = 0

print "LED number %d" % number

for x in range(0, number):
  a = r*math.cos(x*space)
  b = r*math.sin(x*space)
  angle = (57.2957795*x*space)
  print "%f, %f, %f" % (a,b, angle)
