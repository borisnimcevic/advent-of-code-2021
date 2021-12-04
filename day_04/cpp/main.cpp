#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

uint32_t part1();
uint32_t part2();

const std::string inputFile = "../input/input.txt";
/* const std::string inputFile = "../input/test.txt"; */

int main()
{
  std::cout << part1() <<  " <<<<< part1" << std::endl;
  /* std::cout << "part1: " << part1() << std::endl; */
  /* std::cout << "part2: " << part2() << std::endl; */
}

bool checkBingo(const std::vector<int32_t> &table){
  int32_t sumRows = 0;
  int32_t sumColums = 0;
  for(int i = 0; i < 5; i++)
  {
    for(int j=0; j < 5; j++)
    {
      sumRows += table[i*5+j];
      sumColums += table[i+j*5];
    }
    if(sumColums == -5 || sumRows == -5)
    {
      return true;
    }
    sumRows = 0;
    sumColums = 0;
  }
  return false;
}

uint32_t sumTable(const std::vector<int32_t> &table){
  uint32_t sum = 0;
  for(auto a : table)
  {
    if(a > 0)
      sum += a;
  }
  return sum;
}

void printTable(const std::vector<int32_t> &table){
  std::cout << "New Table:" << std::endl;
  for(int i = 0; i < 5; i++)
  {
    for(int j=0; j < 5; j++)
    {
      std::cout << table[i*5+j] << ", ";
    }
      std::cout << std::endl;
  }
}

uint32_t  part1()
{
  // ------ read bingo numbers
  std::ifstream file(inputFile);

  if(!file)
  {
    std::cerr<<"Cannot find the file."<< std::endl;
    return 0;
  }

  std::string temp;
  file >> temp;
  /* std::cout << temp << std::endl; */

  std::vector<uint32_t> bingoNumbers;

  std::stringstream ss(temp);

  for(int i; ss >> i;)
  {
    bingoNumbers.push_back(i);
    if(ss.peek() == ',')
    {
      ss.ignore();
    }
  }

  // ------ read the table
  uint32_t number;
  std::vector<int32_t> table;
  std::vector<std::vector<int32_t>> tables;

  while(file >> number){
    table.push_back(number);

    for(int i = 1; i < 25; i++)
    {
      file >> number;
      table.push_back(number);
    }

    tables.push_back(table);
    /* printTable(table); */
    table.clear();
  }

  // ------ draw bingo numbers
  for(auto bingo : bingoNumbers){
    for(auto &tableNum : tables)
    {
      for(auto &index : tableNum)
      {
        if(index == bingo)
        {
          index = -1;
        }
      }
      if(checkBingo(tableNum))
      {
        return sumTable(tableNum) * bingo;
      }
    }
  }

  return 0;
}
