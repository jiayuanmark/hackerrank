if __name__ == "__main__":
    T = int(raw_input())
    
    for t in range(T):
        N = int(raw_input())
        
        X, Y = -1, -1
        for x in xrange(N/3+1, -1, -1):
            for y in xrange((N-3*x)/5+1, -1, -1):
                if 3 * x + 5 * y == N:
                    X, Y = x, y
                    break
            if X != -1 and Y != -1:
                break 

        if X == -1 or Y == -1:
            print -1
        else:
            print "5" * (3*X) + "3" * (5*Y) 