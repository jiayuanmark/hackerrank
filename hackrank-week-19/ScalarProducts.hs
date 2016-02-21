import Control.Applicative
import qualified Data.Set as S

fib :: [Integer]
fib = 0 : 1 : zipWith (+) fib (tail fib)

solve :: Integer -> Integer -> Integer -> Int
solve _ _ 1 = 0
solve c m n = S.size set
  where
    c'   = (c ^ 2) `mod` m
    n'   = fromIntegral n
    tup  = gen . drop 2 . take (2 * n' + 2) $ fib
    set  = S.fromList $ l1 ++ l2
    l1   = map (\x -> x * c' `mod` m) $ zipWith prod tup (tail tup)
    l2   = map (\x -> (prod x x) * c' `mod` m) $ init . tail $ tup
    -- Util functions
    prod (x,y) (u,v) = x * u + y * v
    gen []      = []
    gen (a:b:c) = (a,b) : gen c
    gen _       = error "unexpected!"

main :: IO ()
main = do
  [c, m, n] <- map read . words <$> getLine
  putStrLn . show $ solve c m n
