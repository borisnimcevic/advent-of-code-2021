#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <math.h>
#include <string>
#include <map>
#include <set>

void part1();
void part2();

const std::string inputFile = "../input/input.txt";
/* const std::string inputFile = "../input/test.txt"; */

const uint32_t INF = 10000;
std::vector<std::vector<uint32_t>> input;
std::vector<std::vector<uint32_t>> distances;

int main()
{
  part1();
  part2();
}


void printVec(const std::vector<uint32_t> &vec)
{
  for(auto a: vec)
  {
    printf("%3d",a);
  }
  std::cout << std::endl;
}

void printFeild(const std::vector<std::vector<uint32_t>> &field)
{
  for(const auto &r : field)
  {
    for(const auto &c :r)
    {
      printf("%3d",c);
    }
    std::cout << "\n";
  }
}


void dijkstra(const std::pair<uint32_t, uint32_t> &point)
{
  uint32_t const MAX_COL = input.at(0).size() -1;
  uint32_t const MAX_ROW = input.size() -1;

  std::set<std::pair<uint32_t,std::pair<uint32_t, uint32_t>>> extract_set;
  extract_set.insert(std::make_pair(0,point));

  while(!extract_set.empty())
  {
    const std::pair<uint32_t, std::pair<uint32_t,uint32_t>> temp = *(extract_set.begin());
    extract_set.erase(extract_set.begin());

    const std::pair<uint32_t,uint32_t> current_spot = temp.second;

    // find adjecent spots
    std::vector<std::pair<uint32_t,uint32_t>> adj;

    const uint32_t row = current_spot.first;
    const uint32_t col = current_spot.second;

    if(row > 0)
      adj.push_back(std::make_pair(row-1,col));
    if(col > 0)
      adj.push_back(std::make_pair(row,col-1));
    if(row < MAX_ROW)
      adj.push_back(std::make_pair(row+1,col));
    if(col < MAX_COL)
      adj.push_back(std::make_pair(row,col+1));

    for(auto i = adj.begin(); i!= adj.end(); ++i)
    {
      const uint32_t row_adj = i->first;
      const uint32_t col_adj = i->second;
      std::pair<uint32_t, uint32_t> node;
      node.first = row_adj;
      node.second = col_adj;
      uint32_t weight = input.at(row_adj).at(col_adj);

      if(distances.at(row_adj).at(col_adj) > distances.at(current_spot.first).at(current_spot.second) + weight)
      {
        if(distances.at(row_adj).at(col_adj) != INF)
        {
          extract_set.erase(extract_set.find(std::make_pair(distances.at(row_adj).at(col_adj), node)));
        }
        distances.at(row_adj).at(col_adj) = distances.at(current_spot.first).at(current_spot.second) + weight;
        extract_set.insert(std::make_pair(distances.at(row_adj).at(col_adj), node));
      }
    }
  }
  std::cout << "shortest : " << (int)distances.back().back() << "\n";
}

void part1()
{
  std::ifstream file(inputFile);

  if(!file)
  {
    std::cerr<<"Cannot find the file."<< std::endl;
  }

  // input values
  std::string temp;
  std::vector<uint32_t> row;
  std::vector<uint32_t> tempRow;

  // weights
  std::vector<uint32_t> row_dist;



  // middle
  while(file >> temp)
  {
    row.clear();
    row_dist.clear();

    for(auto num : temp)
    {
      row.push_back(num-'0');
      row_dist.push_back(INF);
    }
    input.push_back(row);
    distances.push_back(row_dist);
  }
  distances.at(0).at(0) = 0;

  std::pair<uint32_t,uint32_t> start;
  start.first = 0;
  start.second = 0;

  std::cout << "part1: \n";
  dijkstra(start);
}

void part2()
{
  uint32_t width = input.at(0).size();
  uint32_t height = input.size();
  
  for(int k = 0; k < 4; ++k)
  {
    for(int j = 0; j < height; ++j)
    {
      for(int i = 0; i < width; ++i)
      {
        uint32_t num = input.at(j).at(i+(k*width));
        num++;
        num %= 10;
        if(num == 0)
          num++;
        input.at(j).push_back(num);
      }
    }
  }

  width = input.at(0).size();

  for(int k = 0; k < 4; ++k)
  {
    for(int i = 0; i < height; i++)
    {
      std::vector<uint32_t> temp;
      for(const auto &a : input.at(i+(k*height)))
      {
        auto num = (a+1)%10;
        if(num == 0)
          num++;
        temp.push_back(num);
      }
      input.push_back(temp);
    }
  }

  distances.clear();

  for(const auto &row : input)
  {
    std::vector<uint32_t> temp_distance;
    for(const auto &col: row)
    {
      temp_distance.push_back(INF);
    }
    distances.push_back(temp_distance);
  }

  distances.at(0).at(0) = 0;

  std::pair<uint32_t,uint32_t> start;
  start.first = 0;
  start.second = 0;

  std::cout << "part2: \n";
  dijkstra(start);
}
