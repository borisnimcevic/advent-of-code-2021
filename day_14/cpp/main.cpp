#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <math.h>
#include <string>
#include <map>

void part1();
void part2();
void part3();

const std::string inputFile = "../input/input.txt";
const uint32_t LOOP = 100;
/* const std::string inputFile = "../input/test.txt"; */
/* const uint32_t LOOP = 16; */

const int STEPS = 40;

std::map<std::string, uint64_t> gains;

int main()
{
  part3();
}

void part1()
{
  std::ifstream file(inputFile);

  if(!file)
  {
    std::cerr<<"Cannot find the file."<< std::endl;
  }

  std::string oldSequence;

  file >> oldSequence;

  std::array<std::string, 2> tempPair;
  std::vector<std::array<std::string, 2>> templates;

  for(int i = 0; i < LOOP; ++i)
  {
    file >> tempPair.at(0);
    file >> tempPair.at(1);
    templates.push_back(tempPair);
  }

  std::cout << "size of templastes " << templates.size() << std::endl;
  std::cout << "last : " << templates.back().at(0) << std::endl;

  std::string newSequence = oldSequence;

  for(int loop = 0; loop < 40; ++loop)
  {
    uint32_t counter = 0;
    for(int i = 0; i < oldSequence.size() - 1; ++i)
    {
      std::string twoChar = std::string() + oldSequence.at(i) + oldSequence.at(i+1);
      for(const auto &temp : templates)
      {
        if(temp.at(0) == twoChar)
        {
          counter++;
          newSequence.insert(i+counter, temp.at(1));
          break;
        }
      }
    }
    oldSequence = newSequence;
  }

  std::cout << "size of sequence " << oldSequence.size() << std::endl;

  std::map<char, uint32_t> match;
  for(const auto &letter : oldSequence)
  {
    match[letter]++;
  }

  uint64_t max = 0;
  uint64_t min = 99999999999;
  for(const auto a : match)
  {
    if(a.second > max)
      max = a.second;
    if(a.second < min)
      min = a.second;
  }

  std::cout << "min " << min << std::endl;
  std::cout << "max " << max << std::endl;

  std::cout << max - min << "\n";
}

struct Node
{
  Node(std::string n, std::string w) : name(n), weight(w) {}
  std::string name;
  std::string weight;
  Node *left;
  Node *right;
};


void explore(const Node *current,const uint8_t counter)
{
  gains[current->weight]++;
  if(counter+1 == STEPS)
    return;

  explore(current->right, counter+1);
  explore(current->left, counter+1);
}

void part2()
{
  std::ifstream file(inputFile);

  if(!file)
  {
    std::cerr<<"Cannot find the file."<< std::endl;
  }

  std::string oldSequence;
  file >> oldSequence;

  std::vector<Node> nodes;

  for(int i = 0; i < LOOP; ++i)
  {
    std::string name;
    std::string gain;
    file >> name;
    file >> gain;
    Node a(name, gain);
    nodes.push_back(a);
  }

  for(auto &looking : nodes)
  {
    const auto leftName = looking.name.at(0) + looking.weight;
    const auto rightName = looking.weight + looking.name.at(1);
    for(auto &target : nodes)
    {
      if(leftName == target.name)
        looking.left  = &target;
      if(rightName == target.name)
        looking.right  = &target;
    }
  }

  for(int i = 0; i < oldSequence.size() - 1; ++i)
  {
    const std::string currentName = std::string() + oldSequence.at(i) + oldSequence.at(i+1);
    for(auto &n : nodes)
    {
      if(currentName == n.name)
      {
        int counter = 0;
        explore(&n, counter);
        std::cout << "done with: " << i+1 << " iterrations.\n";
        break;
      }
    }
  }

  for(const auto c : oldSequence)
  {
    gains[std::string(1,c)]++;
  }

  for(const auto &g: gains)
  {
    std::cout << g.first << " : " << g.second << "\n";
  }

  std::vector<uint64_t> minMax;
  for(const auto &g: gains)
  {
    minMax.push_back(g.second);
  }

  std::sort(minMax.begin(), minMax.end());

  std::cout << minMax.back() - minMax.front() << std::endl;
}

struct Node2
{
  Node2(std::string n, std::string m)
  {
    name = n;
    left = name.front() + m;
    right =  m + name.back();
  }

  std::string name;
  std::string left;
  std::string right;
};

void part3()
{
  std::ifstream file(inputFile);

  if(!file)
  {
    std::cerr<<"Cannot find the file."<< std::endl;
  }

  std::string oldSequence;
  file >> oldSequence;

  std::vector<Node2> nodes;

  for(int i = 0; i < LOOP; ++i)
  {
    std::string name;
    std::string middle;
    file >> name;
    file >> middle;
    Node2 a(name, middle);
    nodes.push_back(a);
  }

  // init map
  std::map<std::string, uint64_t> pairCount;
  for(int i = 0; i < oldSequence.size() - 1; ++i)
  {
    std::string twoChar = std::string() + oldSequence.at(i) + oldSequence.at(i+1);
    pairCount[twoChar]++;
  }

  for(int i = 0; i < STEPS; ++i)
  {
    std::map<std::string, uint64_t> tempMap;
    for(const auto &p : pairCount)
    {
      for(const auto &n : nodes)
      {
        if(p.first == n.name)
        {
          tempMap[n.left]+=p.second;
          tempMap[n.right]+=p.second;
          break;
        }
      }
    }
    pairCount = tempMap;
  }


  std::map<char, uint64_t> letters;
  for(const auto &p : pairCount)
  {
    letters[p.first.front()] += p.second;
  }
  letters[oldSequence.back()]++;

  std::vector<uint64_t> minMax;
  for(const auto &l : letters)
  {
    minMax.push_back(l.second);
  }

  std::sort(minMax.begin(), minMax.end());

  std::cout << minMax.back() - minMax.front() << std::endl;
}
