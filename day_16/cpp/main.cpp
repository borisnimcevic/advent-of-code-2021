#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <math.h>
#include <string>
#include <map>
#include <set>
#include <bitset>

void part1(const std::string &input);

const std::string inputFile = "../input/input.txt";
/* const std::string inputFile = "../input/test.txt"; */

const std::string TEST1 = "D2FE28";

int main()
{
  part1(TEST1);
  /* part1("1"); */
}

template <size_t N1, size_t N2 >
std::bitset <N1 + N2> concat( const std::bitset <N1> & b1, const std::bitset <N2> & b2 ) {
    std::string s1 = b1.to_string();
    std::string s2 = b2.to_string();
    return std::bitset <N1 + N2>( s1 + s2 );
}

void printBin(const std::vector<bool> &in)
{
  for(const auto &a: in)
  {
    if(a)
      std::cout << "1";
    else
      std::cout << "0";
  }
  std::cout << "\n";
}

void part1(const std::string &input)
{
  std::vector<bool> msg;
  std::bitset<4> letter = 0;
  for(const auto &c : input)
  {
    if(c <= '9')
      letter = c - '0';
    else
      letter = c - 'A' + 10;

    for(int i = letter.size()-1; i >= 0; --i)
    {
      if(letter[i])
        msg.push_back(true);
      else
        msg.push_back(false);
    }
  }

  printBin(msg);
}
