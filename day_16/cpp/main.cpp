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

std::vector<bool> getData(const std::string &input);
void part1(const std::string &input);
void part2(std::vector<bool> &msg);

const std::string inputFile = "../input/input.txt";
/* const std::string inputFile = "../input/test.txt"; */

/* const std::string TEST = "D2FE28"; */
/* const std::string TEST = "38006F45291200"; */
/* const std::string TEST = "EE00D40C823060"; */
/* const std::string TEST = "8A004A801A8002F478"; */
/* const std::string TEST = "620080001611562C8802118E34"; */
/* const std::string TEST = "C0015000016115A2E0802F182340"; */
/* const std::string TEST = "A0016C880162017C3686B18A3D4780"; */
/* const std::string TEST = "60556F980272DCE609BC01300042622C428BC200DC128C50FCC0159E9DB9AEA86003430BE5EFA8DB0AC401A4CA4E8A3400E6CFF7518F51A554100180956198529B6A700965634F96C0B99DCF4A13DF6D200DCE801A497FF5BE5FFD6B99DE2B11250034C00F5003900B1270024009D610031400E70020C0093002980652700298051310030C00F50028802B2200809C00F999EF39C79C8800849D398CE4027CCECBDA25A00D4040198D31920C8002170DA37C660009B26EFCA204FDF10E7A85E402304E0E60066A200F4638311C440198A11B635180233023A0094C6186630C44017E500345310FF0A65B0273982C929EEC0000264180390661FC403006E2EC1D86A600F43285504CC02A9D64931293779335983D300568035200042A29C55886200FC6A8B31CE647880323E0068E6E175E9B85D72525B743005646DA57C007CE6634C354CC698689BDBF1005F7231A0FE002F91067EF2E40167B17B503E666693FD9848803106252DFAD40E63D42020041648F24460400D8ECE007CBF26F92B0949B275C9402794338B329F88DC97D608028D9982BF802327D4A9FC10B803F33BD804E7B5DDAA4356014A646D1079E8467EF702A573FAF335EB74906CF5F2ACA00B43E8A460086002A3277BA74911C9531F613009A5CCE7D8248065000402B92D47F14B97C723B953C7B22392788A7CD62C1EC00D14CC23F1D94A3D100A1C200F42A8C51A00010A847176380002110EA31C713004A366006A0200C47483109C0010F8C10AE13C9CA9BDE59080325A0068A6B4CF333949EE635B495003273F76E000BCA47E2331A9DE5D698272F722200DDE801F098EDAC7131DB58E24F5C5D300627122456E58D4C01091C7A283E00ACD34CB20426500BA7F1EBDBBD209FAC75F579ACEB3E5D8FD2DD4E300565EBEDD32AD6008CCE3A492F98E15CC013C0086A5A12E7C46761DBB8CDDBD8BE656780"; */

const std::string TEST = "620D7B005DF2549DF6D51466E599E2BF1F60016A3F980293FFC16E802B325332544017CC951E3801A19A3C98A7FF5141004A48627F21A400C0C9344EBA4D9345D987A8393D43D000172329802F3F5DE753D56AB76009080350CE3B44810076274468946009E002AD2D9936CF8C4E2C472400732699E531EDDE0A4401F9CB9D7802F339DE253B00CCE77894EC084027D4EFFD006C00D50001098B708A340803118E0CC5C200A1E691E691E78EA719A642D400A913120098216D80292B08104DE598803A3B00465E7B8738812F3DC39C46965F82E60087802335CF4BFE219BA34CEC56C002EB9695BDAE573C1C87F2B49A3380273709D5327A1498C4F6968004EC3007E1844289240086C4D8D5174C01B8271CA2A880473F19F5024A5F1892EF4AA279007332980CA0090252919DEFA52978ED80804CA100622D463860200FC608FB0BC401888B09E2A1005B725FA25580213C392D69F9A1401891CD617EAF4A65F27BC5E6008580233405340D2BBD7B66A60094A2FE004D93F99B0CF5A52FF3994630086609A75B271DA457080307B005A68A6665F3F92E7A17010011966A350C92AA1CBD52A4E996293BEF5CBFC3480085994095007009A6A76DF136194E27CE34980212B0E6B3940B004C0010A8631E20D0803F0F21AC2020085B401694DA4491840D201237C0130004222BC3F8C2200DC7686B14A67432E0063801AC05C3080146005101362E0071010EC403E19801000340A801A002A118012C0200B006AC4015088018000B398019399C2FC432013E3003551006E304108AA000844718B51165F35FA89802F22D3801374CE3C3B2B8B5B7DDC11CC011C0090A6E92BF5226E92BF5327F3FD48750036898CC7DD9A14238DD373C6E70FBCA0096536673DC9C7770D98EE19A67308154B7BB799FC8CE61EE017CFDE2933FBE954C69864D1E5A1BCEC38C0179E5E98280";

