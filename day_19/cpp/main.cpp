#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <list>

const std::string inputFile = "../input/input.txt";
/* const std::string inputFile = "../input/test.txt"; */

struct Beacon
{
  /* bool counted = false; */
  int counted = 0;
  int x,y,z;
};

struct Scanner
{
  int x,y,z = 0;
  std::vector<Beacon> beacons;
};

Scanner composite_scan;

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

int markCounted(Scanner &s1, Scanner &s2)
{
  int sum = 0;
  for (auto &b1 : s1.beacons) {
    for (auto &b2 : s2.beacons) {
      if(b1.x == b2.x && b1.y == b2.y && b1.z == b2.z)
      {
        b1.counted++;
        /* b2.counted++; */
      }
    }
  }
  return sum;
}

int checkAllaxis(Scanner &s1, 
    Scanner &s2,
    const std::pair<std::pair<int, int>, std::pair<int, int>> &points)
{
  // check 16 axis
  Scanner st = s2;
  int max = 0;
  for(int j = 0; j < 4; ++j){
    rotateAxis(st,'z');
    moveScanner(s1,st,points.first,points.second);

    for(int i = 0; i < 4; ++i){
      rotateAxis(st,'x');
      moveScanner(s1,st,points.first,points.second);

      for(int k = 0; k < 4; ++k)
      {
        rotateAxis(st,'y');
        moveScanner(s1,st,points.first,points.second);

        // check if they align
        if(pointsMatch(s1,st,points.first,points.second))
        {
            int sum = countOverlap(s1,st);
            if(sum > max && sum > 11)
            {
              max = sum;
              s2 = st;
            }
        }
      }
    }
  }

  /* max = markCounted(s1,s2); */
  return max;
}

void incCounters(Scanner &s1, 
    Scanner &s2,
    const std::pair<std::pair<int, int>, std::pair<int, int>> &points)
{
  Scanner st = s2;
  int max = 0;
  for(int j = 0; j < 4; ++j){
    rotateAxis(st,'z');
    moveScanner(s1,st,points.first,points.second);

    for(int i = 0; i < 4; ++i){
      rotateAxis(st,'x');
      moveScanner(s1,st,points.first,points.second);

      for(int k = 0; k < 4; ++k)
      {
        rotateAxis(st,'y');
        moveScanner(s1,st,points.first,points.second);

        // check if they align
        if(pointsMatch(s1,st,points.first,points.second))
        {
            int sum = countOverlap(s1,st);
            if(sum > max && sum > 11)
            {
              max = sum;
              s2 = st;
            }
        }
      }
    }
  }
  markCounted(s1,s2);
}

void move(Scanner &small, Beacon &beac, Beacon &small_beac)
{
  const int xm = beac.x - small_beac.x;
  const int ym = beac.x - small_beac.y;
  const int zm = beac.x - small_beac.z;

  for(auto &b : small.beacons)
  {
    b.x += xm;
    b.y += ym;
    b.z += zm;
  }

  small.x += xm;
  small.y += ym;
  small.z += zm;
}

int countOverlap(const Scanner &small)
{
  int sum = 0;
  for (const auto &b1 : composite_scan.beacons) {
    for (const auto &b2 : small.beacons) {
      if(b1.x == b2.x && b1.y == b2.y && b1.z == b2.z)
      {
        sum++;
      }
    }
  }
  return sum;
}

void align(Scanner &small, Beacon &beac)
{
  /* Scanner st = s2; */
  for(auto &b: small.beacons)
  {
    for(int j = 0; j < 4; ++j)
    {
      rotateAxis(small,'z');
      move(small, beac, b);

      for(int i = 0; i < 4; ++i)
      {
        rotateAxis(small,'x');
        move(small, beac, b);

        for(int k = 0; k < 4; ++k)
        {
          rotateAxis(small,'y');
          move(small, beac, b);

          // check if they align
          int sum = countOverlap(small);
          if(sum > 11)
          {
            std::cout << "(" << small.x << "," << small.y << "," << small.z << ")\n";
          }
        }
      }
    }
  }
}

