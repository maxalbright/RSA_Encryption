# RSA Encryption and Decription

## How to Compile & Run:
- Compile using "make" or "make rsa"
- Run using ./rsa p q (where p and q are large primes)

## Then you will be prompted with the following options: 
  
1. EXIT - Gracefully terminate the program.
2. DECRYPT "input" "output" - Opens the file at "input", reads the contents of the file, decrypts the message, and overwrites the contents of the file at "output" with the decrypted message.
3. ENCRYPT "filename" "n" "message" - Creates/overwrites the file at the specified path, writing an encrypted version of "message", which is a string of lowercase letters a-z and spaces (but no tabs or newlines). 
- "n" is an integer (equal to p * q) which will be used in the encryption process. <br>

The program will continue until EXIT is the command or there is an invalid input. 

This program utilized modular exponentiation algorithms, the Euclidean Algorithm, and the Extended Euclidean Algorithm to perform RSA encryption and decryption. 
