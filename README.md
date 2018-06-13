# Numbers
A memory efficient implementation of BigInteger for C++ , along with a Random class to generate approximately uniformly distributed Random numbers.

1. To use the libray save the file Numbers.h in the same folder as your resident code.
2. Write the line #include "Numbers.h" in the preprocessor directives section of your code.

Usage:
1. Initialisation:
	a. Int n;
	b. Int n(-4356); /// or any other value
	c. Int n = 32875 /// or any other value
	d. Int c = 43463;
          	Int f = c;
2. All operators including logical , relational , increment , decrement along with simple arithmetic operators are available , the same as with a normal integer.
3. cin and cout have been overloaded so the numbers can be input from the keyboard too.
4. The function factorial returns an Int which contains the factorial of the number given as argument to it.
5. To use the Random function first an object of the Random class must be created. The argument passed to the constructor only determines the time taken for instantiation. A small value like 10,20,5 would not be suitable for the function to perform well and a large value like 2500 , 1500 would not be suitable either. So ideally any value between 100 to 1200 should be chosen for the same. 
Random a(232);
a.random(b) will give return a long long type variable which will be less tha or equal to b. This can only be used for generating positive numbers , so a negative input would not work.

This implementation is very optimal in terms of memory utilisation. The numbers are stored in binary , however since data is only byte addressable one byte is used to store 8 bits of the data using a character. Using a simple bool variable would have meant that every bit is stored as a byte making this system very memory ineffecient.
Now the systems requires ceil(log(n)/8)+1 bytes for the number n. The extra byte is for the sign of the number. 
