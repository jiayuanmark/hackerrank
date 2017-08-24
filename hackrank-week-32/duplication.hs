import Control.Applicative ((<$>))
import qualified Data.Vector.Unboxed as V

precompute :: V.Vector Bool
precompute = head $ dropWhile (\v -> V.length v <= 1000) vs
  where
    dup v = v V.++ V.map not v
    vs = iterate dup (V.singleton False)

main :: IO ()
main = do
  let v = precompute
  q <- read <$> getLine
  flip mapM_ [1..q] $ \_ -> do
    x <- read <$> getLine
    case (v V.! x) of
      True  -> putStrLn "1"
      False -> putStrLn "0"

