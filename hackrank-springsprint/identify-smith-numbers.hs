import Control.Applicative
import qualified Data.Char as C
import qualified Data.List as L

primeFactors :: Int -> [Int]
primeFactors 1 = []
primeFactors n = 
  case factors of
    [] -> [n]
    _  -> factor : (primeFactors (n `div` factor))
  where
    factors = take 1 $ filter (\x -> (n `mod` x) == 0) [2 .. n-1]
    factor  = head factors

isSmith :: Int -> Bool
isSmith n = sumDigits == sumFactor
  where
  	sumDigits = sum $ map C.digitToInt (show n)
  	sumFactor = sum $ map C.digitToInt $ L.concatMap show $ primeFactors n 

main :: IO ()
main = do
  n <- read <$> getLine
  case (isSmith n) of
  	True -> putStrLn "1" 
  	_    -> putStrLn "0"

