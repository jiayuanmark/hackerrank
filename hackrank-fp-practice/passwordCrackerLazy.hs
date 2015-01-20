{-# LANGUAGE BangPatterns #-}

import Control.Applicative
import Data.Array
import qualified Data.ByteString.Char8 as C 
import qualified Data.List as L
import qualified Data.Set as S

import Debug.Trace (trace)

type Dict  = S.Set C.ByteString
type Table = Array Int Int

-- substring between i and j
substr :: Int -> Int -> C.ByteString -> C.ByteString
substr i j = C.drop (i-1) . (C.take j)

crack :: Dict -> C.ByteString -> [Int] -> Table
crack dict pwd lns = table
  where
    match i j = (substr i j pwd) `S.member` dict

    n         = C.length pwd
    bnds      = (0,n)

    table    :: Table
    table     = array bnds [ (i, dp i) | i <- range bnds ]
    
    dp 0      = -2
    dp i      = let p = filter (check i) lns
                in if L.null p then -1 else i - (head p)
    check i l = and [(i-l >= 0), (table ! (i-l) /= -1), (match (i-l+1) i)]

backTrack :: Table -> C.ByteString -> Int -> [C.ByteString]
backTrack tb w cur
  | prev < 0  = []
  | otherwise = (backTrack tb w prev) ++ [ substr (prev+1) cur w ]
  where prev = tb ! cur

solve :: Int -> IO ()
solve 0 = return ()
solve t = do
  _   <- (read <$> getLine) :: IO Int
  wds <- map C.pack . words <$> getLine
  pwd <- C.pack <$> getLine
  let n = C.length pwd
  let dic = S.fromList wds
  let lns = map C.length wds
  let tab = crack dic pwd lns
  case tab ! n of
    -1 -> putStrLn "WRONG PASSWORD"
    _  -> C.putStrLn $ C.intercalate (C.pack " ") (backTrack tab pwd n)
  solve $! (t-1)

main :: IO ()
main = do
  t <- read <$> getLine
  solve t
