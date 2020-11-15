#ifndef BASIC_SSTREAM_HPP
#define BASIC_SSTREAM_HPP
/** @brief Implementation of `ostringstream` with pre-allocated size.
 *
 */
#include <cstdio>
#include <ostream>
#include <streambuf>

#define self * this

using namespace std;

class vector_stream_buffer : public streambuf {
public:
  explicit vector_stream_buffer(size_t size = 4096u );
protected:
  streamsize xsputn(const char_type * s, streamsize count) override;
  int_type overflow(int_type character) override;
private:
  friend class vector_output_stream;
  string buffer;
};

class vector_output_stream : protected vector_stream_buffer, public ostream {
private:
  using string_type = add_pointer_t<const ostream::char_type>;
public:
  explicit vector_output_stream(size_t size);
  string str();
  void clear();
  template <typename T>
  vector_output_stream & operator<<(T && value);
  explicit operator string_type() const noexcept;
};

template <typename T>
vector_output_stream & vector_output_stream::operator<<(T && value) {
  using base_reference = add_lvalue_reference_t<ostream>;
  return static_cast<base_reference>(self) << forward<T>(value), self;
}

#endif //BASIC_SSTREAM_HPP
