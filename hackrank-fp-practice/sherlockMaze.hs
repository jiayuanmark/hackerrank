import Control.Applicative
import Control.Monad
import Data.Array.IO

import qualified Data.List as List

countPath :: Int -> Int -> Int -> IO Int
countPath 1 1 0 = return 1
countPath n m k = do
  let bnds = ((1,1,0,0), (n,m,k,1))
  table <- newArray bnds 0 :: IO (IOUArray (Int,Int,Int,Int) Int)
  forM_ (range bnds) (dp table)
  foldM (f table) 0 [ (n,m,s,t) | s <- [0..k], t <- [0,1] ]
  where
    go x y     = (x + y) `mod` (10^9 + 7)
    f  arr v t = do v' <- readArray arr t
                    return $ go v v'

    -- dynamic programming
    dp arr t@(1,1,_,_) = writeArray arr t 0
    dp arr t@(_,1,0,0) = writeArray arr t 1
    dp arr t@(1,_,0,1) = writeArray arr t 1

    dp arr t@(i,j,l,0)
      | l > 0 && i > 1 = do n1 <- readArray arr (i-1,j,l,0)
                            n2 <- readArray arr (i-1,j,l-1,1)
                            writeArray arr t $ go n1 n2
      | i > 1          = readArray arr (i-1,j,l,0) >>= writeArray arr t
      | otherwise      = writeArray arr t 0

    dp arr t@(i,j,l,1)
      | l > 0 && j > 1 = do n1 <- readArray arr (i,j-1,l,1)
                            n2 <- readArray arr (i,j-1,l-1,0)
                            writeArray arr t $ go n1 n2
      | j > 1          = readArray arr (i,j-1,l,1) >>= writeArray arr t
      | otherwise      = writeArray arr t 0


solve :: Int -> IO ()
solve t
  | t == 0 = return ()
  | otherwise = do
    [n, m, k] <- map read . words <$> getLine
    sol <- countPath n m k
    putStrLn $ show sol
    solve $! t-1

main :: IO ()
main = do
  t <- read <$> getLine
  solve t
