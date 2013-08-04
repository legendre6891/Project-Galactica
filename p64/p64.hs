import Data.List (elemIndex)
import Math.NumberTheory.Powers.Squares

squares = map (^2) [1..]

data QCFStep = QCFStep Int Int Int deriving (Eq)

instance Show QCFStep where
    show (QCFStep a b c) = "(√" ++ show a ++ " + " ++ show b ++ ") / " ++ show c

instance Ord QCFStep where
    QCFStep a b c `compare` QCFStep d e f = (a + b + c) `compare` (d + e + f)

getNext :: QCFStep -> QCFStep
getNext (QCFStep a b c) = let root = sqrt . fromIntegral $ a
                              ipart = floor $ (root + fromIntegral b) / fromIntegral c
                              b1 = b - ipart * c
                              c' = (a - b1^2) `div` c
                          in QCFStep a (-b1) c'


period :: Int -> Int
period a = periodHelper [QCFStep a 0 1]

periodHelper :: [QCFStep] -> Int
periodHelper qs = let q' = getNext $ head qs
                  in case elemIndex q' qs of
                        Just a -> a + 1
                        Nothing -> periodHelper $ q':qs

solve n = length $ filter odd $ map period $ filter (not . isSquare') [1..n]
