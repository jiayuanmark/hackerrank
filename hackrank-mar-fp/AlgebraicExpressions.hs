import Control.Applicative ((<$>), (*>), (<*))
import Control.Monad (forM_)
import Data.List (intercalate)
import Text.Parsec
import Text.Parsec.String
import Text.Parsec.Char
import Text.Parsec.Combinator
import qualified Data.Map.Strict as M

data Expr = Constant Int
          | Single Int Int
          | Neg Expr
          | Add Expr Expr
          | Sub Expr Expr
          | Mul Expr Expr
          | Div Expr Expr
          | Exp Expr Expr
          deriving (Eq, Show)

num :: Parser Int
num = read <$> many1 digit

withSpaces :: Parser a -> Parser a
withSpaces p = spaces *> p <* spaces

expr :: Parser Expr
expr = withSpaces (term `chainl1` addop)

term :: Parser Expr
term = withSpaces p
  where p   = try nop <|> (signed factor) `chainl1` mulop
        nop = do
          f  <- signed factor
          fs <- many1 factor
          return (foldl Mul f fs)

signed :: Parser Expr -> Parser Expr
signed p = do
  sgn <- withSpaces $ option '+' (char '-')
  e   <- p
  case sgn of
    '+' -> return e
    '-' -> return (Neg e)

factor :: Parser Expr
factor = withSpaces p
  where p =   try single
          <|> expo

expo :: Parser Expr
expo = (parens <|> constant) `chainl1` expop

parens :: Parser Expr
parens = char '(' *> expr <* char ')'

constant :: Parser Expr
constant = Constant <$> num

single :: Parser Expr
single = do
  c <- withSpaces (option 1 num)
  char 'x'
  p <- spaces *> option 1 parsePower
  return $ Single c p
  where
    parsePower = char '^' *> num

expop :: Parser (Expr -> Expr -> Expr)
expop = char '^' *> return Exp

mulop :: Parser (Expr -> Expr -> Expr)
mulop =   char '*' *> return Mul
      <|> char '/' *> return Div

addop :: Parser (Expr -> Expr -> Expr)
addop =   char '+' *> return Add
      <|> char '-' *> return Sub

parseInput :: IO Expr
parseInput = do
  line <- getLine
  case (parse (expr <* eof) "" line) of
    Left  _  -> error "parse failure!"
    Right ex -> return ex

interp :: Expr -> M.Map Int Int
interp (Constant x) =
  M.singleton 0 x
interp (Single x y) =
  M.singleton y x
interp (Neg e) =
  M.map negate (interp e)
interp (Add e1 e2) =
  M.unionWith (+) (interp e1) (interp e2)
interp (Sub e1 e2) =
  M.unionWith (+) m1 (M.map negate m2)
  where
    m1 = interp e1
    m2 = interp e2
interp (Mul e1 e2) =
  foldl f M.empty m1
  where
    m1        = M.toList (interp e1)
    m2        = interp e2
    f m (k,v) =
      let m' = M.map (* v) (M.mapKeys (+ k) m2)
      in M.unionWith (+) m m'
interp (Div e1 e2) =
  case (M.lookup 0 m2) of
    Just d | d /= 0 -> M.map (`div` d) m1
    _               -> error "divide by zero!"
  where
    m1 = interp e1
    m2 = interp e2
interp (Exp e1 e2) =
  M.singleton 0 (a ^ b)
  where
    a = M.findWithDefault 0 0 (interp e1)
    b = M.findWithDefault 0 0 (interp e2)

output :: M.Map Int Int -> IO ()
output m =
  case filter ((/= 0) . snd) (M.toDescList m) of
    []           -> putStrLn "0"
    (t@(_,v):xs) -> if v < 0 then putStrLn $ "-" ++ format t ++ " " ++ format' xs
                    else putStrLn $ format t ++ " " ++ format' xs
  where
    format (k,v)
      | k == 0    = show (abs v)
      | k == 1    = coed ++ "x"
      | otherwise = coed ++ "x^" ++ (show k)
      where coed = if abs v == 1 then "" else show (abs v)

    format' = let f t@(_,x) = (if x > 0 then "+ " else "- ") ++ format t
              in intercalate " " . map f

solve :: IO ()
solve = do
  e <- parseInput
  output (interp e)

main :: IO ()
main = do
  t <- read <$> getLine
  forM_ [1..t] $ \_ -> solve
