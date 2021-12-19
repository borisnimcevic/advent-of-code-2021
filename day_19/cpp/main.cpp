#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

/* const std::string inputFile = "../input/input.txt"; */
const std::string inputFile = "../input/test.txt";

struct Beacon
{
  bool counted = false;
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
      std::cout << "x: " << b.x << "| y: " << b.y << "| z: " << b.z << "| counted: " << b.counted;
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
}

void moveScanner(Scanner &scan, const int xm, const int  ym, const int zm)
{
  for(auto &b: scan.beacons)
  {
    b.x += xm;
    b.y += ym;
    b.z += zm;
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

  /* printScanners(scanners); */

  int xd,yd,zd =0;
  /* for(int k = 0; k < scanners.at(0).beacons.size() ; ++k) */
  for(int k = 0; k < 1; ++k)
  {
    //get distance
    /* for(int p = 0; p < scanners.at(0).beacons.size() ; ++p) */
    for(int p = k+1; p < 2; ++p)
    {
      xd = abs(scanners.at(0).beacons.at(k).x - scanners.at(0).beacons.at(p).x);
      yd = abs(scanners.at(0).beacons.at(k).y - scanners.at(0).beacons.at(p).y);
      zd = abs(scanners.at(0).beacons.at(k).z - scanners.at(0).beacons.at(p).z);


      //find match
      int xd2, yd2, zd2 =0;
      for(int i = 0; i < scanners.at(1).beacons.size() ; ++i)
      {
        for(int j = i+1; j < scanners.at(1).beacons.size() ; ++j)
        {
          xd2 = abs(scanners.at(1).beacons.at(i).x - scanners.at(1).beacons.at(j).x);
          yd2 = abs(scanners.at(1).beacons.at(i).y - scanners.at(1).beacons.at(j).y);
          zd2 = abs(scanners.at(1).beacons.at(i).z - scanners.at(1).beacons.at(j).z);

          if( xd == xd2 && yd == yd2 && zd == zd2)
          {
            std::cout << "distance between " << k << " and " << p << " scanner " << 0 << "\n";
            std::cout << "distance between " << i << " and " << j << " scanner " << 1 << "\n";
          }
        }
      }
    }
  }

  // align the pairs
  std::pair<std::pair<int, int>, std::pair<int, int>> points;
  std::pair<int, int> p1;
  std::pair<int, int> p2;
  p1.first = 0;
  p1.second = 1;
  p2.first = 3;
  p2.second = 8;
  points.first = p1;
  points.second = p2;

  // get target coordinates
  int xt = scanners.at(0).beacons.at(p1.first).x;
  int yt = scanners.at(0).beacons.at(p1.first).y;
  int zt = scanners.at(0).beacons.at(p1.first).z;

  // move the next scanner to match the point
  int xm = xt - scanners.at(1).beacons.at(p2.first).x;
  int ym = yt - scanners.at(1).beacons.at(p2.first).y;
  int zm = zt - scanners.at(1).beacons.at(p2.first).z;

  moveScanner(scanners.at(1), xm, ym, zm);

  // check if they align
  if(scanners.at(0).beacons.at(p1.first).x == scanners.at(1).beacons.at(p2.first).x &&
     scanners.at(0).beacons.at(p1.first).y == scanners.at(1).beacons.at(p2.first).y &&
     scanners.at(0).beacons.at(p1.first).z == scanners.at(1).beacons.at(p2.first).z
    )
  {
    std::cout << "first points match\n";
    if(scanners.at(0).beacons.at(p1.second).x == scanners.at(1).beacons.at(p2.second).x &&
       scanners.at(0).beacons.at(p1.second).y == scanners.at(1).beacons.at(p2.second).y &&
       scanners.at(0).beacons.at(p1.second).z == scanners.at(1).beacons.at(p2.second).z
      )
    {
      std::cout << "SECOND points match\n";
    }
  }

  /* rotateAxis(); // * 4 */
  /* swapAxis();   // * 6 */
}













