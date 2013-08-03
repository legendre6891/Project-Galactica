module CFrac (
eval
) where

import Data.Ratio

eval :: (Integral a) => [Ratio a] -> Ratio a
eval [] = 0
eval xs = foldr1 reduce xs
    where
        reduce x y = x + recip y
