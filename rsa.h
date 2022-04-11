//
//  rsa.h
//
//
//  Created by Max Albright on 10/19/21.
//

#ifndef rsa_h
#define rsa_h
#include <fstream>
#include <string>
#include <vector>

void encrypt(std::ofstream& filename, const long n, std::string message);

void decrypt(std::ifstream& input, std::ofstream& output, const long& d, const long& n);
long ezModularExponentiation(const long& b, const long& m);

long ModularExponentiation(const long& b, const std::vector<int>& n, const long& m);

long decryptionkey(long p, long q);

long gcd(long a, long b);

std::vector<int> binaryrep(long n);

#endif /* rsa_h */
