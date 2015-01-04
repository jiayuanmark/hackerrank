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
  forM_ [0..bnd] (dp table 0 0)
  forM_ ns (print table)
  where bnd            = List.foldl1' max ns
        go x y z       = mod (x + mod (y*z) (10^8+7)) (10^8+7)
        -- dynamic programming
        dp arr _ _   0 = writeArray arr 0 1
        dp arr i val n
          | i == n-1   = do n1 <- readArray arr i
                            n2 <- readArray arr (n-1-i)
                            writeArray arr n $ go val n1 n2 
          | otherwise  = do n1 <- readArray arr i
                            n2 <- readArray arr (n-1-i)
                            dp arr (i+1) (go val n1 n2) n
        -- print
        print arr i    = do sol <- readArray arr i
                            putStrLn (show sol) 

main :: IO ()
main = do
  t <- read <$> getLine
  ns <- readqs t []
  solve ns