#include <iostream>
#include <vector>

/* const int MIN_X = 20; */
/* const int MAX_X = 30; */
/* const int MIN_Y = -10; */
/* const int MAX_Y = -5; */

const int MIN_X = 248;
const int MAX_X = 285;
const int MIN_Y = -85;
const int MAX_Y = -56;

bool hit(int x, int y)
{
  int x_pos = 0;
  int y_pos = 0;
  int x_v = x;
  int y_v = y;

  while(x_pos < MAX_X && y_pos > MIN_Y)
  {
    x_pos+= x_v;
    y_pos+= y_v;

    if(x_pos >= MIN_X && x_pos <= MAX_X && y_pos >= MIN_Y && y_pos <= MAX_Y)
    {
      return true;
    }

    if(x_v > 0)
      x_v--;
    y_v--;
  }

  return false;
}

int main()
{
  uint64_t sum = 0;
  for(int x_vel = 0; x_vel < MAX_X+1; x_vel++)
  {
    for(int y_vel = abs(MIN_Y-1); y_vel > MIN_Y-1; --y_vel)
    {
      if(hit(x_vel, y_vel))
        sum++;
    }
  }
  std::cout << "sum of hits: " << sum << "\n";
}
