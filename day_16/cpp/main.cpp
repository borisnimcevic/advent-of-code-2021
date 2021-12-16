#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <math.h>
#include <string>
#include <map>
#include <set>
#include <bitset>

void part1(const std::string &input);

const std::string inputFile = "../input/input.txt";
/* const std::string inputFile = "../input/test.txt"; */

/* const std::string TEST = "D2FE28"; */
/* const std::string TEST = "38006F45291200"; */
/* const std::string TEST = "EE00D40C823060"; */
/* const std::string TEST = "8A004A801A8002F478"; */
/* const std::string TEST = "620080001611562C8802118E34"; */
/* const std::string TEST = "C0015000016115A2E0802F182340"; */
/* const std::string TEST = "A0016C880162017C3686B18A3D4780"; */
const std::string TEST = "60556F980272DCE609BC01300042622C428BC200DC128C50FCC0159E9DB9AEA86003430BE5EFA8DB0AC401A4CA4E8A3400E6CFF7518F51A554100180956198529B6A700965634F96C0B99DCF4A13DF6D200DCE801A497FF5BE5FFD6B99DE2B11250034C00F5003900B1270024009D610031400E70020C0093002980652700298051310030C00F50028802B2200809C00F999EF39C79C8800849D398CE4027CCECBDA25A00D4040198D31920C8002170DA37C660009B26EFCA204FDF10E7A85E402304E0E60066A200F4638311C440198A11B635180233023A0094C6186630C44017E500345310FF0A65B0273982C929EEC0000264180390661FC403006E2EC1D86A600F43285504CC02A9D64931293779335983D300568035200042A29C55886200FC6A8B31CE647880323E0068E6E175E9B85D72525B743005646DA57C007CE6634C354CC698689BDBF1005F7231A0FE002F91067EF2E40167B17B503E666693FD9848803106252DFAD40E63D42020041648F24460400D8ECE007CBF26F92B0949B275C9402794338B329F88DC97D608028D9982BF802327D4A9FC10B803F33BD804E7B5DDAA4356014A646D1079E8467EF702A573FAF335EB74906CF5F2ACA00B43E8A460086002A3277BA74911C9531F613009A5CCE7D8248065000402B92D47F14B97C723B953C7B22392788A7CD62C1EC00D14CC23F1D94A3D100A1C200F42A8C51A00010A847176380002110EA31C713004A366006A0200C47483109C0010F8C10AE13C9CA9BDE59080325A0068A6B4CF333949EE635B495003273F76E000BCA47E2331A9DE5D698272F722200DDE801F098EDAC7131DB58E24F5C5D300627122456E58D4C01091C7A283E00ACD34CB20426500BA7F1EBDBBD209FAC75F579ACEB3E5D8FD2DD4E300565EBEDD32AD6008CCE3A492F98E15CC013C0086A5A12E7C46761DBB8CDDBD8BE656780";

/* const std::string TEST = "C200B40A82"; */
/* const std::string TEST = "04005AC33890"; */
/* const std::string TEST = "9C0141080250320F1802104A08"; */
/* const std::string TEST = "CE00C43D881120"; */

int main()
{
  part1(TEST);
  /* part1("1"); */
}

void printBin(const std::vector<bool> &in)
{
  for(const auto &a: in)
  {
    if(a)
      std::cout << "1";
    else
      std::cout << "0";
  }
  std::cout << "\n";
}

bool isAllZero(const std::vector<bool> &in)
{
  for(const auto &a: in)
  {
    if(a)
      return false;
  }
  return true;
}

