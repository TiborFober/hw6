#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <algorithm>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        std::string str = k;
        // make all letters lowercase
        for(size_t i = 0; i < str.size(); ++i)
        {
          str[i] = std::tolower(str[i]);
        }

        // init w[5] with 0s
        unsigned long long w[5] = {0,0,0,0,0};
        int groupCount = 0;

        // start from the end
        for(int i = str.length(); i > 0 && groupCount < 5; i -= 6)
        {

          int start = 0;
          if((i - 6) > 0)
          {
            start = i - 6;
          }
          else
          {
            start = 0;
          }
          std::string group = str.substr(start, i - start);
          unsigned long long val = 0;

          // convert group to base 36 number
          for(size_t j = 0; j < group.size(); ++j)
          {
            val *= 36;
            val += static_cast<unsigned long long>(letterDigitToNumber(group[j]));
          }
          
          // store it in reverse order
          w[4 - groupCount] = val;
          ++groupCount;
        }

        unsigned long long hash = 0;
        for(int i = 0; i < 5; ++i)
        {
          hash += rValues[i] * w[i];
        }

        return static_cast<HASH_INDEX_T>(hash);
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if(std::isalpha(letter))
        {
          return static_cast<HASH_INDEX_T>(letter - 'a');
        }
        else if(std::isdigit(letter))
        {
          return static_cast<HASH_INDEX_T>(letter - '0' + 26);
        }
        else
        {
          return 0;
        }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
