#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <math.h>

void getData(std::vector<std::vector<std::string>> &);
uint64_t part1(const std::vector<std::vector<std::string>> &);
uint64_t part2(const std::vector<std::vector<std::string>> &);

const std::string inputFile = "../input/input.txt";
/* const std::string inputFile = "../input/test.txt"; */

int main()
{
  std::vector<std::vector<std::string>> digits;
  getData(digits);
  std::cout << part1(digits) <<  " <<<<< part1" << std::endl;
  std::cout << part2(digits) <<  " <<<<< part2" << std::endl;
}

void getData(std::vector<std::vector<std::string>> &digits)
{
  std::ifstream file(inputFile);

  if(!file)
  {
    std::cerr<<"Cannot find the file."<< std::endl;
  }

  std::string digit;
  std::vector<std::string> row;


  while(!file.eof())
  {
    for(int i = 0; i < 14; ++i)
    {
        file >> digit;
        std::sort(digit.begin(), digit.end());
        row.push_back(digit);
    }
    digits.push_back(row);
    row.clear();
  }
  digits.pop_back();
}

uint64_t part1(const std::vector<std::vector<std::string>> &digits)
{
  uint64_t sum = 0;
  for(const auto &r : digits)
  {
    for(int i = 10; i < 14; ++i)
    {
      auto len = r.at(i).size();
      if(len == 2 || len == 3 || len == 4 || len == 7)
      {
        sum++;
      }
    }
  }

  return sum;
}

std::string findMagicNum(std::vector<std::string> &mix, const std::string inputNum)
{
  uint64_t min = 99999; // some large value
  uint64_t minIndex = 0;

  for(int i = 0; i < mix.size(); ++i)
  {
    int hit = 0;
    for(auto charMix : mix.at(i)) 
    {
      for(auto charIn : inputNum)
      {
        if(charIn == charMix)
        {
          hit++;
          break;
        }
      }
    }
    if(hit < min)
    {
      min = hit;
      minIndex = i;
    }
  }

  std::string newNum = mix.at(minIndex);
  mix.erase(mix.begin()+minIndex);
  return newNum;
}

uint64_t findValue(const std::string &s, const std::vector<std::string> & rewired)
{
  for(int i = 0 ; i < rewired.size(); ++i)
  {
    if(s == rewired.at(i))
    {
      return i;
    }
  }
  return 0;
}


uint64_t part2(const std::vector<std::vector<std::string>> &digits)
{
  uint64_t sum = 0;

  for(const auto &row: digits)
  {
    std::string one;
    std::string four;
    std::string seven;
    std::string eight;
    std::vector<std::string> twoThreeFive;
    std::vector<std::string> zeroSixNine;


    for(int i = 0; i < 10; ++i)
    {
      if(row.at(i).size() == 2){
        one = row.at(i);
      }
      else if(row.at(i).size() == 3){
        seven = row.at(i);
      }
      else if(row.at(i).size() == 4){
        four = row.at(i);
      }
      else if(row.at(i).size() == 5){
        twoThreeFive.push_back(row.at(i));
      }
      else if(row.at(i).size() == 6){
        zeroSixNine.push_back(row.at(i));
      }
      else if(row.at(i).size() == 7){
        eight = row.at(i);
      }
    }

    const std::string two = findMagicNum(twoThreeFive, four);
    const std::string five = findMagicNum(twoThreeFive, one);
    const std::string three = twoThreeFive.at(0);

    const std::string six = findMagicNum(zeroSixNine, one);
    const std::string zero = findMagicNum(zeroSixNine, four);
    const std::string nine = zeroSixNine.at(0);

    const std::vector<std::string> rewired = {zero, one, two, three, four, five, six, seven, eight, nine};

    std::vector<uint64_t> fourDigits;
    for(int i = 10; i < 14 ; ++i)
    {
      fourDigits.push_back(findValue(row.at(i),rewired));
    }

    sum+= 
        fourDigits.at(0) * 1000 + 
        fourDigits.at(1) * 100 + 
        fourDigits.at(2) * 10 + 
        fourDigits.at(3);
  }

  return sum;
}
