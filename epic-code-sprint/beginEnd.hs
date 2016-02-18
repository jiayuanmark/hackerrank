import Control.Applicative
import qualified Data.List as L
import qualified Data.Map as M

solve :: String -> Integer
solve s = L.foldl1' (+) $ map (\x -> (x - 1) * x `div` 2) (M.elems cnt)
  where
    cnt     = L.foldl' inc M.empty s
    inc m c = case (M.lookup c m) of
      Just o  -> M.insert c (o+1) m
      Nothing -> M.insert c 1 m

main :: IO ()
main = do
  n <- read <$> getLine
  s <- getLine
  putStrLn . show $ n + solve s