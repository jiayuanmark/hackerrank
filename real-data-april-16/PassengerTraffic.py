from sklearn import linear_model

def mean(x):
  if len(x) == 0:
    return 0.0
  return sum(x) / len(x)

def dotprod(x, y):
	return sum([ a * b for (a, b) in zip(x,y) ])   

feat_size = 2

if __name__ == "__main__":
  n = int(raw_input())

  month_data = [ [] for _ in range(12) ]
  all_data = []
  for i in xrange(n):
    val = int(raw_input().split()[1])
    month_data[i % 12].append(val)
    all_data.append(val)

  train = []
  label = []

  for i in xrange(1, n):
  	train.append([ mean(month_data[i % 12]), all_data[i-1] ])
  	label.append(all_data[i])

  clf = linear_model.LinearRegression()
  clf.fit(train, label)
  
  for i in range(n, n+12):
  	val = round(clf.intercept_ + dotprod(clf.coef_, [ mean(month_data[i % 12]), all_data[i-1] ] ))
  	print val
  	all_data.append(val)
