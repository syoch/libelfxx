#include <libelfxx/binary_reader.hpp>
#include <assert.h>

BinaryReader::BinaryReader(std::string fname)
    : st(fname, std::ios::binary), bits(ClassType::class32), endian(Endian::Big)
{
}
uint64_t BinaryReader::read_int(int size)
{
  assert(0 < size);
  assert(size <= 8);

  auto bytes = new uint8_t[size];
  st.read((char *)bytes, size);

  uint64_t ret = 0;
  if (endian == Endian::Big)
  {
    for (int i = 0; i < size; i++)
    {
      ret <<= 8;
      ret |= bytes[i];
    }
  }
  else if (endian == Endian::Little)
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
  return read_int(4);
}
uint32_t BinaryReader::read_half()
{
  return read_int(2);
}
uint64_t BinaryReader::read_plat_word()
{
  if (bits == ClassType::class32)
  {
    return read_int(4);
  }
  else if (bits == ClassType::class64)
  {
    return read_int(8);
  }
  else
  {
    assert(false);
  }
}
void BinaryReader::skip(int size)
{
  st.ignore(size);
}