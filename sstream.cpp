#include "sstream.hpp"
#include <cstdio>
#include <streambuf>

#define self * this

using namespace std;


vector_stream_buffer::vector_stream_buffer(size_t size) {
  buffer.reserve(size);
}

streamsize vector_stream_buffer::xsputn(const char_type * s, streamsize count) {
  return buffer.append(s, count), count;
}

vector_stream_buffer::int_type vector_stream_buffer::overflow([[maybe_unused]]int_type character) {
  return 1;
}

vector_output_stream::vector_output_stream(size_t size) : vector_stream_buffer(size), ostream(this) {

}

string vector_output_stream::str() {
  return buffer;
}

void vector_output_stream::clear() {
  buffer.clear();
}

vector_output_stream::operator string_type() const noexcept {
  return buffer.c_str();
}

#ifdef SSTREAM_SELFTEST
int main() {
  auto stream = vector_output_stream(256);
  puts(stream << "The CK owns about " << 10 << " monads.");
  return 0;
}
#endif
