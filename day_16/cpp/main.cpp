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

/* const std::string TEST = "D2FE28"; */
const std::string TEST = "38006F45291200";

int main()
{
  part1(TEST);
  /* part1("1"); */
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

bool isAllZero(const std::vector<bool> &in)
{
  for(const auto &a: in)
  {
    if(a)
      return false;
  }
  return true;
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

  bool message_done = false;
  while(!message_done)
  {
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

    if(type == 4)
    {
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

      /* int leftover_bits = 4 - ((num_counter * 5 + 6) % 4); */
      /* if(leftover_bits != 4) */
      /* { */
      /*   for(int i = 0; i < leftover_bits; ++i) */
      /*   { */
      /*     msg.pop_back(); */
      /*   } */
      /* } */
      int literal_number = 0;
      for(int i = 0; i < nums.size(); ++i)
      {
        literal_number += nums.at(i) << ((nums.size() - i -1) * 4);
      }
      std::cout << "literal_number : " << literal_number << "\n";
      /* printBin(msg); */
      std::cout << "\n";
    }
    else
    {
      bool typeID = msg.back();
      msg.pop_back();
      std::cout << "typeID " << typeID <<  "\n";
      if(typeID)
      {
      }
      else
      {
        // 15 bits
        std::bitset<15> bit_length;
        for(int i = 0; i < 15; ++i)
        {
          bit_length[15 - 1 - i] = msg.back();
          msg.pop_back();
        }
        /* std::cout << bit_length << "\n"; */
        std::cout << "bit length : " << (int)bit_length.to_ulong() << "\n";
        /* printBin(msg); */
        std::cout << "\n";
      }
    }

    message_done = isAllZero(msg);
  }

}
