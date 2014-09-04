import numpy as np
from scipy.fftpack import dct
import scipy.ndimage

model = {
"7": "1000000010000000100000001000000010000000100000001000000010000000",
"3": "1010101010101010101010101010101010101010101010101010101010101000",
"1": "1000000010000000101000001010000010100000101000001010000010100000",
"5": "1000000010000000100000001000000010000000100000001000000010000000"
}


def loadImage():
	R, C = [ int(u) for u in raw_input().split() ]
	img = np.zeros((R, C))
	for r in range(R):
		row = raw_input().split()
		for c in range(C):
			R, G, B = [ int(u) for u in row[c].split(",") ]
			img[r, c] = round(0.2989 * R + 0.5870 * G + 0.1140 * B)
	return img

def genHash(dctimg):
	dctimg = dctimg[0:8, 0:8]
	avg = np.mean(dctimg)
	hsh = [ "1" if dctimg[i,j] >= avg else "0" for i in xrange(8) for j in xrange(8) ]
	return "".join(hsh)

def compareHash(h1, h2):
	dst = 0
	for s1, s2 in zip(h1, h2):
		if s1 != s2:
			dst += 1
	return dst

def solve(hsh):
	nearDst, ans = 65, "0";
	for k, v in model.iteritems():
		if compareHash(v, hsh) <= nearDst:
			nearDst = compareHash(v, hsh)
			ans = k
	return k


if __name__ == "__main__":
	img = scipy.ndimage.filters.gaussian_filter(loadImage(), sigma=3)
	img = scipy.ndimage.zoom(img, zoom=0.25)
	print img
	dctimg = dct(img)
	print solve(genHash(dctimg))


