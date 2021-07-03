#include <libelfxx/binary_reader.hpp>
#include <assert.h>

BinaryReader::BinaryReader(std::string fname)
    : st(fname, std::ios::binary), bits(Bits::CLASS32), endian(big)
{
}
uint64_t BinaryReader::read_int(int size)
{
  assert(0 < size);
  assert(size <= 8);

  auto bytes = new char[size];
  st.read(bytes, size);
  printf("%d\n", bytes[0]);
  uint64_t ret = 0;
  if (endian == big)
  {
    for (int i = 0; i < size; i++)
    {
      ret <<= 8;
      ret |= bytes[i];
    }
  }
  else if (endian == little)
  {
    for (int i = size - 1; i >= 0; i--)
    {
      ret <<= 8;
      ret |= bytes[i];
    }
  }
  return ret;
}
uint64_t BinaryReader::read_word()
{
  if (bits == CLASS32)
  {
    return read_int(4);
  }
  else if (bits == CLASS64)
  {
    return read_int(8);
  }
  else
  {
    assert(false);
  }
}
uint32_t BinaryReader::read_half()
{
  if (bits == CLASS32)
  {
    return read_int(2);
  }
  else if (bits == CLASS64)
  {
    return read_int(4);
  }
  else
  {
    assert(false);
  }
}