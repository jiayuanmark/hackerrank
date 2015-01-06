{-# LANGUAGE BangPatterns #-}

import Control.Applicative
import Control.Monad
import Data.Array

import Debug.Trace (trace)

import qualified Data.List as List

solve :: Int -> [Int] -> IO ()
solve n a = print
  where
    table     :: Array Int (Int,Int)
    table      = array (1,n) [ (i, dp i) | i <- [1..n] ]

    cond  i x  = (i `mod` x == 0) && (fst (table ! (i`div`x)) /= -1)
    score i    = [ (1 + fst (table ! (i`div`x)), (i`div`x)) | x <- filter (cond i) a ]

    -- dynamic programming
    dp i       | trace ("calculate: " ++ show i) False = undefined
    dp 1       = (1,-1)
    dp i       = let sub = score i
                 in case (List.null sub) of
                      True  -> (-1,-1)
                      False -> List.foldl1' min sub
    -- print
    print      = let (v,p) = table ! n
                 in case v of
                      -1 -> putStrLn "-1"
                      _  -> backtrack p [n]
    -- backtrack
    backtrack i arr 
      | i == -1   = putStrLn $ List.intercalate " " (map show arr)
      | otherwise = backtrack (snd (table ! i)) (i:arr)


main :: IO ()
main = do
  [n, _] <- map read . words <$> getLine
  a      <- map read . words <$> getLine
  solve n a