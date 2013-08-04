
good num = all demDigits $ show num
    where
        demDigits d = elem d ['0','1','2']

f n = f_help n 1
    where
        f_help n a
                 | good (n * a) = a
                 | otherwise = f_help n a+1

main = putStrLn $ show . sum $ map f [1..1000]
