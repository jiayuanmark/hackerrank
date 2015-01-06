{-# LANGUAGE BangPatterns #-}

import Control.Applicative
import Control.Monad
import Data.Array.IO
import qualified Data.List as List

readqs :: Int -> [Int] -> IO [Int]
readqs 0 !ns = return ns
readqs t !ns = do
  n <- read <$> getLine
  readqs (t-1) (ns ++ [n])

solve :: [Int] -> IO ()
solve ns = do
  table <- newArray (0, bnd) 0 :: IO (IOUArray Int Int)
  forM_ [1..bnd] (dp table)
  forM_ ns (print table)
  where bnd          = List.foldl1' max ns
        go x y       = (x + y) `mod` (10^8+7)
        -- dynamic programming
        dp arr 1     = writeArray arr 1 1 
        dp arr i     = do n1 <- readArray arr (i-1)
                          n2 <- readArray arr (i-2)
                          writeArray arr i $ go n1 n2 
        -- print
        print arr i  = do sol <- readArray arr i
                          putStrLn (show sol) 

main :: IO ()
main = do
  t <- read <$> getLine
  ns <- readqs t []
  solve ns