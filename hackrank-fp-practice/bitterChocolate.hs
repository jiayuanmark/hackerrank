import Control.Applicative
import Data.Array

import qualified Data.List as List

play :: Int -> Int -> Int -> String
play r1 r2 r3 = case table ! (r1,r2,r3) of
                  True  -> "WIN"
                  False -> "LOSE"
  where
    bnds         = ((1,0,0),(r1,r2,r3))
    table       :: Array (Int,Int,Int) Bool 
    table        = array bnds [ (ijk, dp ijk) | ijk <- range bnds ]

    status i j k = [ table ! (i,j,k')                | k' <- [0..(k-1)] ]
                ++ [ table ! (i,j', min k j')        | j' <- [0..(j-1)] ]
                ++ [ table ! (i',min j i', min k i') | i' <- [1..(i-1)] ]

    dp (1,0,0) = False
    dp (i,j,k)
      | List.foldl1' (||) $ map not $ status i j k = True
      | otherwise = False

solve :: Int -> IO ()
solve 0 = return ()
solve t = do
  [r1, r2, r3] <- map read . words <$> getLine
  putStrLn $ play r1 r2 r3
  solve $! (t-1)

main :: IO ()
main = do
  t <- read <$> getLine
  solve t