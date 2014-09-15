import Data.Char
import qualified Data.List as L

digitSum :: String -> String
digitSum = show . sum . map digitToInt

superDigit :: String -> String
superDigit x
	| length x == 1 = x
	| otherwise = superDigit $ digitSum x

main :: IO ()
main = do
	ln <- getLine
	let 
	  c = L.words ln
	  n = c !! 0
	  k = c !! 1
	  p = show $ (read k) * (read $ digitSum n)
	putStrLn $ superDigit p