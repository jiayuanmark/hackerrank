{-# LANGUAGE BangPatterns #-}

import Control.Applicative
import qualified Data.List as L

data Dice = Dice { top   :: Int
                 , front :: Int
                 , right :: Int
                 } deriving (Show, Eq)

rotateRight :: Dice -> Dice
rotateRight (Dice t f r) = Dice { top   = 7 - r
                                , front = f
                                , right = t
                                }

rotateDown :: Dice -> Dice
rotateDown (Dice t f r) = Dice { top   = 7 - f
                               , front = t
                               , right = r
                               }


maxSumPath :: Int -> Int -> Dice -> Int
maxSumPath 1 1 !dice = top dice
maxSumPath !m !n !dice
  | m == 1    = top dice + rpath
  | n == 1    = top dice + dpath
  | otherwise = top dice + max rpath dpath
  where
    rpath = maxSumPath m (n-1) (rotateRight dice)
    dpath = maxSumPath (m-1) n (rotateDown dice)

solve :: Int -> IO ()
solve 0 = return ()
solve t = do
  [m, n] <- map read . words <$> getLine
  putStrLn $ show $ maxSumPath m n (Dice 1 2 4)
  solve $! (t-1)

main :: IO ()
main = do
  t <- read <$> getLine
  solve t
