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

void moveScanner(const Scanner &s1,
                  Scanner &s2,
                  const std::pair<int, int> &p1,
                  const std::pair<int, int> &p2
                  )
{
  // get target coordinates
  const int xm = s1.beacons.at(p1.first).x - s2.beacons.at(p2.first).x;
  const int ym = s1.beacons.at(p1.first).y - s2.beacons.at(p2.first).y;
  const int zm = s1.beacons.at(p1.first).z - s2.beacons.at(p2.first).z;

  for(auto &b : s2.beacons)
  {
    b.x += xm;
    b.y += ym;
    b.z += zm;
  }
}

bool pointsMatch(
    const Scanner &s1,
    const Scanner &s2,
    const std::pair<int, int> &p1,
    const std::pair<int, int> &p2)
{
  if(s1.beacons.at(p1.first).x == s2.beacons.at(p2.first).x &&
     s1.beacons.at(p1.first).y == s2.beacons.at(p2.first).y &&
     s1.beacons.at(p1.first).z == s2.beacons.at(p2.first).z)
  {
    if(s1.beacons.at(p1.second).x == s2.beacons.at(p2.second).x &&
       s1.beacons.at(p1.second).y == s2.beacons.at(p2.second).y &&
       s1.beacons.at(p1.second).z == s2.beacons.at(p2.second).z)
    {
      return true;
    }

  }

  return false;
}

void rotateAxis(Scanner &scan, const char axis)
{
  for(auto &b: scan.beacons)
  {
    if(axis == 'x')
    {
      int temp = b.y;
      b.y = b.z;
      b.z = temp;
      b.z *= -1;
    }
    if(axis == 'y')
    {
      int temp = b.x;
      b.x = b.z;
      b.z = temp;
      b.z *= -1;
    }

    if(axis == 'z')
    {
      int temp = b.x;
      b.x = b.y;
      b.y = temp;
      b.y *= -1;
    }
  }
}

int countOverlap(const Scanner &s1, const Scanner &s2)
{
  int sum = 0;
  for (const auto &b1 : s1.beacons) {
    for (const auto &b2 : s2.beacons) {
      if(b1.x == b2.x && b1.y == b2.y && b1.z == b2.z)
      {
        sum++;
      }
    }
  }
  return sum;
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
            std::cout << "distance between " << k << " and " << p << " scanner " << 0 << " is same as ";
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

  // check 16 axis
  for(int i = 0; i < 4; ++i){
    rotateAxis(scanners.at(1),'z');
    moveScanner(scanners.at(0),scanners.at(1),p1,p2);

    for(int i = 0; i < 4; ++i){
      rotateAxis(scanners.at(1),'x');
      moveScanner(scanners.at(0),scanners.at(1),p1,p2);

      // check if they align
      if(pointsMatch(scanners.at(0),scanners.at(1),p1,p2))
      {
          int sum = countOverlap(scanners.at(0), scanners.at(1));
          std::cout << "number of overlaps: " << sum << "\n";
      }
    }
  }

  // check 8 axis
  rotateAxis(scanners.at(1),'y');
  moveScanner(scanners.at(0),scanners.at(1),p1,p2);

  for(int i = 0; i < 4; ++i){
    rotateAxis(scanners.at(1),'x');
    moveScanner(scanners.at(0),scanners.at(1),p1,p2);

    // check if they align
    if(pointsMatch(scanners.at(0),scanners.at(1),p1,p2))
    {
        int sum = countOverlap(scanners.at(0), scanners.at(1));
        std::cout << "number of overlaps: " << sum << "\n";
    }
  }

  rotateAxis(scanners.at(1),'y');
  moveScanner(scanners.at(0),scanners.at(1),p1,p2);
  rotateAxis(scanners.at(1),'y');
  moveScanner(scanners.at(0),scanners.at(1),p1,p2);

  for(int i = 0; i < 4; ++i){
    rotateAxis(scanners.at(1),'x');
    moveScanner(scanners.at(0),scanners.at(1),p1,p2);

    // check if they align
    if(pointsMatch(scanners.at(0),scanners.at(1),p1,p2))
    {
        int sum = countOverlap(scanners.at(0), scanners.at(1));
        std::cout << "number of overlaps: " << sum << "\n";
    }
  }
}













