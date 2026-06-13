#include <iostream>
#include <string_view>
#include <type_traits>

template <typename T>
constexpr std::string_view type_name() {
#if defined(__clang__)
  constexpr std::string_view function = __PRETTY_FUNCTION__;
  constexpr std::string_view prefix = "T = ";
  constexpr std::string_view suffix = "]";
#elif defined(__GNUC__)
  constexpr std::string_view function = __PRETTY_FUNCTION__;
  constexpr std::string_view prefix = "T = ";
  constexpr std::string_view suffix = ";";
#elif defined(_MSC_VER)
  constexpr std::string_view function = __FUNCSIG__;
  constexpr std::string_view prefix = "type_name<";
  constexpr std::string_view suffix = ">(void)";
#else
  return "unknown";
#endif

  const auto start = function.find(prefix) + prefix.size();
  const auto end = function.rfind(suffix);
  return function.substr(start, end - start);
}

template <typename T>
void print_type(std::string_view name) {
  std::cout << name << " : " << type_name<T>() << '\n';
}

template <typename T, typename Param>
void print_deduction(std::string_view call) {
  std::cout << call << '\n';
  print_type<T>("  T");
  print_type<Param>("  param");
}

template <typename T>
void by_ref(T& param) {
  print_deduction<T, decltype(param)>("f(T& param)");
}

template <typename T>
void by_const_ref(const T& param) {
  print_deduction<T, decltype(param)>("f(const T& param)");
}

template <typename T>
void by_pointer(T* param) {
  print_deduction<T, decltype(param)>("f(T* param)");
}

template <typename T>
void by_const_pointer(const T* param) {
  print_deduction<T, decltype(param)>("f(const T* param)");
}

template <typename T>
void by_const_top_level_pointer(T* const param) {
  print_deduction<T, decltype(param)>("f(T* const param)");
}

template <typename T>
void by_forwarding_ref(T&& param) {
  print_deduction<T, decltype(param)>("f(T&& param)");
}

template <typename T>
void by_value(T param) {
  print_deduction<T, decltype(param)>("f(T param)");
}

template <typename T>
void by_const_value(const T param) {
  print_deduction<T, decltype(param)>("f(const T param)");
}

void sample_function(int, double) {}

int main() {
  std::cout << "Item 1: テンプレートの型推論を理解する\n\n";

  int x = 27;
  const int cx = x;
  int& rx = x;
  const int& crx = x;

  int* px = &x;
  const int* pcx = &cx;
  int* const cpx = &x;
  const int* const cpcx = &cx;

  std::cout << "[1] ParamType が参照の場合\n";
  by_ref(x);
  by_ref(cx);
  by_ref(rx);
  by_ref(crx);
  std::cout << "f(T& param) に 42 のような右辺値は渡せない\n\n";

  by_const_ref(x);
  by_const_ref(cx);
  by_const_ref(rx);
  by_const_ref(crx);
  by_const_ref(42);
  by_const_ref(px);
  by_const_ref(pcx);
  by_const_ref(cpx);
  by_const_ref(cpcx);

  std::cout << "\n[2] ParamType がポインタの場合\n";
  by_pointer(px);
  by_pointer(pcx);
  by_pointer(cpx);
  by_pointer(cpcx);
  by_const_pointer(px);
  by_const_pointer(pcx);
  by_const_top_level_pointer(px);
  by_const_top_level_pointer(cpcx);
  std::cout << "f(T* param) に int や int& は渡せない\n";
  std::cout << "値として渡されるポインタ自身の top-level const は外れる\n";

  std::cout << "\n[3] ParamType が転送参照の場合\n";
  by_forwarding_ref(x);
  by_forwarding_ref(cx);
  by_forwarding_ref(rx);
  by_forwarding_ref(crx);
  by_forwarding_ref(42);
  by_forwarding_ref(px);
  by_forwarding_ref(cpcx);
  std::cout << "左辺値なら T 自体が左辺値参照、右辺値なら T は非参照型になる\n";

  std::cout << "\n[4] ParamType が値渡しの場合\n";
  by_value(x);
  by_value(cx);
  by_value(rx);
  by_value(crx);
  by_value(px);
  by_value(pcx);
  by_value(cpx);
  by_value(cpcx);
  by_const_value(x);
  by_const_value(cpcx);
  std::cout << "値渡しでは参照性と top-level const が落ちる\n";
  std::cout << "ただし const int* のような pointee 側の const は残る\n";

  std::cout << "\n[5] 配列実引数と関数実引数\n";
  const char name[] = "cpp";
  by_value(name);
  by_ref(name);
  by_value(sample_function);
  by_ref(sample_function);
  std::cout << "値渡しでは配列はポインタへ、関数は関数ポインタへ decay する\n";
  std::cout << "参照渡しでは配列長や関数型そのものが保たれる\n";

  static_assert(std::is_same_v<decltype(x), int>);
  static_assert(std::is_same_v<decltype(cx), const int>);
  static_assert(std::is_same_v<decltype(rx), int&>);
  static_assert(std::is_same_v<decltype(crx), const int&>);

  static_assert(std::is_same_v<decltype(px), int*>);
  static_assert(std::is_same_v<decltype(pcx), const int*>);
  static_assert(std::is_same_v<decltype(cpx), int* const>);
  static_assert(std::is_same_v<decltype(cpcx), const int* const>);

  static_assert(std::is_same_v<decltype(name), const char[4]>);
  static_assert(std::is_function_v<decltype(sample_function)>);
}

