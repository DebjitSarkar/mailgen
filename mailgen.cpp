#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <iomanip>
#include <cassert>

using namespace std;

class Mail {
 public:
  Mail(string s) {
    cout << "vvvvv-INPUT-vvvvv" << endl;
    input = stringToVec(s);
    cout << "^^^^^-INPUT-^^^^^" << endl;
  }

  vector<string> stringToVec(string s) {
    vector<string> v;
    for (int i = 0; i < INPUT_SIZE; ++i) {
      v.push_back(s.substr(i, 1));
    }
    return v;
  }

  void rearrange() {
    cout << "vvvvv-REARRANGE-vvvvv" << endl;
    ;
    for (int i = 0; i < INPUT_SIZE; ++i) {
      rearr.push_back(input[rearrangeIndex[i]]);
    }
    cout << "^^^^^-REARRANGE-^^^^^" << endl;
  }

  void dearrange() {
    cout << "vvvvv-DEARRANGE-vvvvv" << endl;
    vector<string> dearranged(INPUT_SIZE);
    for (int i = 0; i < INPUT_SIZE; ++i) {
      dearranged[rearrangeIndex[i]] = rearr[i];
    }
    printVec(dearranged);
    cout << "^^^^^-DEARRANGE-^^^^^" << endl;
  }

  void printVec(vector<string> v) {
    int size = v.size();
    for (int i = 0; i < size / 2; ++i) {
      cout << v[i] << " ";
    }
    cout << endl;
    for (int i = size / 2; i < size; ++i) {
      cout << v[i] << " ";
    }
    cout << endl;
  }

  void strToBit() {
    cout << "vvvvv-STRTOBIT-vvvvv" << endl;
    for (int i = 0; i < INPUT_SIZE; ++i) {
      bits.push_back(bitMap[rearr[i]]);
    }
    cout << "^^^^^-STRTOBIT-^^^^^" << endl;
  }

  void packBits() {
    cout << "vvvvv-PACKBITS-vvvvv" << endl;
    string inter = "";
    for (int i = 0; i < INPUT_SIZE; ++i) {
      for (int j = 4; j > -1; --j) {
        inter.append(bits[i].substr(j, 1));
      }
    }

    int i = 0;
    while (i < 120) {
      string reverseMe = inter.substr(i, 8);
      string reversed = "";
      for (int j = 7; j > -1; --j) {
        reversed.append(reverseMe.substr(j, 1));
      }
      packed.push_back(reversed);

      i += 8;
    }
    cout << "^^^^^-PACKBITS-^^^^^" << endl;
  }

  int bitToDec(string s) {
    int size = s.length();
    int val = 0;
    int pos = 1;
    for (int i = size - 1; i > -1; --i) {
      val += stoi(s.substr(i, 1)) * pos;
      pos *= 2;
    }
    return val;
  }

  void checkSum() {
    cout << "vvvvv-CHECKSUM-vvvvv" << endl;
    vector<int> vals;
    for (int i = 0; i < packed.size(); ++i) {
      vals.push_back(bitToDec(packed[i]));
    }

    int sum = 0;
    for (int i = 1; i < vals.size(); ++i) {
      sum += vals[i] + i;
      sum &= 0xFF;
    }
    if (sum == vals[0])
      cout << "^^^^^-CHECKSUM-^^^^^" << endl;
    else
      cout << "CHECKSUM FAILED: " << sum << " vs " << vals[0] << endl;
  }

