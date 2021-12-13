#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <math.h>
#include <string>
#include <map>

struct node{
  std::string name;
  std::vector<std::string> next;
  bool visited = false;
  int visits = 0;
};


void getData(std::vector<node> &);
void bothParts(std::vector<std::vector<int>> &);
uint64_t part1(std::vector<node> path, uint64_t score, const std::string point);
uint64_t part2(std::vector<node> path, uint64_t score, const std::string point, bool &repeat);

/* const std::string inputFile = "../input/input.txt"; */
const std::string inputFile = "../input/test1.txt";

int main()
{
  std::vector<node> path;
  /* getData(path); */
  /* std::cout << part1(path, 0, "start") << " <<<<< part1\n"; */

  path.clear();
  getData(path);
  bool repeat = false;
  std::cout << part2(path, 0, "start", repeat) << " <<<<< part2\n";
}

void printNode(const std::vector<node> &path)
{
  for(const auto &node : path)
  {
    std::cout << node.name << " {";
    for(const auto &point : node.next)
    {
      std::cout << " " << point;
    }
    std::cout << " }\n";
  }
}

int findNode(const std::string &name, const std::vector<node> &nodes)
{
  for(int i = 0; i < nodes.size(); ++i)
  {
    if(nodes.at(i).name == name)
    {
      return i;
    }
  }
  return -1;
}

void cleanNode(std::vector<node> &path)
{
  for(auto & node : path)
  {
    for(int i = 0; i < node.next.size(); ++i)
    {
      if(node.next.at(i) == node.name)
      {
        node.next.erase(node.next.begin() + i);
      }
    }
  }
}
void getData(std::vector<node> &path)
{
  std::ifstream file(inputFile);

  if(!file)
  {
    std::cerr<<"Cannot find the file."<< std::endl;
  }

  std::string tempName;
  std::string tempNext;

  while(file >> tempName)
  {
    node tempNode;
    file >> tempNext;
    const auto index = findNode(tempName, path);
    const auto in2 = findNode(tempNext,path);
    
    std::cout << tempName << " - " << tempNext << std::endl;

    if(index == -1)
    {
      tempNode.name = tempName;

      std::cout << "create " << tempName << std::endl;

      tempNode.next.push_back(tempNext);
      path.push_back(tempNode);

      std::cout << "add " << tempNext << " to " <<  tempName << std::endl;

      if(tempNext != "end" && tempName != "start" && tempNext != tempName)
      {
        if(in2 == -1)
        {
          tempNode.name = tempNext;
          std::cout << "create " << tempNext << std::endl;

          tempNode.next.push_back(tempName);
          path.push_back(tempNode);
          std::cout << "add " << tempName << " to " <<  tempNext << std::endl;
        }
        else
        {
          path.at(in2).next.push_back(tempName);
          std::cout << "add " << tempName << " to " <<  tempNext << std::endl;
        }
      }
    }
    else
    {
      path.at(index).next.push_back(tempNext);
      std::cout << "add " << tempNext << " to " <<  tempName << std::endl;

      if(tempNext != "end" && tempName != "start" && tempNext != tempName)
      {
        if(in2 == -1)
        {
          tempNode.name = tempNext;
          std::cout << "create " << tempNext << std::endl;

          tempNode.next.push_back(tempName);
          path.push_back(tempNode);
          std::cout << "add " << tempName << " to " <<  tempNext << std::endl;
        }
        else
        {
          path.at(in2).next.push_back(tempName);
          std::cout << "add " << tempName << " to " <<  tempNext << std::endl;
        }
      }
    }
  }

  cleanNode(path);
  std::cout << "=========\n";
  printNode(path);
}

/* uint64_t part1(std::vector<node> path, uint64_t score, const std::string point) */
/* { */

/*   std::cout << "node = " << point << "\n"; */

/*   if(point == "end") */
/*     return score+1; */

/*   const auto index = findNode(point, path); */
/*   if(index == -1) */
/*   { */
/*     return score; */
/*   } */
/*   else if(path.at(index).visited && path.at(index).name.at(0) >= 'a') */
/*   { */
    /* return score+1; */
/*     return score; */
/*   } */
/*   else */
/*   { */
/*     path.at(index).visited = true; */
    /* if(path.at(index).next.size() == 1) */
    /* { */
    /*   return score+1; */
    /* } */
/*     for(int i = 0; i < path.at(index).next.size(); ++ i) */
/*     { */
      /* if(path.at(index).next.at(i).visited && path.at(index).next.at(i).name.at(0) >= 'a') */
/*       score = part1(path, score, path.at(index).next.at(i)); */
/*     } */
/*   } */
/*   return score; */
/* } */

uint64_t part2(std::vector<node> path, uint64_t score, const std::string point, bool &repeat)
{

  /* std::cout << "node = " << point << "\n"; */

  if(point == "end")
  {
    repeat = false;
    return score+1;
  }

  const auto index = findNode(point, path);
  const bool letter = path.at(index).name.at(0) >= 'a';
  bool visit;
  if(repeat)
  {
    visit = path.at(index).visits > 0;
  }
  else
  {
    visit = path.at(index).visits > 1;
  }

  if(letter && visit)
  {
    /* if(repeat) */
    /* { */
    /*   repeat = false; */
    /*   return score+1; */
    /* } */
    /* else */
    /* { */
    /*   return score; */
    /* } */
    return score;
  }
  else
  {
    path.at(index).visits++;
    if(path.at(index).visits > 1)
      repeat = true;
    for(int i = 0; i < path.at(index).next.size(); ++ i)
    {
      score = part2(path, score, path.at(index).next.at(i), repeat);
    }
  }
  return score;
}
