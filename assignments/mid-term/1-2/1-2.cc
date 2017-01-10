#include <iostream>

class SemanticSurprise {
public:

  SemanticSurprise()
  : _value(0) { }

  SemanticSurprise(int value)
  : _value(value) { }

  bool operator==(const SemanticSurprise & other) const {
    return _value == other._value;
  }

  bool operator!=(const SemanticSurprise & other) const {
    return !(*this == other);
  }

  int value() const {
    return _value;
  }


private:
  int _value;
};



void print_surprise(const SemanticSurprise & s) {
  std::cout << "SemanticSurprise.value: " << s.value() << std::endl;
}

int main(){
  
  SemanticSurprise s1;          // <-- Op?
  s1.value();                   // <-- value?

  SemanticSurprise s2(4);       // <-- Op?
  s2.value();                   // <-- value?

  SemanticSurprise s3 = s2;     // <-- Op?
  s3.value();                   // <-- value?

  SemanticSurprise s4(s3);      // <-- Op?
  s4 == s3;                     // <-- value?
  s2 != s3;                     // <-- value?

  const SemanticSurprise s5 = SemanticSurprise(10);
  print_surprise(SemanticSurprise(10));

  return 0;
}
