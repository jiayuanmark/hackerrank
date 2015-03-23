import Control.Applicative
import qualified Data.List as L

isKaprekar :: Integer -> Bool
isKaprekar num = num == ((sread l) + (sread r))
  where
    sqr      = show (num * num)
    d        = length $ show num
    pt       = (length sqr) - d       
    (l,r)    = L.splitAt pt sqr
    sread [] = 0
    sread x  = read x

main :: IO ()
main = do
  p <- read <$> getLine
  q <- read <$> getLine
  let sol = filter isKaprekar [p..q]
  if length sol /= 0
  	then putStrLn $ L.unwords (map show sol)
  	else putStrLn "INVALID RANGE"