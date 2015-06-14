{-# LANGUAGE FlexibleContexts #-}

import Control.Applicative
import Control.Monad
import Data.Array.IO
import qualified Data.List as L

mx :: Int
mx = 10^6

sieveArray :: Int -> IO (IOUArray Int Bool)
sieveArray n = do
  arr <- newArray (1, n) True :: IO (IOUArray Int Bool)
  writeArray arr 1 False
  forM_ nums (go arr)
  return arr
  where
    nums        = L.takeWhile (\x -> x * x <= n) [2..n]
    go arr x    = do p <- readArray arr x
                     when p $ forM_ [x * x, x * (x+1)..n] $
                      \y -> writeArray arr y False

check :: (IOUArray Int Bool) -> Int -> IO Int
check arr n
  | odd n     = do p <- f 2
                   return $ if p then 2 * (n - 2) else 0
  | otherwise = try [2..(n `div` 2 - 1)]
  where
    f x       = do a <- readArray arr x
                   case a of
                    False -> return False
                    _     -> readArray arr (n - x)
    try []     = return 0
    try (y:ys) = do chk <- f y
                    case chk of
                      True -> return $ y * (n - y)
                      _    -> try ys

solve' :: (IOUArray Int Bool) -> Int -> Int -> IO (Int, Int)
solve' primes a b = do
  chk <- mapM (check primes) [a..b]
  let res = filter (/= 0) chk
  return (L.length res, mul res)
  where
    mul = L.foldl' (\x y -> mod (x * y) (10^9+7) ) 1

solve :: (IOUArray Int Bool) -> Int -> IO ()
solve _ 0 = return ()
solve primes n = do
  [a, b] <- map read . words <$> getLine
  (x, y) <- solve' primes a b
  putStrLn $ (show x) ++ " " ++ (show y)
  solve primes (n-1)

main :: IO ()
main = do
  primes <- sieveArray mx
  n <- read <$> getLine
  solve primes n
