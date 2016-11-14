#!/bin/python

if __name__ == "__main__":
  s, t = [ int(u) for u in raw_input().split() ]
  a, b = [ int(u) for u in raw_input().split() ]
  m, n = [ int(u) for u in raw_input().split() ]
  av = [ a + int(u) for u in raw_input().split() ]
  bv = [ b + int(u) for u in raw_input().split() ]

  f = lambda x : x >= s and x <= t
  print len(filter(f, av))
  print len(filter(f, bv))
