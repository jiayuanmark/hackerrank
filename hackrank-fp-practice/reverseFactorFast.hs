{-# LANGUAGE BangPatterns #-}

import Control.Applicative
import Control.Monad
import Data.Array
import qualified Data.List as L
import qualified Data.Map.Strict as M

import Debug.Trace (trace)

type Path   = M.Map Int Int
type Queue  = [Int]
type Buffer = [Int]

solve :: Int -> [Int] -> Queue -> Path -> Path
solve _ _ [] !p = p
solve !n !mu !q !p
  | n `M.member` p      = p
  | M.null front        = M.empty
  | n `M.member` front  = M.insert n (M.findWithDefault (-1) n front) p
  | otherwise           = solve n mu nq np
  where
    go x   = filter ((n >=) . fst) $ map (\y -> (x*y, x)) mu
    front  = M.fromListWith min (q >>= go)
    nq     = M.keys (M.difference front p)
    np     = M.union p $ front

backTrack :: Path -> Int -> Buffer -> IO ()
backTrack _ (-1) b  = putStrLn $ unwords (map show b)
backTrack p u !b =
  case M.lookup u p of
    Just  v   -> backTrack p v (u:b)
    Nothing   -> putStrLn "-1"

main :: IO ()
main = do
  [n, _] <- map read . words <$> getLine
  as     <- map read . words <$> getLine
  let mult = L.sort (L.nub as)
  let path = solve n mult [1] $ M.singleton 1 (-1)
  backTrack path n []