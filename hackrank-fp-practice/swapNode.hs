import Control.Applicative
import Control.Monad
import Data.Array
import qualified Data.List as L

data Tree = Null | Branch Int Tree Tree
            deriving Eq

instance Show Tree where
  show Null                 = ""
  show (Branch v Null Null) = show v
  show (Branch v Null r)    = (show v) ++ " " ++ (show r)
  show (Branch v l Null)    = (show l) ++ " " ++ (show v)
  show (Branch v l r)       = L.intercalate " " [show l, show v, show r]

type TreeArray = Array Int (Int,Int)
type Depth     = Int

buildTree :: TreeArray -> Int -> Tree
buildTree _ (-1) = Null
buildTree arr i  = Branch i (buildTree arr l) (buildTree arr r)
  where (l,r) = arr ! i

swapTree :: Tree -> Depth -> Int -> Tree
swapTree Null _ _  = Null
swapTree (Branch v l r) d k
  | d `mod` k == 0 = Branch v nr nl  
  | otherwise      = Branch v nl nr
  where
    nl = swapTree l (d+1) k
    nr = swapTree r (d+1) k

readTree :: IO TreeArray
readTree = do
  n   <- read <$> getLine
  lst <- forM [1..n] $ \_ -> do
    [x,y] <- map read . words <$> getLine
    return (x,y)
  return $ array (1,n) (zip [1..n] lst)

solve :: Tree -> Int -> IO ()
solve _ 0    = return ()
solve tree t = do
  k <- read <$> getLine
  let newtree = swapTree tree 1 k
  putStrLn $ show newtree
  solve newtree $! (t-1)

main :: IO ()
main = do
  arr <- readTree
  t   <- read <$> getLine
  let tree = buildTree arr 1
  solve tree t

