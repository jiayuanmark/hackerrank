import sys


if __name__ == "__main__":
	content1 = open(sys.argv[1], "r").readlines()
	content2 = open(sys.argv[2], "r").readlines()

	assert(len(content1) == len(content2))
	counter = 0
	for idx in range(len(content1)):
		if content1[idx].strip() == content2[idx].strip():
			counter = counter + 1

	print float(counter) / len(content1) 