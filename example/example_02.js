import io as io


// list comprehention
factorial :: (n) =>
    mul [x | x in 1 .. n]


/**************/
factorial :: (n) => 
    n > 0  | n * factorial(n - 1) 
    n == 1 | 


main :: _ => print $ factorial 10
