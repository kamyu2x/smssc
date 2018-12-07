# smssc

smssc is a small library that provides two functions for breaking down an image into Sega Master System sprites.

## Input

`r_mat` is a pointer to the entry (`0`,`0`) of an `r_x`-by-`r_y` matrix. So `r_mat[y*r_x + x]` is the entry (`x`,`y`)
(0 ≤ `x` < `r_x`, 0 ≤ `y` < `r_y`).
`r_mat[y*r_x + x] != 0` if and only if pixel (`x`,`y`) is in the region that smssc8x8 (resp. smssc8x16) tries to cover with 8x8 sprites (resp. 8x16 sprites).

`c_n1` is an upper bound for the minimum number of sprites. Setting `c_n1` to a sharp upper bound could speed up the function (if such an upper bound can be guessed). In all cases, `c_n1` must be ≤ 64. Setting `c_n1` = 64 should be fine in most cases.

constraints: 
* 0 ≤ *w* ≤ 256
* 0 ≤ *h* ≤ 249
* 0 ≤ `c_n1` ≤ 64

where *w* and *h* are the width and height of the smallest rectangle that contains all the entries of matrix `r_mat` that are different from 0. In particular, these 2 constraints are satisfied in the case  
0 ≤ `r_x` ≤ 256  
0 ≤ `r_y` ≤ 249

## Output

return value = 1 if the function was not able to allocate memory for `c0_x` or `c0_y` (malloc)  
return value = 0 otherwise
 
`c0_n` = the number of sprites  
`(*c0_x)[i]` = the x-coordinate of the top left corner for sprite i (0 ≤ `i` < `*c0_n`)  
`(*c0_y)[i]` = the y-coordinate of the top left corner for sprite i (0 ≤ `i` < `c0_n`). If `r_mat` is a zero matrix or if the function was not able to cover the region with a number of sprites ≤ `c_n1`, then  
`*c0_n` = 0  
`*c0_x` = `*c0_y` = `NULL`
