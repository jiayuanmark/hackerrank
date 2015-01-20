{-# LANGUAGE BangPatterns #-}

import Control.Applicative
import Control.Monad
import Data.Array.IO
import qualified Data.ByteString.Char8 as C 
import qualified Data.List as L
import qualified Data.Set as S

import Debug.Trace (trace)

type Dict  = S.Set C.ByteString
type Table = IOUArray (Int,Int) Bool

-- substring between i and j
substr :: Int -> Int -> C.ByteString -> C.ByteString
substr i j = C.drop (i-1) . (C.take j)

crack :: Dict -> C.ByteString -> Int -> IO Table
crack dict pwd !ln = do
  arr <- newArray bnds False :: IO Table
  forM_ [ (i,i+l) | l <- [0..(n-1)], i <- [1..n], i+l <= n ] (dp arr)
  return arr
  where
    match i j  = (substr i j pwd) `S.member` dict

    n          = C.length pwd
    bnds       = ((1,1),(n,n))
    
    dp arr t@(i,j)
      | match i j  = writeArray arr t True
      | otherwise  = go arr i j (i+ln-1) >>= writeArray arr t

    go arr i j k
      | k >= j     = return False
      | otherwise  = do 
        lft <- readArray arr (i,k)
        rht <- readArray arr (k+1,j)
        case (lft && rht) of
          True -> return True
          _    -> go arr i j $! (k+1)

backTrack :: Dict -> Table -> C.ByteString -> Int -> Int -> IO ()
backTrack dc tb w !ofs n
  | match w   = putStr " " >> C.putStrLn w
  | otherwise = do
    pts <- filterM (pick tb) [1..(C.length w)]
    let (u,v) = C.splitAt (head pts) w
    case ofs of
      0 -> C.putStr u 
      _ -> putStr " " >> C.putStr u 
    backTrack dc tb v (ofs + (head pts)) n
  where
    match w    = w `S.member` dc
    pick arr i = case (match (C.take i w)) of
        False -> return False
        _     -> readArray arr (ofs+i+1,n) 

solve :: Int -> IO ()
solve 0 = return ()
solve t = do
  _   <- (read <$> getLine) :: IO Int
  wds <- map C.pack . words <$> getLine
  pwd <- C.pack <$> getLine
  let n = C.length pwd
  let ln  = L.foldl1' min (map C.length wds)
  let dic = S.fromList wds
  tab <- crack dic pwd ln
  ans <- readArray tab (1,n)
  case ans of
    False -> putStrLn "WRONG PASSWORD"
    True  -> backTrack dic tab pwd 0 n
  solve $! (t-1)

main :: IO ()
main = do
  t <- read <$> getLine
  solve t


