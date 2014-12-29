import Control.Applicative
import qualified Data.List as L

data Tree = Branch { range :: (Int, Int)
				   , val   :: Integer
				   , left  :: Tree
				   , right :: Tree 
				   }
		  | Leaf   { range :: (Int, Int)
		  		   , val   :: Integer
				   }
		  deriving (Show, Eq)

split :: (Int, Int) -> Int
split (l,r) = div (l+r) 2

buildTree :: [Integer] -> (Int, Int) -> Tree
buildTree arr rg@(l,r)
	 | l == r    = Leaf (l,l) $ head arr
	 | otherwise = Branch { range = (l,r)
	 					  , val   = lcm (val leftTree) (val rightTree)
						  , left  = leftTree
						  , right = rightTree
						  } 
	 where
		 mid = split rg
		 (larr, rarr) = L.splitAt (mid-l+1) arr
		 leftTree = buildTree larr (l, mid)
		 rightTree = buildTree rarr (mid+1, r)

queryTree :: Tree -> (Int,Int) -> Integer
queryTree (Leaf _ mul) _ = mul
queryTree (Branch rng mul l r) q@(ql,qr) 
	| rng == q = mul
	| ql > mid   = queryTree r q
	| qr <= mid  = queryTree l q
	| otherwise  = lcm lft rht
	where
		mid = split rng
		lft = queryTree l (ql, mid)
		rht = queryTree r (mid+1, qr)

updateTree :: Tree -> (Int,Integer) -> Tree
updateTree (Leaf rng val) (_,m) = Leaf rng $ val * m
updateTree (Branch rng mul l r) q@(id,_)
	| id <= mid = Branch { range = rng
						 , val = lcm (val newl) (val r)
						 , left = newl
						 , right = r
						 } 
	| otherwise = Branch { range = rng
						 , val = lcm (val l) (val newr)
						 , left = l
						 , right = newr
						}
	where
		mid = split rng
		newl = updateTree l q
		newr = updateTree r q 

solve :: Int -> Tree -> IO()
solve 0 _ = return ()
solve i tree = do
	[t, v1, v2] <- words <$> getLine
	case t of
		"Q" -> do
			putStrLn . show $ mod (queryTree tree (read v1, read v2)) (10^9+7)
			solve (i-1) tree
		"U" -> do
			solve (i-1) $ updateTree tree (read v1, read v2)

main :: IO ()
main = do
	n <- read <$> getLine
	arr <- map read . words <$> getLine
	k <- read <$> getLine
	solve k $ buildTree arr (0, n-1)
