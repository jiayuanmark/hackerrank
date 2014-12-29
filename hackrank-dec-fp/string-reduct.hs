import qualified Data.List as L

main :: IO()
main = do
	s <- getLine
	putStrLn $ L.nub s