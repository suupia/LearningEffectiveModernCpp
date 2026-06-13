#include <iostream>
#include <string_view>
#include <typeinfo>
#include <vector>

void PrintCompiler(){
    std::cout << "Compiler detected: ";

#if defined(__clang__)
    std::cout << "Clang/LLVM\n";
    std::cout << "Version: " << __clang_major__ << "." << __clang_minor__ << "." << __clang_patchlevel__ << "\n";

#elif defined(__GNUC__) || defined(__GNUG__)
    // Note: Clang also defines __GNUC__, so checking Clang first is necessary.
    std::cout << "GNU GCC\n";
    std::cout << "Version: " << __GNUC__ << "." << __GNUC_MINOR__ << "." << __GNUC_PATCHLEVEL__ << "\n";

#elif defined(_MSC_VER)
    std::cout << "Microsoft Visual Studio (MSVC)\n";
    std::cout << "Compiler Version Code: " << _MSC_VER << "\n";

#else
    std::cout << "Unknown Compiler\n";
#endif
}

// コンパイラによる診断情報
template<typename T>
class TD;

struct Widget {};

template<typename T>
void f(const T& param){
  using std::cout;
  cout << "T     = " << typeid(T).name() << '\n';
  cout << "param = " << typeid(param).name() << '\n';
}

std::vector<Widget> createVec(){
  return std::vector<Widget>(3);
}

int main() {
  std::cout << "item04_view_deduced_types.cpp" << std::endl;
  PrintCompiler(); 

  const int theAnswer = 42;
  auto x = theAnswer;
  auto y = &theAnswer;

  // わざコンパイルエラーさせることで、x, y の型を知ることができる
  // TD<decltype(x)> xType;
  // TD<decltype(y)> yType;

  // x と y の型を表示する
  std::cout << typeid(x).name() << '\n';
  std::cout << typeid(y).name() << '\n';

  const auto vw = createVec(); // factory 関数の戻り値で vw を初期化

  if(!vw.empty()){
    f(&vw[0]); // f を呼び出す
  }

  return 0;
}
