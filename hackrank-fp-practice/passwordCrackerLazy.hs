{-# LANGUAGE BangPatterns #-}

import Control.Applicative
import Data.Array
import qualified Data.ByteString.Char8 as C 
import qualified Data.List as L
import qualified Data.Set as S

import Debug.Trace (trace)

type Dict  = S.Set C.ByteString
type Table = Array (Int,Int) Bool

-- substring between i and j
substr :: Int -> Int -> C.ByteString -> C.ByteString
substr i j = C.drop (i-1) . (C.take j)

crack :: Dict -> C.ByteString -> Table
crack dict pwd = table
  where
    match i j  = (substr i j pwd) `S.member` dict

    n          = C.length pwd
    bnds       = ((1,1),(n,n))

    table     :: Table
    table      = array bnds [ (ij, dp ij) | ij <- range bnds ]
    
    dp (i,j)
      | i > j      = False
      | i == j     = match i j
      | match i j  = True
      | otherwise  = any (\k -> (table ! (i,k)) && (table ! (k+1,j))) [i..(j-1)]

backTrack :: Dict -> Table -> C.ByteString -> Int -> Int -> [C.ByteString]
backTrack dc tb w ofs n
  | pass w    = [w]
  | otherwise = u:(backTrack dc tb v (ofs+sp) n)
  where
    pass   = flip S.member dc
    pick i = (pass (C.take i w)) && (tb ! (ofs+i+1,n)) 
    sp     = head $ filter pick [1..]
    (u,v)  = C.splitAt sp w

solve :: Int -> IO ()
solve 0 = return ()
solve t = do
  _   <- (read <$> getLine) :: IO Int
  wds <- map C.pack . words <$> getLine
  pwd <- C.pack <$> getLine
  let n = C.length pwd
  let dic = S.fromList wds
  let tab = crack dic pwd
  case tab ! (1,n) of
    False -> putStrLn "WRONG PASSWORD"
    True  -> C.putStrLn $ C.intercalate (C.pack " ") (backTrack dic tab pwd 0 n)
  solve $! (t-1)

main :: IO ()
main = do
  t <- read <$> getLine
  solve t




