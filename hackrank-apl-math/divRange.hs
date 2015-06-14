import Control.Applicative
import qualified Data.List as L

data Tree = Branch { range :: (Int, Int)
                   , val   :: Integer
                   , left  :: Tree
                   , right :: Tree 
                   }
          | Leaf   { range :: (Int, Int)
                   , val   :: Integer
                   } deriving (Show, Eq)

split :: (Int, Int) -> Int
split (l,r) = div (l+r) 2

buildTree :: [Integer] -> (Int, Int) -> Tree
buildTree arr rg@(l,r)
  | l == r    = Leaf (l,l) $ head arr
  | otherwise = Branch { range = (l,r)
                       , val   = gcd (val lhs) (val rhs)
                       , left  = lhs
                       , right = rhs
                       }
   where
     mid          = split rg
     (larr, rarr) = L.splitAt (mid-l+1) arr
     lhs          = buildTree larr (l, mid)
     rhs          = buildTree rarr (mid+1, r)

queryTree :: Tree -> Integer -> Int
queryTree (Leaf _ v) k = if v `mod` k == 0 then 1 else 0 
queryTree (Branch rg@(l,r) v lhs rhs) k
  | (v `mod` k) == 0 = ((r-l+1) * (r-l+2)) `div` 2
  | otherwise        = (queryTree lhs k) + (queryTree rhs k) + (lv * rv)
  where
    lv = query lhs k True
    rv = query rhs k False

query :: Tree -> Integer -> Bool -> Int
query (Leaf _ v) k _ = if v `mod` k == 0 then 1 else 0
query (Branch rg@(l,r) v lhs rhs) k right
  | (v `mod` k) == 0 = (r-l+1)
  | right            = query rhs k right
  | otherwise        = query lhs k right

solve :: Int -> Tree -> IO ()
solve 0 _    = return ()
solve n tree = do
  k <- read <$> getLine
  putStrLn . show $ queryTree tree k
  solve (n-1) tree

main :: IO ()
main = do
  n <- read <$> getLine
  c <- map read . words <$> getLine
  q <- read <$> getLine
  solve q $ buildTree c (0, n-1)