void compare(Scanner &comp, Scanner &small_scan)
{
  for(auto &b : comp.beacons)
  {
    align(small_scan, b);
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
  std::list<Scanner> scanners;

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
  composite_scan = scanners.front();
  scanners.pop_front();

  Scanner new_scan = scanners.front();
  compare(composite_scan, new_scan);

  return;
}
/*   for(int s1 = 0; s1 < scanners.size() ; ++s1) */
/*   { */
/*     for(int s2 = s1; s2 < scanners.size() ; ++s2) */
    /* for(int s2 = 0; s2 < scanners.size() ; ++s2) */
/*     { */
      /* if (s1 == s2) */
      /*   break; */
/*       std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> distance; */
/*       // get matching distances */
/*       for(int k = 0; k < scanners.at(s1).beacons.size() ; ++k) */
      /* for(int k = 0; k < 1; ++k) */
/*       { */
/*         //get distance */
/*         for(int p = k; p < scanners.at(s1).beacons.size() ; ++p) */
        /* for(int p = k+1; p < scanners.at(s1).beacons.size() ; ++p) */
        /* for(int p = 0; p < scanners.at(s1).beacons.size() ; ++p) */
/*         { */
/*           int const xd = abs(scanners.at(s1).beacons.at(k).x - scanners.at(s1).beacons.at(p).x); */
/*           int const yd = abs(scanners.at(s1).beacons.at(k).y - scanners.at(s1).beacons.at(p).y); */
/*           int const zd = abs(scanners.at(s1).beacons.at(k).z - scanners.at(s1).beacons.at(p).z); */


/*           //find match */
/*           for(int i = 0; i < scanners.at(s2).beacons.size() ; ++i) */
/*           { */
/*             for(int j = i; j < scanners.at(s2).beacons.size() ; ++j) */
            /* for(int j = i+1; j < scanners.at(s2).beacons.size() ; ++j) */
            /* for(int j = 0; j < scanners.at(s2).beacons.size() ; ++j) */
/*             { */
/*               int const xd2 = abs(scanners.at(s2).beacons.at(i).x -  */
/*                   scanners.at(s2).beacons.at(j).x); */

/*               int const yd2 = abs(scanners.at(s2).beacons.at(i).y -  */
/*                   scanners.at(s2).beacons.at(j).y); */

/*               int const zd2 = abs(scanners.at(s2).beacons.at(i).z -  */
/*                   scanners.at(s2).beacons.at(j).z); */

/*               if( xd == xd2 && yd == yd2 && zd == zd2) */
/*               { */
/*                 std::pair<std::pair<int, int>, std::pair<int, int>> points; */
/*                 std::pair<int, int> p1; */
/*                 std::pair<int, int> p2; */
/*                 p1.first = k; */
/*                 p1.second = p; */
/*                 p2.first = i; */
/*                 p2.second = j; */
/*                 points.first = p1; */
/*                 points.second = p2; */
/*                 distance.push_back(points); */
/*               } */
/*             } */
/*           } */
/*         } */
/*       } */

/*       int max = 0; */
/*       int index = 0; */
/*       for(int i = 0; i < distance.size(); ++i) */
/*       { */
/*         int over = checkAllaxis(scanners.at(s1), scanners.at(s2), distance.at(i)); */
/*         if(over > max) */
/*         { */
/*           max = over; */
/*           index = i; */
/*           std::cout << "Overlap between s" << s1<< " and s" << s2<< " is " << max << "\n"; */
        /*   std::cout << "Sensor " << s2 << " pos: x: " << scanners.at(s2).x */
        /*     << " y: " << scanners.at(s2).y << " z: " << scanners.at(s2).z << "\n"; */
/*         } */
/*       } */
/*       if(!distance.empty()) */
/*         incCounters(scanners.at(s1), scanners.at(s2), distance.at(index)); */
      /* if(s1 != s2) */
      /* overlap += max; */
/*     } */
/*     std::cout << std::endl; */
/*   } */
/*   int overlap = 0; */
/*   for(auto &sc: scanners) */
/*   { */
/*     for (auto &b : sc.beacons) { */
/*       overlap += b.counted; */
/*     } */
/*   } */

/*   int sumBeacons =0; */
/*   for(const auto &a: scanners) */
/*   { */
/*     sumBeacons += a.beacons.size(); */
/*   } */
/*   std::cout << "total beacons " << sumBeacons << "\n"; */
  /* std::cout << "total unique " << sumBeacons - (2*overlap) << "\n"; */
/*   std::cout << "total unique " << sumBeacons - overlap << "\n"; */
/* } */




/* // 362 too high, 302 too low */
/* // 310 is not */
/* // 311 is not */
/* // 312 is not */
/* // 328 is not */
/* // 333 is not */
/* // 334 is not */
/* // 335 is not */
/* // 376 is not obviously... */
