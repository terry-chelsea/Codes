#include <iostream>
#include <sstream>

template <typename T, T min, T max>
struct Range {
  using Type = T;
  static constexpr T min_value = min;
  static constexpr T max_value = max;
  static_assert(static_cast<int>(min_value) <= static_cast<int>(max_value));
};

using BoolRange = Range<bool, false, true>;
#define ENUM_RANGE(E) Range<E, E##_MIN, E##_MAX>

enum TestType
{
    TestType_MIN,
    START,
    END,
    INVALID,
    TestType_MAX
};

template<TestType typeValue>
class Operator
{
    public:
        static int Invoke(int value)
        {
            std::cout << "output : " << value << ", type value : " << typeValue << std::endl;
            return value + 1;
        }
};

template <typename...>
struct TypeList {};

template <typename T1,
          T1 min1,
          T1 max1,
          int val1,
          template <T1, typename...> typename Op,
          typename... OpTypeArgs,
          typename... Args>
static auto LoopCompareInvoke1(const T1& v1, const TypeList<OpTypeArgs...>& op_type_args, Args&&... args) {
  static_assert(min1 <= max1);
  static_assert(min1 <= val1);

  if constexpr (val1 > static_cast<int>(max1)) {
    std::stringstream ss;
    ss << "unknown template argument value " << v1;
    throw std::runtime_error(ss.str());

    // For return type deduction only.
    return Op<static_cast<T1>(val1), OpTypeArgs...>::Invoke(std::forward<Args>(args)...);
  } else {
    if (val1 == v1) {
      return Op<static_cast<T1>(val1), OpTypeArgs...>::Invoke(std::forward<Args>(args)...);
    } else {
      return LoopCompareInvoke1<T1, min1, max1, val1 + 1, Op>(v1, op_type_args, std::forward<Args>(args)...);
    }
  }
}

template <typename Type1,
    template <typename Type1::Type, typename...> typename Op,
    typename... Args>
auto InvokeTemplate(const typename Type1::Type& v1, Args&&... args)
{
    using T1 = typename Type1::Type;
    return LoopCompareInvoke1<
            T1,
            Type1::min_value,
            Type1::max_value,
            Type1::min_value,
            Op> (v1, TypeList<>(), std::forward<Args>(args)...);
}

int main()
{
    int value = Operator<END>::Invoke(4);
    int ret = InvokeTemplate<ENUM_RANGE(TestType), Operator>(END, 1);
    std::cout << "return value : " << ret << std::endl;
    return 0;
}


