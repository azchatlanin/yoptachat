#pragma once

#include <iostream>

namespace hack::iterators
{
  template<typename T>
  class sequence_ostream_iterator
  {
    using iterator_category = std::output_iterator_tag;
    using traits = std::char_traits<char>;
    using ostream_type = std::basic_ostream<char, traits>;

    private:
      std::basic_ostream<char, traits>* os_;
      std::string devider_ = ", ";
      std::size_t size_;

    public:
      sequence_ostream_iterator(std::size_t size, ostream_type& os) : os_ { &os }, size_ { size } { }

      auto& operator=(T const& item)
      {
        --size_;
        *os_ << item << (size_ != 0 ? devider_ : "");
        return *this;
      }

      auto& operator*()
      {
        return *this;
      }

      auto& operator++()
      {
        return *this;
      }
  };
}

