#include <initializer_list>
#include <iostream>
#include <string_view>
#include <type_traits>
#include <vector>

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
  const auto end = function.find(suffix, start);
  return function.substr(start, end - start);
}

template <typename T>
void print_type(std::string_view name) {
  std::cout << name << " : " << type_name<T>() << '\n';
}

template <typename T>
void template_by_value(T) {
  print_type<T>("template f(T) の T");
}

template <typename T>
void template_by_const_ref(const T&) {
  print_type<T>("template f(const T&) の T");
}

template <typename T>
void template_by_forwarding_ref(T&&) {
  print_type<T>("template f(T&&) の T");
}

template <typename T>
void template_initializer_list(std::initializer_list<T>) {
  print_type<T>("template f(initializer_list<T>) の T");
}

int test() {
  int x{0};
  int& y = x;
  ++x;
  std::cout << y << std::endl;

}

int main() {
  std::cout << "Item 2: auto の型推論を理解する\n\n";

  auto x = 27;
  const auto cx = x;
  const auto& rx = x;

  std::cout << "[1] auto はテンプレート型推論にかなり近い\n";
  print_type<decltype(x)>("auto x = 27");
  print_type<decltype(cx)>("const auto cx = x");
  print_type<decltype(rx)>("const auto& rx = x");
  template_by_value(27);
  template_by_value(x);
  template_by_const_ref(x);

  std::cout << "\n[2] auto&& は転送参照として振る舞う\n";
  auto&& uref1 = x;
  auto&& uref2 = cx;
  auto&& uref3 = 27;
  print_type<decltype(uref1)>("auto&& uref1 = x");
  print_type<decltype(uref2)>("auto&& uref2 = cx");
  print_type<decltype(uref3)>("auto&& uref3 = 27");
  template_by_forwarding_ref(x);
  template_by_forwarding_ref(cx);
  template_by_forwarding_ref(27);

  std::cout << "\n[3] 波括弧初期化だけは auto とテンプレート型推論で違う\n";
  auto x1 = 27;
  auto x2(27);
  auto x3 = {27};
  auto x4{27};
  auto xs = {11, 23, 9};
  print_type<decltype(x1)>("auto x1 = 27");
  print_type<decltype(x2)>("auto x2(27)");
  print_type<decltype(x3)>("auto x3 = {27}");
  print_type<decltype(x4)>("auto x4{27}");
  print_type<decltype(xs)>("auto xs = {11, 23, 9}");

  std::cout << "\n[4] テンプレートは波括弧だけでは T を推論しない\n";
  template_initializer_list({11, 23, 9});
  std::cout << "f({11, 23, 9}) は f(T) だとコンパイル不可\n";
  std::cout << "f(initializer_list<T>) なら T = int と推論できる\n";

  std::cout << "\n[5] 戻り型 auto とラムダ引数 auto はテンプレート型推論側\n";
  std::cout << "auto createInitList() { return {1, 2, 3}; } はコンパイル不可\n";
  std::cout << "[](const auto& v){}({1, 2, 3}) もコンパイル不可\n";

  std::vector<int> values{1, 2, 3};
  auto reset_values = [&values](const std::initializer_list<int> new_values) {
    values.assign(new_values.begin(), new_values.end());
  };
  reset_values({4, 5, 6});
  std::cout << "明示的に initializer_list<int> を受けるラムダなら代入できる: ";
  for (const int value : values) {
    std::cout << value << ' ';
  }
  std::cout << '\n';

  static_assert(std::is_same_v<decltype(x1), int>);
  static_assert(std::is_same_v<decltype(x3), std::initializer_list<int>>);
  static_assert(std::is_same_v<decltype(x4), int>);
  static_assert(std::is_same_v<decltype(uref1), int&>);
  static_assert(std::is_same_v<decltype(uref2), const int&>);
  static_assert(std::is_same_v<decltype(uref3), int&&>);
}
