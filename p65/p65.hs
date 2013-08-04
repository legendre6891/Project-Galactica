import CFrac
import Data.Char (digitToInt)
import Data.Ratio (numerator, (%))

main = putStrLn . show . sum . map digitToInt $ show . numerator . foldr1 (\x y -> x + recip y) . map (%1) $ take 100 $ (:) 2 $ concat [ [1,2*x,1] | x <- [1..] ]
