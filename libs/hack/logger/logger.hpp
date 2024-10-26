#pragma once

#include <experimental/source_location>
#include <string>

#include "hack/utils/color.hpp"
#include "hack/concepts/concepts.hpp"
#include "hack/iterators/sequence_ostream_iterator.hpp"
#include "hack/iterators/associative_ostream_iterator.hpp"

namespace hack
{
  // Моя реализация логера. 
  // Просто по тому что к ней привык :)
  // Ибо думаю, что  логировать в консоль в web продакшене - так себе затея. А в деве, ну какая разница как я это для себя делаю.:)
  class log
  {
    public:
      log(std::string devider_ = ", ", std::experimental::source_location location_ = std::experimental::source_location::current()) : location { location_ }
      {
        this->devider = devider_;
      }

      log(log&) = delete;
      log(log&&) = delete;

    public:
      template<typename... Args>
      void operator() (const Args&... args)
      {
        count = sizeof...(Args);
        prepare(make_type_view, location);
        print(args...);
      }

    private:
      std::experimental::source_location location;
      inline static int count = 0;
      inline static std::string devider = " ";

    private:
      template<typename T, typename U>
      void prepare(T t, U u)
      {
        std::cout << t
                  << u.file_name() << ":" << utils::color::reset 
                  << utils::color::italic << utils::color::yellow << u.function_name() << "()" << utils::color::reset
                  << utils::color::bold << utils::color::blue << "[" << u.line() << "]" << utils::color::reset << ": ";
      }

      static void print() { std::cout << std::endl; }

      static std::ostream& make_type_view(std::ostream &os)
      {
        os << utils::color::bold << utils::color::green << "[ok]" << utils::color::reset << utils::color::green;
        return os;
      }

      template<typename T, typename... Args>
      static void print(const T& data, const Args&... args)
      {
        --count;
        print_t(data);
        print(args...);
      }

      template<concepts::is_string T>
      static void print_t(const T& data)
      {
        std::cout << data << (count != 0 ? devider : "");
      }

      template<std::integral T>
      static void print_t(const T& data)
      {
        std::cout << data << (count != 0 ? devider : "");
      }

      template<concepts::is_sequence_container T>
      static void print_t(const T& data)
      {
        std::cout << "{ ";
        std::copy(data.cbegin(), data.cend(), iterators::sequence_ostream_iterator<typename T::value_type>(data.size(), std::cout));
        std::cout << " }" << (count != 0 ? devider : "");
      }

      template<concepts::is_set T>
      static void print_t(const T& data)
      {
        std::cout << "{ ";
        std::copy(data.cbegin(), data.cend(), iterators::sequence_ostream_iterator<typename T::value_type>(data.size(), std::cout));
        std::cout << " }" << (count != 0 ? devider : "");
      }

      template<concepts::is_unordered_set T>
      static void print_t(const T& data)
      {
        std::cout << "{ ";
        std::copy(data.cbegin(), data.cend(), iterators::sequence_ostream_iterator<typename T::value_type>(data.size(), std::cout));
        std::cout << " }" << (count != 0 ? devider : "");
      }

      template<concepts::is_forward_list T>
      static void print_t(const T& data)
      {
        std::cout << "{ ";
        std::copy(data.cbegin(), data.cend(), iterators::sequence_ostream_iterator<typename T::value_type>(std::distance(data.cbegin(), data.cend()), std::cout));
        std::cout << " }" << (count != 0 ? devider : "");
      }
      
      template<concepts::is_map T>
      static void print_t(const T& data)
      {
        std::cout << "{";
        std::copy(data.begin(), data.cend(), iterators::associative_ostream_iterator<typename T::value_type>(data.size(), std::cout));
        std::cout << "}" << (count != 0 ? devider : "");
      }

      template<concepts::is_tuple T, typename std::size_t... idx>
      static void print_t(const T& data)
      {
        print_t(data, std::make_index_sequence<std::tuple_size<T>::value>{});
      }

      template<typename T, typename std::size_t... idx>
      static void print_t(const T& data, std::index_sequence<idx...>)
      {
        std::cout << "{ ";
        ((std::cout << std::get<idx>(data) << (idx != std::tuple_size<T>::value - 1 ? devider : "")), ...);
        std::cout << " }" << (count != 0 ? devider : "");
      }

      template<concepts::not_defined T>
      static void print_t(const T& data)
      {
        std::cout << data << (count != 0 ? devider : "");
      }

      friend class warn;
      friend class error;
  };

  class warn : public log
  {
    public:
      warn(std::string devider_ = ", ", std::experimental::source_location location_ = std::experimental::source_location::current()) : location { location_ }
      {
        this->devider = devider_;
      }

      warn(warn&) = delete;
      warn(warn&&) = delete;

    public:
      template<typename... Args>
      void operator() (const Args&... args)
      {
        prepare(make_type_view, location);
        count = sizeof...(Args);
        print(args...);
      }

    private:
      std::experimental::source_location location;

    private:
      static std::ostream& make_type_view(std::ostream &os)
      {
        os << utils::color::bold << utils::color::yellow << "[WARN]" << utils::color::reset << utils::color::yellow;
        return os;
      }
  };

  class error : public log
  {
    public:
      error(std::string devider_ = ", ", std::experimental::source_location location_ = std::experimental::source_location::current()) : location { location_ }
      {
        this->devider = devider_;
      }
      error(error&) = delete;
      error(error&&) = delete;

    public:
      template<typename... Args>
      void operator() (const Args&... args)
      {
        prepare(make_type_view, location);
        count = sizeof...(Args);
        print(args...);
      }

    private:
      std::experimental::source_location location;

    private:
      static std::ostream& make_type_view(std::ostream &os)
      {
        os << utils::color::bold <<  utils::color::red << "[ERROR]" << utils::color::reset << utils::color::red;
        return os;
      }
  };
}

