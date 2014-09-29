import Data.Array

countPath :: Int -> Int -> Int -> Integer
countPath n' m' k'
	| (n' == 1) && (m' == 1) && (k' == 0) = 1
	| otherwise = getSol [0..k'] 0
	where
		getSol ks val | ks `seq` val `seq` False = undefined
		getSol [] val = val
		getSol (k:ks) val = getSol ks $ rem (table!(n',m',k,1) + table!(n',m',k,0) + val) 1000000007

		table = array ((1,1,0,0), (n',m',k',1)) [ (idx, dp idx) | idx <- range((1,1,0,0), (n',m',k',1)) ]
		dp (1,1,_,_) = 0
		dp (_,1,0,0) = 1
		dp (1,_,0,1) = 1
		dp (i,j,k,0)
			| k > 0 && i > 1 = table!(i-1,j,k,0) + table!(i-1,j,k-1,1)
			| i > 1 = table!(i-1,j,k,0)
			| otherwise = 0
		dp (i,j,k,1)
			| k > 0 && j > 1 = table!(i,j-1,k,1) + table!(i,j-1,k-1,0)
			| j > 1 = table!(i,j-1,k,1)
			| otherwise = 0


solve :: Int -> IO ()
solve n
	| n == 0 = return ()
	| otherwise = do
		input <- getLine
		let prob = map read $ words input
		putStrLn $ show $ countPath (prob !! 0) (prob !! 1) (prob !! 2)
		solve (n-1)

main :: IO ()
main = do
	t <- getLine
	solve $ read t
	