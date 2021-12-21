#include <iostream>
#include <fstream>
#include <vector>
#include <map>

const int P1=4;

/* const int P2=8; */
const int P2=10;

void part1();
int threeThrows(int &);

int main()
{
  part1();
}

void part1()
{
  int num_throws;
  int p1_pos = P1;
  int p1_score = 0;

  int p2_pos = P2;
  int p2_score = 0;

  while(true)
  {
    p1_pos+= threeThrows(num_throws);
    p1_pos = p1_pos % 10;
    if(p1_pos == 0)
    {
      /* p1_pos++; */
      p1_pos = 10;
    }
    p1_score+=p1_pos;

    if(p1_score >= 1000)
      break;

    p2_pos+= threeThrows(num_throws);
    p2_pos = p2_pos % 10;
    if(p2_pos == 0)
    {
      /* p2_pos++; */
      p2_pos = 10;
    }
    p2_score+=p2_pos;
    if(p2_score >= 1000)
      break;
  }

  std::cout << p1_score << std::endl;
  std::cout << p2_score << std::endl;
  std::cout << num_throws << std::endl;
  if(p1_score < p2_score)
  {
    std::cout << num_throws * p1_score << std::endl;
  }
  else
  {
    std::cout << num_throws * p2_score << std::endl;
  }
}

int threeThrows(int &num_throws)
{
  static int cube_position = 0;
  int move = 0;

  for(int i = 0; i < 3; ++i)
  {
    cube_position++;
    if(cube_position > 100)
    {
      cube_position = 1;
    }
    move+=cube_position;
    num_throws++;
  }

  return move;
}

// too high = 928620
