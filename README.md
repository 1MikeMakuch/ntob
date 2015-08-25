Convert integers between bases


$ ./ntob -h
ntob, version 1.01

usage: ./ntob -o <output base> -n <input value> [-i <input base>] [-1|-2] [-h]

N to Base: Convert a number from one base to another. Bases can be anything from 2 to 36.
Input base defaults to 10. Bases beyond 16 use the alphabet as you'd expect.

-1 or -2 calculate 1s or 2s complement

Examples:

$ ntob -o 2 -n 10             # convert 10 to binary
1010

$ ntob -o 10 -n 1010 -i 2     # and back
10

$ ntob -o 8 -n 10             # convert 10 to octal
12

$ ntob -o 16 -n 10            # base 16 A is equal to decimal 10
A

$ ntob -o 36 -n 35            # base 36 Z is equal to decimal 35
Z

$ ntob -o 36 -n  1767707668033969
HELLOWORLD

