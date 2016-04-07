import Control.Applicative
import qualified Data.List as L

main :: IO ()
main = do
    _ <- read <$> getLine :: IO Int
    s <- getLine
    putStrLn . show . length $ L.group s

