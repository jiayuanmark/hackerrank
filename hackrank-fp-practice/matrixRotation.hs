import Control.Applicative
import Control.Monad
import Data.Array
import qualified Data.List as L

import Debug.Trace (trace)

type Matrix = Array (Int,Int) Int
type Rect   = (Int, Int, Int, Int)

peel :: Matrix -> Rect -> [[Int]]
peel mx (u,b,l,r)
  | ((l > r) || (u > b)) = []
  | otherwise            = lv : (peel mx $! (u+1,b-1,l+1,r-1))  
  where
    lv     = left ++ bottom ++ right ++ upper
    left   = [ mx ! (i,l) | i <- [u..b] ]
    bottom = [ mx ! (b,i) | i <- [(l+1)..r] ]
    right  = [ mx ! (i,r) | i <- [(b-1),(b-2)..u] ]
    upper  = [ mx ! (u,i) | i <- [(r-1),(r-2)..(l+1)] ]

unpeel' :: [[Int]] -> Rect -> [ ((Int,Int),Int) ] 
unpeel' [] _             = []
unpeel' (i:is) (u,b,l,r) = (zip idx i) ++ (unpeel' is (u+1,b-1,l+1,r-1)) 
  where
    idx    = left ++ bottom ++ right ++ upper
    left   = [ (i,l) | i <- [u..b] ]
    bottom = [ (b,i) | i <- [(l+1)..r] ]
    right  = [ (i,r) | i <- [(b-1),(b-2)..u] ]
    upper  = [ (u,i) | i <- [(r-1),(r-2)..(l+1)] ]

unpeel :: [[Int]] -> Rect -> Matrix
unpeel i (u,b,l,r) = array bnds (unpeel' i (u,b,l,r))
  where bnds = ((u,l),(b,r))

rotate :: Int -> [[Int]] -> [[Int]]
rotate s = map go
  where
    go l =  let len    = length l
                p      = len - (s `mod` len)
                (x,y)  = L.splitAt p l
            in y ++ x

readMatrix :: Int -> Int -> IO Matrix
readMatrix m n = do
  mx <- foldM readRow [] [1..m] 
  return $ array bnds (zip (range bnds) mx)
  where
    bnds        = ((1,1),(m,n))
    readRow l _ = do
      ls <- map read . words <$> getLine
      return (l ++ ls)

printMatrix :: Int -> Int -> Matrix -> IO ()
printMatrix m n mx = forM_ [1..m] $ \r -> do
  putStrLn . unwords $ map (\c -> show (mx ! (r,c))) [1..n]

main :: IO ()
main = do
  [m, n, r] <- map read . words <$> getLine
  mx        <- readMatrix m n
  let rect = (1,m,1,n)
  let lst  = rotate r $ peel mx rect
  printMatrix m n $ unpeel lst rect


