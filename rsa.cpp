//
//  rsa.cpp
//
//
//  Created by Max Albright on 10/17/21.
//
#include "rsa.h"

#include "math.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
int main(int argc, char* argv[]) {
    long p = stoll(argv[1]);
    long q = stoll(argv[2]);
    // calculate decryption key
    long key = decryptionkey(p, q);
    if (key == -1) {
        return 0;
    }
    string firstword;
    cout << "To exit: 'EXIT'. To Decrypt: 'DECRYPT [input] [output]'. To Encrypt: 'ENCRYPT [filename] [n] [message]'."
         << endl;
    cin >> firstword;
    // create a loop that allows user to continuously encrypt/decrypt files
    while (firstword != "EXIT") {
        if (firstword == "DECRYPT") {
            string inputfilename, outputfilename;
            cin >> inputfilename >> outputfilename;
            if (cin.fail()) {
                return 0;
            }
            ifstream input(inputfilename);
            ofstream output(outputfilename);
            decrypt(input, output, key, p * q);

        } else if (firstword == "ENCRYPT") {
            string outputfilename, message;
            long n;
            cin >> outputfilename >> n;
            // get rid of the leading whitespace that getline will inlcude
            getline(cin >> ws, message);
            if (cin.fail()) {
                return 0;
            }
            if (n < 27) {
                cout << "n is too small (less than 27)" << endl;
                return 0;
            } else {
                ofstream filename(outputfilename);
                encrypt(filename, n, message);
            }
        } else {
            return 0;
        }
        cout << "To exit: 'EXIT'. To Decrypt: 'DECRYPT [input] [output]'. To Encrypt: 'ENCRYPT [filename] [n] "
                "[message]'."
             << endl;
        cin >> firstword;
    }
    return 0;
}

void decrypt(ifstream& input, ofstream& output, const long& d, const long& n) {
    long C;
    while (!input.fail()) {
        input >> C;
        // stop when there are no more integers to decrypt
        if (input.fail()) {
            break;
        }
        // perform modular exponentiation on the first int
        long M = ModularExponentiation(C, binaryrep(d), n);

        // convert M to characters
        string Ms;
        string mstring;
        stringstream ss(mstring);
        ss << M;
        ss >> mstring;
        int x = 1 + log(n / 27) / log(100);
        // add any leading zeroes back that were lost due to casting strings to ints
        int diff = x * 2 - mstring.size();
        string zero = "0";
        for (int i = 0; i < diff; i++) {
            mstring = zero + mstring;
        }
        // read two characters at a time
        for (int i = 0; i < (int)(mstring.size()); i += 2) {
            int sub = stoi(mstring.substr(i, 2));
            string addtoM;
            if (sub == 0) {
                addtoM = " ";
            } else {
                addtoM = (char)(sub + 96);
            }
            Ms.append(addtoM);
        }
        output << Ms;
    }
}

void encrypt(ofstream& filename, const long n, string message) {
    // how many letters to read at a time
    int x = 1 + log(n / 27) / log(100);
    // keep track of how many letters of the message have been read
    int runningx = 0;
    while (runningx < (int)(message.size())) {
        string Ms;
        // translate the letters into integers, x letters at a time
        for (int i = 0; i < x; i++) {
            string addtoM;
            if (i + runningx >= (int)(message.size())) {
                addtoM = "00";

            } else if (message[i + runningx] == ' ') {
                addtoM = "00";
            } else {
                if (message[i + runningx] < 106) {
                    addtoM = "0" + to_string(((int)(message[i + runningx])) - 96);
                } else {
                    addtoM = to_string(((int)(message[i + runningx])) - 96);
                }
            }
            Ms.append(addtoM);
        }
        long M;
        stringstream ss(Ms);
        ss >> M;
        // perform modular exponentiation with e as the power,
        // so it doesn't need to be passed as a parameter.
        filename << ezModularExponentiation(M, n) << " ";
        runningx += x;
    }
}

long ezModularExponentiation(const long& b, const long& m) {
    // Perform modular exponentiation with e as the power.
    // e will always be the same in binary so it doesn't
    // need to be passed in as a parameter.
    long x = 1;
    long power = b % m;
    // e in binary is 10000000000000001;
    for (int i = 0; i < 17; i++) {
        if (i == 0 || i == 16) {
            x = ((x * power) % m);
        }
        power = ((power * power) % m);
    }
    return x;
}

long ModularExponentiation(const long& b, const vector<int>& n, const long& m) {
    // modular exponentiation algorithm we learned in class
    long x = 1;
    long power = b % m;
    // e in binary is 10000000000000001;
    for (int i = 0; i < (int)(n.size()); i++) {
        if (n[i] == 1) {
            x = (x * power) % m;
        }
        power = ((power * power) % m);
    }
    return x;
}

long decryptionkey(long p, long q) {
    // Use euclidean algorithm to calculate this
    long denom = gcd(p - 1, q - 1);
    long L = (p - 1) * (q - 1) / denom;
    // if L is less than or equal to e (65537)
    if (L <= 65537) {
        cout << "L value too small" << endl;
        return -1;  // end this function call and terminate program in main
    }
    // Use extended Euclidean Algorithm to find d
    long s = 0;
    long old_s = 1;
    long t = 1;
    long old_t = 0;
    long r = 65537;
    long old_r = L;
    while (r != 0) {
        long quotient = old_r / r;
        long temp = r;
        r = old_r - quotient * r;
        old_r = temp;
        temp = s;
        s = old_s - quotient * s;
        old_s = temp;
        temp = t;
        t = old_t - quotient * t;
        old_t = temp;
    }
    if (old_t < 0) {
        old_t += ((p - 1) * (q - 1));
    }
    return old_t;
}

long gcd(long a, long b) {
    // Euclidean Algorithm
    long x = a;
    long y = b;
    while (y != 0) {
        long r = x % y;
        x = y;
        y = r;
    }
    return x;
}

vector<int> binaryrep(long n) {
    // convert n to binary in the form of a vector
    vector<int> a;
    while (n > 0) {
        a.push_back(n % 2);
        n /= 2;
    }
    return a;
}