/* const std::string TEST = "C200B40A82"; */
/* const std::string TEST = "04005AC33890"; */
/* const std::string TEST = "880086C3E88112"; */
/* const std::string TEST = "CE00C43D881120"; */
/* const std::string TEST = "D8005AC2A8F0"; */
/* const std::string TEST = "F600BC2D8F"; */
/* const std::string TEST = "9C005AC2F8F0"; */
/* const std::string TEST = "9C0141080250320F1802104A08"; */

int main()
{
  /* part1(TEST); */
  std::vector<bool> message = getData(TEST);
  part2(message);
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

std::vector<bool> getData(const std::string &input)
{
  std::vector<bool> msg;
  std::bitset<4> letter = 0;
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
  return msg;
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

    version_sum += version;

    for(int i = 0; i < 3; ++i)
    {
      type <<=1;
      if(msg.back())
        type++;
      msg.pop_back();
    }

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

      uint64_t literal_number = 0;
      for(int i = 0; i < nums.size(); ++i)
      {
        literal_number += nums.at(i) << ((nums.size() - i -1) * 4);
      }
      literal_numbers.push_back(literal_number);

      equation += std::to_string(literal_number);
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
        bitLen = (int)bit_length.to_ulong();
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



int get3bits(std::vector<bool> &msg)
{
  int num = 0;
  for(int i = 0; i < 3; ++i)
  {
    num <<=1;
    if(msg.back())
      num++;
    msg.pop_back();
  }
  return num;
}

void reduce(std::vector<int> &vec, const int res)
{
  for(int &v : vec)
  {
    v-=res;
  }
}

void printVec(std::vector<int> &vec)
{
  for(int &v : vec)
  {
    std::cout << v << ", ";
  }
  std::cout << "\n";
}

void printVec(std::vector<uint64_t> &vec)
{
  for(uint64_t &v : vec)
  {
    std::cout << v << ", ";
  }
  std::cout << "\n";
}

uint64_t parse(std::vector<bool> &msg,
    const int oper,
    std::vector<int> &pack_len,
    std::vector<int> &bin_len
    )
{
  std::vector<uint64_t> literal_numbers;

  /* std::cout << "pack_count: "; */
  /* printVec(pack_len); */
  /* std::cout << "bin_count: "; */
  /* printVec(bin_len); */
  /* std::cin.get(); */
  std::cout << "new\n";

  while(!isAllZero(msg) && (pack_len.back() > 0 || bin_len.back() > 0))
  {

    std::cout << "while:\n";
    std::cout << "pack_count: ";
    printVec(pack_len);
    std::cout << "bin_count: ";
    printVec(bin_len);
    std::cin.get();

    msg.pop_back();
    msg.pop_back();
    msg.pop_back();
    const int type = get3bits(msg);
    reduce(bin_len, 6);

    if(type == 4)
    {
        /* std::cout << "number start\n"; */
        /* std::cin.get(); */
        std::vector<uint64_t> temp_numbers;
        bool end_packet = false;
        while(!end_packet)
        {
          // check if it is the last number
          if(!msg.back())
            end_packet = true;
          msg.pop_back();
          reduce(bin_len, 1);

          int temp_num = 0;
          for(int i = 0; i < 4; ++i)
          {
            temp_num <<=1;
            if(msg.back())
              temp_num++;
            msg.pop_back();
            reduce(bin_len, 1);
          }
          temp_numbers.push_back(temp_num);
        }
        uint64_t literal_number = 0;
        for(int i = 0; i < temp_numbers.size(); ++i)
        {
          literal_number += temp_numbers.at(i) << ((temp_numbers.size() - i -1) * 4);
        }
        literal_numbers.push_back(literal_number);
        std::cout << "new number : " << literal_number << "\n";
        printVec(literal_numbers);
        reduce(pack_len, 1);
    }
    else
    {
        const bool typeID = msg.back();
        msg.pop_back();
        reduce(bin_len, 1);
        reduce(pack_len, 1);
        if(typeID)
        {
          std::bitset<11> sub_packet;
          for(int i = 0; i < 11; ++i)
          {
            sub_packet[11 - 1 - i] = msg.back();
            msg.pop_back();
            reduce(bin_len, 1);
          }
          pack_len.push_back((int)sub_packet.to_ulong());
          bin_len.push_back(0);
        }
        else
        {
          // 15 bits
          std::bitset<15> bit_length;
          for(int i = 0; i < 15; ++i)
          {
            bit_length[15 - 1 - i] = msg.back();
            msg.pop_back();
            reduce(bin_len, 1);
          }
          bin_len.push_back((int)bit_length.to_ulong());
          pack_len.push_back(0);
        }
        /* reduce(pack_len, 1); */
        std::cout << "diving deeper\n";
        std::cout << "pack_count: ";
        printVec(pack_len);
        std::cout << "bin_count: ";
        printVec(bin_len);
        std::cin.get();
        literal_numbers.push_back(parse(msg, type, pack_len, bin_len));
      }

      /* std::cin.get(); */
  }
  std::cout << "exit\n";
  std::cout << "pack_count: ";
  printVec(pack_len);
  std::cout << "bin_count: ";
  printVec(bin_len);
  std::cin.get();
  std::cout << "literals: ";
  printVec(literal_numbers);
  std::cout << "operator : " << oper << "\n";
  std::cin.get();
  pack_len.pop_back();
  bin_len.pop_back();

  // calculate
  if(oper == 0)
  {
    uint64_t sum = 0;
    for(const auto &a: literal_numbers)
    {
      sum+=a;
    }
    return sum;
  }
  if(oper == 1)
  {
    uint64_t prod = 1;
    for(const auto &a: literal_numbers)
    {
      prod*=a;
    }
    return prod;
  }
  if(oper == 2)
  {
    std::sort(literal_numbers.begin(), literal_numbers.end());
    return literal_numbers.front();
  }
  if(oper == 3)
  {
    std::sort(literal_numbers.begin(), literal_numbers.end());
    return literal_numbers.back();
  }
  if(oper == 5)
  {
    if(literal_numbers.at(0) > literal_numbers.at(1))
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
  if(oper == 6)
  {
    if(literal_numbers.at(0) < literal_numbers.at(1))
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
  if(oper == 7)
  {
    if(literal_numbers.at(0) == literal_numbers.at(1))
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }

  std::cout << "should not get here\n";
  return 0;
}

void part2(std::vector<bool> &msg)
{
  msg.pop_back();
  msg.pop_back();
  msg.pop_back();
  const int type = get3bits(msg);
  std::cout << "type : " << type << "\n";

  const bool typeID = msg.back();
  msg.pop_back();

  std::vector<int> bin_len;
  std::vector<int> pack_len;
  if(typeID)
  {
    std::bitset<11> sub_packet;
    for(int i = 0; i < 11; ++i)
    {
      sub_packet[11 - 1 - i] = msg.back();
      msg.pop_back();
    }
    pack_len.push_back((int)sub_packet.to_ulong());
    bin_len.push_back(0);
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
    bin_len.push_back((int)bit_length.to_ulong());
    pack_len.push_back(0);
  }
  uint64_t result;
  std::cout << "p : " << pack_len.front()<< " b: " << bin_len.front() << "\n";
  result = parse(msg, type, pack_len, bin_len);

  std::cout << result << "\n";
}
