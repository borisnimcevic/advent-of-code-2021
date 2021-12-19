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

  s2.x += xm;
  s2.y += ym;
  s2.z += zm;
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

  if(axis == 'x')
  {
    // the axis of scanner
    int temp = scan.y;
    scan.y = scan.z;
    scan.z = temp;
    scan.z *= -1;
  }

  if(axis == 'y')
  {
    int temp = scan.x;
    scan.x = scan.z;
    scan.z = temp;
    scan.z *= -1;
  }

  if(axis == 'z')
  {
    int temp = scan.x;
    scan.x = scan.y;
    scan.y = temp;
    scan.y *= -1;
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


int checkAllaxis(const Scanner &s1, 
    Scanner &s2,
    const std::pair<std::pair<int, int>, std::pair<int, int>> &points)
{
  // check 16 axis
  int max = 0;
  for(int i = 0; i < 4; ++i){
    rotateAxis(s2,'z');
    moveScanner(s1,s2,points.first,points.second);

    for(int i = 0; i < 4; ++i){
      rotateAxis(s2,'x');
      moveScanner(s1,s2,points.first,points.second);

      // check if they align
      if(pointsMatch(s1,s2,points.first,points.second))
      {
          int sum = countOverlap(s1,s2);
          if(sum > max && sum > 11)
          {
            /* int tempx; */
            /* int tempy; */
            /* int tempz; */
            max = sum;
            return max;
          /* std::cout << "Align on " << max << " points. Sensor pos: x: " << s2.x */
          /*   << " y: " << s2.y << " z: " << s2.z << "\n"; */
          }
      }
    }
  }

  for(int i = 0; i < 4; ++i){
    rotateAxis(s2,'y');
    moveScanner(s1,s2,points.first,points.second);

    for(int i = 0; i < 4; ++i){
      rotateAxis(s2,'x');
      moveScanner(s1,s2,points.first,points.second);

      // check if they align
      if(pointsMatch(s1,s2,points.first,points.second))
      {
          int sum = countOverlap(s1,s2);
          if(sum > max && sum > 11)
          {
            max = sum;
            return max;
          }
      }
    }
  }
/*   // check 16 axis */
/*   int max = 0; */
/*   for(int i = 0; i < 4; ++i){ */
/*     rotateAxis(s2,'z'); */
/*     moveScanner(s1,s2,points.first,points.second); */

/*     for(int i = 0; i < 4; ++i){ */
/*       rotateAxis(s2,'x'); */
/*       moveScanner(s1,s2,points.first,points.second); */

/*       // check if they align */
/*       if(pointsMatch(s1,s2,points.first,points.second)) */
/*       { */
/*           int sum = countOverlap(s1,s2); */
/*           if(sum > max) */
/*           { */
/*             max = sum; */
          /* std::cout << "Align on " << max << " points. Sensor pos: x: " << s2.x */
            /* << " y: " << s2.y << " z: " << s2.z << "\n"; */
/*           } */
/*       } */
/*     } */
/*   } */

/*   for(int i = 0; i < 4; ++i){ */
/*     rotateAxis(s2,'y'); */
/*     moveScanner(s1,s2,points.first,points.second); */

/*     for(int i = 0; i < 4; ++i){ */
/*       rotateAxis(s2,'x'); */
/*       moveScanner(s1,s2,points.first,points.second); */

/*       // check if they align */
/*       if(pointsMatch(s1,s2,points.first,points.second)) */
/*       { */
/*           int sum = countOverlap(s1,s2); */
/*           if(sum > max) */
/*             max = sum; */
/*       } */
/*     } */
/*   } */

/*   // check 4 axis */
/*   rotateAxis(s2,'y'); */
/*   moveScanner(s1,s2,points.first,points.second); */

/*   for(int i = 0; i < 4; ++i){ */
/*     rotateAxis(s2,'x'); */
/*     moveScanner(s1,s2,points.first,points.second); */

/*     // check if they align */
/*     if(pointsMatch(s1,s2,points.first,points.second)) */
/*     { */
/*         int sum = countOverlap(s1,s2); */
/*         if(sum > max) */
/*           max = sum; */
/*     } */
/*   } */

/*   // check 4 axis */
/*   rotateAxis(s2,'y'); */
/*   moveScanner(s1,s2,points.first,points.second); */
/*   rotateAxis(s2,'y'); */
/*   moveScanner(s1,s2,points.first,points.second); */

/*   for(int i = 0; i < 4; ++i) */
/*   { */
/*     rotateAxis(s2,'x'); */
/*     moveScanner(s1,s2,points.first,points.second); */

/*     // check if they align */
/*     if(pointsMatch(s1,s2,points.first,points.second)) */
/*     { */
/*         int sum = countOverlap(s1,s2); */
/*         if(sum > max) */
/*           max = sum; */
/*     } */
/*   } */
  return max;
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
  // done reading data


  /* int s1 = 1; */
  /* int s2 = 4; */
  int overlap = 0;
  for(int s1 = 0; s1 < scanners.size() ; ++s1)
  {
    for(int s2 = s1 + 1; s2 < scanners.size() ; ++s2)
    {
      std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> distance;
      // get matching distances
      for(int k = 0; k < scanners.at(s1).beacons.size() ; ++k)
      /* for(int k = 0; k < 1; ++k) */
      {
        //get distance
        for(int p = k+1; p < scanners.at(s1).beacons.size() ; ++p)
        /* for(int p = k+1; p < 2; ++p) */
        {
          int const xd = abs(scanners.at(s1).beacons.at(k).x - scanners.at(s1).beacons.at(p).x);
          int const yd = abs(scanners.at(s1).beacons.at(k).y - scanners.at(s1).beacons.at(p).y);
          int const zd = abs(scanners.at(s1).beacons.at(k).z - scanners.at(s1).beacons.at(p).z);


          //find match
          for(int i = 0; i < scanners.at(s2).beacons.size() ; ++i)
          {
            for(int j = i+1; j < scanners.at(s2).beacons.size() ; ++j)
            {
              int const xd2 = abs(scanners.at(s2).beacons.at(i).x - 
                  scanners.at(s2).beacons.at(j).x);

              int const yd2 = abs(scanners.at(s2).beacons.at(i).y - 
                  scanners.at(s2).beacons.at(j).y);

              int const zd2 = abs(scanners.at(s2).beacons.at(i).z - 
                  scanners.at(s2).beacons.at(j).z);

              if( xd == xd2 && yd == yd2 && zd == zd2)
              {
                std::pair<std::pair<int, int>, std::pair<int, int>> points;
                std::pair<int, int> p1;
                std::pair<int, int> p2;
                p1.first = k;
                p1.second = p;
                p2.first = i;
                p2.second = j;
                points.first = p1;
                points.second = p2;
                distance.push_back(points);
                /* std::cout << "distance between " << k << " and " << p << " scanner " << s1 << " is same as "; */
                /* std::cout << "distance between " << i << " and " << j << " scanner " << s2 << "\n"; */
              }
            }
          }
        }
      }

      int max = 0;
      /* std::cout << distance.size() << "\n"; */
      for(int i = 0; i < distance.size(); ++i)
      {
        int over = checkAllaxis(scanners.at(s1), scanners.at(s2), distance.at(i));
        if(over > max)
        {
          max = over;
          std::cout << "Overlap between s" << s1<< " and s" << s2<< " is " << max << "\n";
          std::cout << "Sensor " << s2 << " pos: x: " << scanners.at(s2).x
            << " y: " << scanners.at(s2).y << " z: " << scanners.at(s2).z << "\n";
        }
      }

      /* if(max >= 12) */
        overlap += max;
      /* std::cout << "Overlap between s" << s1<< " and s" << s2<< " is " << max << "\n"; */
    }
    std::cout << std::endl;
  }

  int sumBeacons =0;
  for(const auto &a: scanners)
  {
    sumBeacons += a.beacons.size();
  }
  std::cout << "total beacons " << sumBeacons << "\n";
  std::cout << "total unique " << sumBeacons - (2*overlap) << "\n";
  /* std::cout << "total unique " << sumBeacons - (overlap) << "\n"; */
}




// 362 too high, 302 too low







