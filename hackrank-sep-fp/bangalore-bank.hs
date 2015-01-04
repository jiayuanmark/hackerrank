import qualified Data.List as L
import Data.Array.Unboxed
import Data.Array.IO
import Data.Array.Base
import Control.Monad

type Prob = (UArray Int Int, Int)

readInput :: IO (Prob)
readInput =
  do
    sz <- getLine
    ln <- getLine
    let n = read sz
    let account = listArray (1,n) $ map parseDigit (L.words ln)
    return (account, n)
  where
    parseDigit x
      | x == "0" = 10
      | otherwise = read x

solve :: Prob -> IO Int
solve (account, n) =
  do
    arr <- newArray (0,n-1) 0 :: IO (IOUArray Int Int)
    dp arr 2
    init <- unsafeRead arr 0
    sol <- mmin arr 1 init
    return (sol + n)
  where
    diff a b = abs ((account ! a) - (account ! b))

    mmin arr i acc | arr `seq` i `seq` acc `seq` False = undefined
    mmin arr i acc = 
      if i == n then return acc
      else unsafeRead arr i >>= (\v -> mmin arr (i+1) (min v acc))
    
    loop arr i inc j acc | arr `seq` i `seq` inc `seq` j `seq` acc `seq` False = undefined 
    loop arr i inc j acc = 
      if j == (i-1) then return acc
      else do
        v <- unsafeRead arr j
        unsafeWrite arr j (v + inc)
        loop arr i inc (j+1) (min acc (v + diff i j))

    dp arr i | arr `seq` i `seq` False = undefined
    dp arr i =
      if i == (n+1) then return ()
      else do
        val <- unsafeRead arr 0
        unsafeWrite arr 0 (val + inc)
        minval <- loop arr i inc 1 val
        unsafeWrite arr (i-1) minval
        dp arr (i+1)
      where inc = diff i (i-1)

main :: IO ()
main = do
  input <- readInput
  ans <- solve input
  putStrLn $ show ans