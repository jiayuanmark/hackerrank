import Control.Applicative
import qualified Data.ByteString as B
import qualified Data.Char as C

spec :: [Int]
spec = map C.digitToInt "31415926535897932384626433833"

isPi :: [B.ByteString] -> Bool
isPi = all ((==) <$> fst <*> snd) . (zip spec) . (map B.length)

solve :: Int -> IO ()
solve 0 = return()
solve t = do
  content <- B.splitWith (== fromIntegral (C.ord ' ')) <$> B.getLine
  case (isPi content) of
    True -> putStrLn "It's a pi song."
    _    -> putStrLn "It's not a pi song."
  solve $! (t-1)

main :: IO ()
main = do
  t <- read <$> getLine
  solve t