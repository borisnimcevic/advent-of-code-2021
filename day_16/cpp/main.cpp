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
  // ===== read input start (backwards, it's easier later)
  std::vector<bool> msg;
  std::bitset<4> letter = 0;
  /* for(const auto &c : input) */
  for(int i = input.size()-1; i >= 0; --i)
  {
    if(input.at(i) <= '9')
      letter = input.at(i) - '0';
    else
      letter = input.at(i) - 'A' + 10;

    for(int j = 0; j < letter.size(); ++j)
    {
      if(letter[j])
        msg.push_back(true);
      else
        msg.push_back(false);
    }
  }

  printBin(msg);

  // ===== read input end

  int version = 0;
  int type = 0;
  std::vector<int> nums;

  for(int i = 0; i < 3; ++i)
  {
    version <<=1;
    if(msg.back())
      version++;
    msg.pop_back();
  }

  std::cout << "version " << version << "\n";

  for(int i = 0; i < 3; ++i)
  {
    type <<=1;
    if(msg.back())
      type++;
    msg.pop_back();
  }

  std::cout << "type " << type << "\n";

  int num_counter = 0;
  bool end_packet = false;
  while(!end_packet)
  {
    if(!msg.back())
      end_packet = true;

    msg.pop_back();

    int temp_num = 0;
    for(int i = 0; i < 4; ++i)
    {
      temp_num <<=1;
      if(msg.back())
        temp_num++;

      msg.pop_back();
    }

    nums.push_back(temp_num);
    num_counter++;
  }

  int leftover_bits = 4 - ((num_counter * 5 + 6) % 4);
  if(leftover_bits != 4)
  {
    for(int i = 0; i < leftover_bits; ++i)
    {
      msg.pop_back();
    }
  }

  for(const auto n : nums)
  {
    std::cout << n << ", ";
  }
  std::cout << "\n";

  std::cout << "size of msg : " << msg.size() << "\n";
}
