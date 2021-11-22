# ECC

## Files for ecc
```ecc.cpp```   
```ecc_parameters.txt```  
```ECC_README.md```
## Installation
This README presumes that mpz_library is appropriately installed in the client machine.

We run the cpp file, to perform the operations as specified in the question.
 
```bash
g++ -o test ecc.cpp 
./test
```
Use **interactive mode** if you want to calculate via the pre - setted value for each function.( *Press 1 when the programs successfully runs* )
If however, one wants to add their own P,x and P,y one needs to enter 0 to start the **static mode**, **after editing the code as per their convenience.** 

## Usage

Each operation: ```Addition, Multiplication, Subtraction, Negation,Calculate``` are done using the following functions:  

```Point Addition( Point P, Point Q, mpz_t p, mpz_t a, mpz_t b)``` Adds Point P + Q to get R  
  
```Point Multiplication ( Point P, mpz_t p, mpz_t a, mpz_t b, int n)``` Multiplies P , n times  i.e P\*P\*P...n times
 
```Point Subtraction( Point P, Point Q, mpz_t p, mpz_t a , mpz_t b)``` : Subtracts Q from P  
  
```Point Negate( Point P, mpz_t p, mpz_t a, mpz_t b)```  Negates given Point P  

```int calculate(mpz_t x,mpz_t p)``` : returns whether a valid y exists on the x inputted    
```int shanks(mpz_t a, const mpz_t x, const mpz_t prime)``` 

 

## Navigating the Code  
To perform each of the operations above a ```TODO``` block corresponding  
 to the calling of each of the functions above has been commented in the code,  
 and needs to be uncommented to perform the respective operation. **The TODO block   
will only run during the pre-defined mode, or when you enter 0 in the terminal at the start**   
 You can also change the values of P and Q for each operation by modifying the values of x and y   
for P and Q in the commented code block itself.

## Additional Notes
Shanks' algorithm is implemented with suitable references from ```GitHub```,```Wikipedia.com```  
The values of p,a, b for **static mode**   
are predefined in the text file ```ecc_parameters.txt``` and   
need not be defined repeatedly as they're read   
automatically during **static mode**.

## License
[MIT](https://choosealicense.com/licenses/mit/)
