{-# LANGUAGE BangPatterns #-}

import Control.Applicative
import Control.Monad
import Data.Array.IO
import qualified Data.ByteString.Char8 as C 
import qualified Data.List as L
import qualified Data.Set as S

import Debug.Trace (trace)

type Dict  = S.Set C.ByteString
type Table = IOUArray Int Int

-- substring between i and j
substr :: Int -> Int -> C.ByteString -> C.ByteString
substr i j = C.drop (i-1) . (C.take j)

crack :: Dict -> C.ByteString -> [Int] -> IO Table
crack dict pwd lns = do
  arr <- newArray bnds (-1) :: IO Table
  forM_ [0..n] (dp arr)
  return arr
  where
    match i j = (substr i j pwd) `S.member` dict

    n         = C.length pwd
    bnds      = (0,n)
    
    dp arr 0  = writeArray arr 0 (-2)
    dp arr i  = go arr i lns >>= writeArray arr i

    go arr i [] = return (-1)
    go arr i (l:ls)
      | (i-l) < 0 = go arr i ls
      | otherwise = do
        sub <- readArray arr (i-l)
        if (sub /= -1) && (match (i-l+1) i)
        then return (i-l) 
        else go arr i ls

backTrack :: Table -> C.ByteString -> Int -> Int -> IO ()
backTrack tb w cur n = do
  prev <- readArray tb cur
  if prev < 0
  then return ()
  else do
    backTrack tb w prev n
    C.putStr (substr (prev+1) cur w)
    if cur == n 
    then putStrLn ""
    else putStr " "

solve :: Int -> IO ()
solve 0 = return ()
solve t = do
  _   <- (read <$> getLine) :: IO Int
  wds <- map C.pack . words <$> getLine
  pwd <- C.pack <$> getLine
  let dic = S.fromList wds
  let ls  = map C.length wds
  tab <- crack dic pwd ls
  let n   = C.length pwd
  ans <- readArray tab n
  case ans of
    -1 -> putStrLn "WRONG PASSWORD"
    _  -> backTrack tab pwd n n
  solve $! (t-1)

main :: IO ()
main = do
  t <- read <$> getLine
  solve t