  void unpackBits() {
    cout << "vvvvv-UNPACKBITS-vvvvv" << endl;
    unpacked.push_back(packed[1].substr(4, 4));
    unpacked.push_back(packed[1].substr(1, 3));
    unpacked.push_back(packed[1].substr(0, 1) + packed[2].substr(5, 3));
    unpacked.push_back(flipLR(packed[3].substr(4, 4) + packed[2].substr(0, 5)));
    unpacked.push_back(flipLR(packed[4].substr(3, 5) + packed[3].substr(0, 4)));
    unpacked.push_back(packed[5].substr(3, 5) + packed[4].substr(0, 3));
    unpacked.push_back(packed[6].substr(7, 1) + packed[5].substr(0, 3));
    unpacked.push_back(packed[7].substr(7, 1) + packed[6].substr(0, 7));
    unpacked.push_back(packed[7].substr(1, 6));
    unpacked.push_back(packed[10].substr(1, 7) + packed[9] + packed[8] + packed[7].substr(0, 1));
    unpacked.push_back(packed[11].substr(2, 6) + packed[10].substr(0, 1));
    unpacked.push_back(packed[12].substr(3, 5) + packed[11].substr(0, 2));
    cout << "^^^^^-UNPACKBITS-^^^^^" << endl;
  }

  string flipLR(string lr) {
    string rl = "";
    for (int i = lr.length() - 1; i > -1; --i) {
      rl += lr[i];
    }
    return rl;
  }

  void doAll() {
    rearrange();  // dont rearrange for given example
    strToBit();
    packBits();
    printVec(packed);
    checkSum();
    unpackBits();
    for (int i = 0; i < unpacked.size(); ++i) {
      cout << unpackedKey[i] << " " << unpacked[i] << endl;
    }
  }

  vector<string> input;
  vector<string> rearr;
  vector<string> bits;
  vector<string> packed;
  vector<string> unpacked;
  vector<string> unpackedKey = {"Mail Type, must be 5 for WonderMail:",
                                "Mission Type:",
                                "Unknown, usually zero:",
                                "Client:",
                                "Target:",
                                "Find/Deliver, can set to 9 if N/A:",
                                "Reward:",
                                "Item Reward, can set to 9 if N/A:",
                                "Friend Area Reward:",
                                "Unknown, can set to 255:",
                                "Dungeon:",
                                "Floor:"};
  vector<int> rearrangeIndex = {12, 20, 9,  17, 4, 15, 1,  23, 3,  7,  19, 14,
                                0,  5,  21, 6,  8, 18, 11, 2,  10, 13, 22, 16};
  int INPUT_SIZE = 24;

  // # = m, % = f
  map<string, string> bitMap = {
      {"?", "00000"}, {"6", "00001"}, {"7", "00010"}, {"N", "00011"},
      {"P", "00100"}, {"R", "00101"}, {"8", "00110"}, {"9", "00111"},
      {"F", "01000"}, {"0", "01001"}, {"+", "01010"}, {".", "01011"},
      {"S", "01100"}, {"T", "01101"}, {"X", "01110"}, {"Y", "01111"},
      {"4", "10000"}, {"5", "10001"}, {"M", "10010"}, {"C", "10011"},
      {"H", "10100"}, {"J", "10101"}, {"-", "10110"}, {"K", "10111"},
      {"1", "11000"}, {"2", "11001"}, {"!", "11010"}, {"f", "11011"},
      {"3", "11100"}, {"Q", "11101"}, {"m", "11110"}, {"W", "11111"},
      {"#", "11110"}, {"%%", "11011"}};
};

int main() {
  string mail1 = "4?-W-#F??28RPF??C?70FF?W";
  mail1 = "4?9?H60??8P74R?!4665YK?1";
  Mail m1(mail1);
  m1.doAll();
}

/*
  string mail1 = "4X04N?7P6JP?1?3mW94?????";
  Mail m(mail1);
  // usually have to rearrange first...
  m.rearr = m.stringToVec(mail1);
  m.printVec(m.rearr);
  m.strToBit();
  m.printVec(m.bits);
  m.packBits();
  cout << "PACKED: " << endl;
  m.printVec(m.packed);
  m.checkSum();
  m.unpackBits();
  cout << "UNPACKED: " << endl;
  m.printVec(m.unpacked);
  for (int i = 0; i < m.unpacked.size(); ++i) {
    cout << m.unpackedKey[i] << " " << m.unpacked[i] << endl;
  }

  m.dearrange();

  Mail m2(mail2);
  //m2.rearrange();
  m2.rearr = m2.stringToVec(mail2);
  m2.doAll();

*/
