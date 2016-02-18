{-# LANGUAGE BangPatterns #-}

import Control.Applicative
import Control.Monad
import Data.Array.Unboxed

type Query = [(Int,Int)]

solve :: IO ()
solve = do
  [m, n] <- map read . words <$> getLine
  query  <- forM [1..n] $ \_ -> do
    [x, y] <- map read . words <$> getLine
    return (x, y)
  putStrLn . show $ calc m query

calc :: Int -> Query -> Int
calc _ []         = 0
calc m ((a,b):qs) = calc' edge qs
  where
    inf  = 2 * (10 ^ 6) :: Int
    bnds = ((1,1),(m,m))
    edge :: UArray (Int, Int) Int
    edge = array bnds [ (ij, fill ij) | ij <- range bnds ]
      where fill (x,y)
              | x == b || y == b = abs (a - b)
              | otherwise        = inf
    calc' :: UArray (Int,Int) Int -> Query -> Int
    calc' !arr []        = minimum [ arr ! ij | ij <- range bnds ]
    calc' !arr ((x,y):q) = calc' arr' q
      where arr' = array bnds [ (ij, dp ij) | ij <- range bnds ]
            val  = abs (x - y)
            dp (u,v)
              | u == y    = minimum [ abs (x - u') + val + arr ! (u',v)
                                      | u' <- [1..m] ]
              | v == y    = minimum [ abs (x - v') + val + arr ! (u,v')
                                      | v' <- [1..m] ]
              | otherwise = inf

main :: IO ()
main = do
  t <- read <$> getLine
  forM_ [1..t] (const solve)
