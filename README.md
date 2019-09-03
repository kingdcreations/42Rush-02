# rush02

## Install:

make fclean   
make

## Usage:

./rush-02 \<number\>

## Examples:

./rush-02 42 | cat -e  
  forty two$

./rush-02 0 | cat -e  
  zero$

./rush-02 10.4 | cat -e  
  error$

./rush-02 100000 | cat -e  
  one hundred thousand$
