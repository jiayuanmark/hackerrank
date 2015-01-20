import Control.Applicative
import qualified Data.List as List

solve :: Integer -> Integer -> Integer
solve n 0 = 1
solve n k = List.foldl' div val [2..k]
	where val = List.foldl1' (*) [(n-k+1)..n]

go :: Int -> IO ()
go 0 = return ()
go t = do
	[n, k] <- map read . words <$> getLine 
	putStrLn . show $ (solve n k) `mod` (10^8+7)
	go $! (t-1)

main :: IO ()
main = do
	t <- read <$> getLine
	go t

