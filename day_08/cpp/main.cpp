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
/* const std::string inputFile = "../input/igor.txt"; */
/* const std::string inputFile = "../input/input_bea.txt"; */
/* const std::string inputFile = "../input/test.txt"; */

int main()
{
  std::vector<std::vector<std::string>> digits;
  getData(digits);
  std::cout << part1(digits) <<  " <<<<< part1" << std::endl;
  std::cout << part2(digits) <<  " <<<<< part2" << std::endl;
}

void printInput(const std::vector<std::vector<std::string>> &digits)
{
  for(const auto &row : digits)
  {
    for(const auto &number : row)
    {
      std::cout << number << " ";
    }
    std::cout << "\n";
  }
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
  /* printInput(digits); */
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

uint64_t sumString(const std::string &s)
{
  uint64_t sum = 0;
  for(const auto &c : s)
  {
    sum+=c;
  }
  return sum;
}

/* std::string findMagicNum(std::vector<std::string> &mix, const std::string inputNum) */
/* { */
/*   uint32_t min = 99999; // some large value */
/*   uint32_t minIndex = 0; */
/*   for(int i = 0; i < mix.size(); ++i) */
/*   { */
/*     int sum = sumString(mix.at(i)); */
/*     for(auto charMix : mix.at(i))  */
/*     { */
/*       for(auto charIn : inputNum) */
/*       { */
/*         if(charIn == charMix) */
/*         { */
/*           sum -= charIn; */
/*           break; */
/*         } */
/*       } */
/*     } */
/*     if(sum < min) */
/*     { */
/*       min = sum; */
/*       minIndex = i; */
/*     } */
/*   } */

/*   std::string newNum = mix.at(minIndex); */
/*   mix.erase(mix.begin()+minIndex); */
/*   return newNum; */
/* } */

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

void removeNumber(std::vector<std::string> &quess, uint64_t num)
{
  uint64_t index = 0;
  for(int i = 0; i < quess.size(); ++i)
  {
    if(sumString(quess.at(i)) == num)
    {
      index = i;
    }
  }
  quess.erase(quess.begin() + index);
}

uint64_t part2(const std::vector<std::vector<std::string>> &digits)
{
  uint64_t sum = 0;
  std::vector<uint64_t> allNumbers;
  uint32_t line = 1;
  for(const auto &row: digits)
  {
    std::string one;
    std::string four;
    std::string seven;
    std::string eight;
    std::vector<std::string> twoThreeFive;
    std::vector<std::string> zeroSixNine;

    int ttf = 0;
    int zsn = 0;

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
        ttf++;
        twoThreeFive.push_back(row.at(i));
      }
      else if(row.at(i).size() == 6){
        zsn++;
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

    /* std::cout << "line : " << line << " "; */
    /* line++; */
    /* std::cout << "ttf: " << ttf << " "; */
    /* std::cout << "zsn: " << zsn << " "; */
    /* for(const auto a : fourDigits) */
    /* { */
    /*   std::cout << (int)a; */
    /* } */
    /* std::cout << std::endl; */

    allNumbers.push_back(
        fourDigits.at(0) * 1000 + 
        fourDigits.at(1) * 100 + 
        fourDigits.at(2) * 10 + 
        fourDigits.at(3) 
        );
    sum+= 
        fourDigits.at(0) * 1000 + 
        fourDigits.at(1) * 100 + 
        fourDigits.at(2) * 10 + 
        fourDigits.at(3);
    /* std::cout << "| sum = " << sum << "\n"; */
    /* std::cin.get(); */
  }

  /* for(const auto &num : allNumbers) */
  /* { */
  /*   sum += num; */
  /* } */
  return sum;
}
