#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>

uint32_t part1();
uint64_t part2();

const std::string inputFile = "../input/input.txt";
/* const std::string inputFile = "../input/test.txt"; */

class Lenternfish{
  public:
    Lenternfish(uint32_t days){
      day = days;
    }

    bool update(){
      if(day == 0)
      {
        day = 6;
        return true;
      }
      --day;
      return false;
    }

    uint32_t status() const
    {
      return day;
    }

  private:
    uint32_t day;
};


int main()
{
  std::cout << part1() <<  " <<<<< part1 (the bad)" << std::endl;
  std::cout << part2() <<  " <<<<< part2 (and the good)" << std::endl;
}

void printDay(const std::vector<Lenternfish> &fish, const uint32_t day)
{
  std::cout << "After day " << day << ": ";
  for(const auto &f : fish)
  {
    std::cout << f.status() << ", ";
  }
  std::cout << std::endl;
}

void printFish(std::map<uint8_t, uint64_t> fish,const uint32_t day)
{
  std::cout << "After day " << day << "\n";
  for(int i = 0; i < 9; ++i)
  {
    std::cout << i << ": " << fish[i] << std::endl;
  }
}

uint64_t countFish(std::map<uint8_t, uint64_t> fish)
{
  uint64_t sum = 0;
  for(int i = 0; i < 9; ++i)
  {
    sum+=fish[i];
  }
  return sum;
}

uint32_t  part1()
{
  // ------ read file
  std::ifstream file(inputFile);

  if(!file)
  {
    std::cerr<<"Cannot find the file."<< std::endl;
    return false;
  }

  std::string temp;
  file >> temp;
  std::vector<Lenternfish> fish;

  std::stringstream ss(temp);
  for(int i; ss >> i;)
  {
    fish.push_back(i);
    if(ss.peek() == ',')
    {
      ss.ignore();
    }
  }

  // --- update fish count
  const auto DAYS = 80;
  for(int day = 1; day <= DAYS; ++day)
  {
    uint32_t newBabies = 0;
    for(auto &f : fish)
    {
      if(f.update())
      {
        ++newBabies;
      }
    }
    for(int i = 0; i < newBabies ; ++i)
    {
      fish.push_back(8);
    }
  }

  return fish.size();
}


uint64_t part2()
{
  // ------ read file
  std::ifstream file(inputFile);

  if(!file)
  {
    std::cerr<<"Cannot find the file."<< std::endl;
    return false;
  }

  std::string temp;
  file >> temp;
  std::map<uint8_t, uint64_t> fish;

  std::stringstream ss(temp);
  for(int i; ss >> i;)
  {
    fish[i]++;
    if(ss.peek() == ',')
    {
      ss.ignore();
    }
  }

  // --- update fish count
  const auto DAYS = 256;
  for(int day = 1; day <= DAYS; ++day)
  {
    uint64_t temp = fish[0];
    for(int i = 1; i < 9; ++i)
    {
      fish[i-1] = fish[i];
    }
    fish[6] += temp;
    fish[8] = temp;
  }

  return countFish(fish);
}