void part1(const std::string &input)
{
  // ===== read input start (backwards, it's easier later)
  std::vector<bool> msg;
  std::bitset<4> letter = 0;
  /* for(const auto &c : input) */
  for(int i = input.size()-1; i >= 0; --i)
  {
    if(input.at(i) <= '9')
      letter = input.at(i) - '0';
    else
      letter = input.at(i) - 'A' + 10;

    for(int j = 0; j < letter.size(); ++j)
    {
      if(letter[j])
        msg.push_back(true);
      else
        msg.push_back(false);
    }
  }

  /* printBin(msg); */

  // ===== read input end
  std::string equation = "";
  std::vector<std::string> temp_symbol;
  std::vector<int> literal_numbers;
  bool typeID;
  int operation = 0;
  int brace_counter = 0;
  int bitLen = 0;
  int subPacketLen = 0;
  int version_sum = 0;
  bool message_done = false;
  while(!message_done)
  {
    int version = 0;
    int type = 0;
    std::vector<int> nums;

    for(int i = 0; i < 3; ++i)
    {
      version <<=1;
      if(msg.back())
        version++;
      msg.pop_back();
    }

    /* std::cout << "version " << version << "\n"; */
    version_sum += version;

    for(int i = 0; i < 3; ++i)
    {
      type <<=1;
      if(msg.back())
        type++;
      msg.pop_back();
    }

    /* std::cout << "type " << type << "\n"; */

    if(type == 4)
    {
      int num_counter = 0;
      bool end_packet = false;
      while(!end_packet)
      {
        if(!msg.back())
          end_packet = true;

        msg.pop_back();

        bitLen--;

        int temp_num = 0;
        for(int i = 0; i < 4; ++i)
        {
          temp_num <<=1;
          if(msg.back())
            temp_num++;

          msg.pop_back();
          bitLen--;
        }

        nums.push_back(temp_num);
        num_counter++;
      }

      int literal_number = 0;
      for(int i = 0; i < nums.size(); ++i)
      {
        literal_number += nums.at(i) << ((nums.size() - i -1) * 4);
      }
      /* std::cout << "literal_number : " << literal_number << "\n"; */
      literal_numbers.push_back(literal_number);

      equation += std::to_string(literal_number);
      /* printBin(msg); */
      /* std::cout << "\n"; */
      subPacketLen--;
    }
    else
    {
      operation = type;
      typeID = msg.back();
      msg.pop_back();
      /* std::cout << "typeID " << typeID <<  "\n"; */
      if(typeID)
      {
        std::bitset<11> sub_packet;
        for(int i = 0; i < 11; ++i)
        {
          sub_packet[11 - 1 - i] = msg.back();
          msg.pop_back();
        }
        subPacketLen = (int)sub_packet.to_ulong();
        /* std::cout << "packet count : " << subPacketLen << "\n"; */
        /* std::cout << "\n"; */
      }
      else
      {
        // 15 bits
        std::bitset<15> bit_length;
        for(int i = 0; i < 15; ++i)
        {
          bit_length[15 - 1 - i] = msg.back();
          msg.pop_back();
        }
        /* std::cout << bit_length << "\n"; */
        bitLen = (int)bit_length.to_ulong();
        /* std::cout << "bit length : " << bitLen << "\n"; */
        /* printBin(msg); */
        /* std::cout << "\n"; */
      }
      equation += "(";
      ++brace_counter;
    }

    std::string temp_s = "";

    if(operation == 0)
    {
      temp_s += "+";
    }
    if(operation == 1)
    {
      temp_s += "*";
    }
    if(operation == 2)
    {
      temp_s += "min";
    }
    if(operation == 3)
    {
      temp_s += "max";
    }
    if(operation == 5)
    {
      temp_s += ">";
    }
    if(operation == 6)
    {
      temp_s += "<";
    }
    if(operation == 7)
    {
      temp_s += "==";
    }

    if(equation.back() == '(')
    {
      temp_symbol.push_back(temp_s);
    }
    else
    {
      equation+= temp_s;
    }

    if(subPacketLen == 0 && typeID)
    /* if(subPacketLen == 0) */
    {
      equation.pop_back();
      if(temp_symbol.size() > 0)
        temp_symbol.pop_back();
      equation += ")";
      --brace_counter;
    }

    if(bitLen == 0 && !typeID)
    /* if(bitLen == 0) */
    {
      equation.pop_back();
      if(temp_symbol.size() > 0)
        temp_symbol.pop_back();
      equation += ")";
      --brace_counter;
    }

    if(equation.back() == ')')
    {
      equation += temp_symbol.back();
      if(temp_symbol.size() > 0)
        temp_symbol.pop_back();
    }

    message_done = isAllZero(msg);
  }

  /* std::cout << version_sum << "\n"; */
  if(equation.back() != ')')
  {
    equation.pop_back();
  }
  for(int i = 0; i < brace_counter; ++i)
  {
    equation+=")";
  }
  std::cout << equation << "\n";

}
