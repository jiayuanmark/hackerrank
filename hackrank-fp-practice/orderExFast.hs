import Control.Applicative

data Tree = Branch { maxv :: Int
                   , lsum :: Int
                   , rsum :: Int
                   , lchd :: Tree
                   , rchd :: Tree
                   , rng  :: (Int,Int)
                   }
            Leaf   { maxv :: Int
                   , rng  :: (Int,Int)
                   } deriving (Eq, Show)
                   








main :: IO ()
main = do
  [n, k] <- map read . words <$> getLine
  arr    <- map read . words <$> getLine