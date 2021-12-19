#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

/* const std::string inputFile = "../input/input.txt"; */
const std::string inputFile = "../input/test.txt";

struct Beacon
{
  int x,y,z;
};

struct Scanner
{
  int x,y,z = 0;
  std::vector<Beacon> beacons;
};

void part1();

int main()
{
  part1();
}

void printScanners(const std::vector<Scanner> &scanner)
{
  int counter = 0;
  for (const auto &scan : scanner) 
  {
    std::cout << "scanner " << counter++ << ":\n";
    for (const auto &b : scan.beacons) 
    {
      std::cout << "x: " << b.x << "| y: " << b.y << "| z: " << b.z;
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
}

void part1()
{
  // ------ read bingo numbers
  std::ifstream file(inputFile);

  if(!file)
  {
    std::cerr<<"Cannot find the file."<< std::endl;
  }

  std::string temp;

  Scanner scanner_temp;
  Beacon beacon_temp;
  std::vector<Scanner> scanners;

  while(file >> temp)
  {
    if(temp == "---")
    {
      std::cout << "pushed" << std::endl;
      scanners.push_back(scanner_temp);
      scanner_temp.beacons.clear();
    }
    else
    {
      beacon_temp.x = stoi(temp);
      file >> temp;
      beacon_temp.y = stoi(temp);
      file >> temp;
      beacon_temp.z = stoi(temp);
      scanner_temp.beacons.push_back(beacon_temp);
    }
  }
  printScanners(scanners);
}
