import Control.Applicative ((<$>))
import Control.Monad
import Data.Char (ord)
import Data.List (group)
import qualified Data.Set as S

weight :: Char -> Int
weight c = ord c - 96

preprocess :: String -> S.Set Int
preprocess s = S.fromList $ concatMap calc $ group s 
  where
    calc g = let w = weight (head g)
             in map (w *) [1..length g]

main :: IO ()
main = do
  s <- getLine
  let t = preprocess s
  n <- read <$> getLine
  forM_ [1..n] $ \_ -> do
    x <- read <$> getLine
    case (x `S.member` t) of
      True  -> putStrLn "Yes"
      False -> putStrLn "No"