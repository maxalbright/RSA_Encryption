Max Albright-4053997355
mdalbrig@usc.edu
RSA ENCRYPTION and DECRYPTION:

compile using "make" or "make rsa".

run using ./rsa <p> <q> where p and q are large primes

then you will be prompted with the following options: 
EXIT Gracefully terminate the program.
DECRYPT [input] [output] Opens the file at [input], reads the contents of the file, decrypts the message, and overwrites the contents of the file at [output] with the decrypted message.
ENCRYPT [filename] [n] [message] Creates/overwrites the file at the specified path, writing an encrypted version of [message], which is a string of lowercase letters a-z and spaces (but no tabs or newlines). [n] is an integer which will be used in the encryption process.

The program will continue until EXIT is the command or there is an invalid input. 

This program utilized modular exponentiation algorithms, the Euclidean Algorithm, and the Extended Euclidean Algorithm to perform RSA encryption and decryption. 
