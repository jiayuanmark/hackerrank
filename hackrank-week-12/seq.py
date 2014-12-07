
graph = {}
visited = set()

vertex = set()
lst = []

def dfs(u):
	visited.add(u)
	for v in sorted(graph.get(u, set()), reverse=True):
		if v not in visited:
			dfs(v)
	lst.append(u)

if __name__ == "__main__":
	# input
	N = int(raw_input())
	for _ in xrange(N):
		_ = int(raw_input())
		L = [ int(u) for u in raw_input().split() ]
		edge = zip(L[:-1], L[1:])
		for u, v in edge:
			graph.setdefault(u, set()).add(v)
			vertex.add(u)
			vertex.add(v)
	
	# topological sort
	for s in sorted(vertex, reverse=True):
		if s not in visited:
			dfs(s)

	# output
	lst.reverse()
	print ' '.join([ str(u) for u in lst ])