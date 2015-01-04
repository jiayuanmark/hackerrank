import qualified Data.List as L
import Control.Applicative

parse :: [String] -> [(Int,Int)]
parse (p:b:ps) = (read p, read b) : parse ps
parse [] = []
parse (p:[]) = error "illegal input"

merge :: [(Int,Int)] -> [(Int,Int)] -> [(Int, Int)]
merge _ [] = []
merge [] _ = []
merge l@((pk,pv):ps) r@((qk,qv):qs)
  | pk == qk = (pk,min pv qv) : merge ps qs  
  | pk < qk = merge ps r
  | otherwise = merge l qs

readFactor :: IO ([(Int,Int)])
readFactor = do
  ln <- getLine
  return $ parse (words ln)

solve :: Int -> [(Int,Int)] -> IO ()
solve 0 f = putStrLn $ L.intercalate " " $ map (\(x,y) -> (show x) ++ " " ++ (show y)) f
solve n f = do
  nf <- readFactor
  solve (n-1) $ merge f nf

main :: IO()
main = do
  n <- read <$> getLine
  f <- readFactor
  solve (n-1) f
