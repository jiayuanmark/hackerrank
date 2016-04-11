
def load_unigram():
	with open("unigram.txt", "r") as f:
		return f.read()

def load_bigram():
	with open("bigram.txt", "r") as f:
		return f.read()

if __name__ == "__main__":
	with open("MissingApostrophes.py", "r") as source:
		with open("MissingApostrophesSubmission.py", "w") as output:
			for line in source.readlines():
				if line.strip() == "<unigram label>":
					output.write(load_unigram())
				elif line.strip() == "<bigram label>":
					output.write(load_bigram())
				else:
					output.write(line)
