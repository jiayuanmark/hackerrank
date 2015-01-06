{-# LANGUAGE BangPatterns #-}

import Control.Applicative
import Control.Monad
import Data.Array.Unboxed

import Debug.Trace (trace)

import qualified Data.List as List

bnds :: ((Int,Int),(Int,Int))
bnds = ((0,0),(10,10))

solve :: Int -> [Int] -> IO ()
solve n keys = putStrLn $ show (n + v)
  where
    v           = dp keys arr
    arr         = array bnds [ (ij, int ij) | ij <- range bnds ]
    int t@(i,j)
      | i == 0 || j == 0 = 0
      | otherwise        = 100000 


dp :: [Int] -> (UArray (Int,Int) Int) -> Int
dp []     !arr = List.foldl1' min [ arr ! ij | ij <- range bnds ] 
dp (k:ks) !arr = dp ks $! table
  where
    table    = array bnds [ (ij, fill ij) | ij <- range bnds ]
    rk       = if k == 0 then 10 else k
    diff x y = abs (x - y)
    fill t@(i,j)
      | i == rk = List.foldl' min (arr!(0,j)) [ arr!(l,j) + diff rk l | l <- [1..10] ] 
      | j == rk = List.foldl' min (arr!(i,0)) [ arr!(i,l) + diff rk l | l <- [1..10] ]
      | otherwise = 100000


main :: IO ()
main = do
  n <- read <$> getLine
  keys <- map read . words <$> getLine
  solve n keys