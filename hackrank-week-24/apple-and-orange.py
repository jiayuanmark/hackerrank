

if __name__ == "__main__":
  s, t = [ int(u) for u in raw_input().split() ]
  a, b = [ int(u) for u in raw_input().split() ]
  m, n = [ int(u) for u in raw_input().split() ]
  av = [ int(u) + a for u in raw_input().split() ]
  bv = [ int(u) + b for b in raw_input().split() ]

  f = lambda x : x >= s && x <= t
  print len(filter(f, av))
  print len(filter(f, bv))