import Control.Applicative
import Data.Array

import qualified Data.List as List

play :: Int -> Int -> Int -> String
play r1 r2 r3 = case table ! (r1,r2,r3,0) of
                  True  -> "WIN"
                  False -> "LOSE"
  where
    bnds            = ((1,0,0,0),(r1,r2,r3,1))
    table          :: Array (Int,Int,Int,Int) Bool 
    table           = array bnds [ (ijkp, dp ijkp) | ijkp <- range bnds ]

    status i j k p  = [ table ! (i,j,k',p)   | k' <- [0..(k-1)] ]
                   ++ [ table ! (i,j',j',p)  | j' <- [0..(j-1)] ]
                   ++ [ table ! (i',i',i',p) | i' <- [1..(i-1)] ]
    -- player 1 (p == 0) v.s. player 2 (p == 1)
    dp (1,0,0,0) = False
    dp (1,0,0,1) = True
    dp (i,j,k,0)
      | List.foldl1' (||) $ status i j k 1 = True
      | otherwise = False
    dp (i,j,k,1)
      | List.foldl1' (||) $ map not $ status i j k 0 = False
      | otherwise = True

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