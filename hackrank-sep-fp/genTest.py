import random

if __name__ == "__main__":
	n = 5000
	f = file("input2", "w")
	f.write(str(n) + "\n")
	f.write(" ".join([ str(random.randint(0,9)) for _ in xrange(n) ]) + "\n")
	f.close()
