#pragma once

#include <croaring/roaring.hh>

// template <typename T>

// class Bitmask : public roaring::Roaring64Map
// {
// public:
//   bool get(T id)
//   {
//     return Roaring64Map::contains(id);
//   }
//   void set(T id)
//   {
//     Roaring64Map::add(id);
//   }
// };

template <typename T>

class BufferedBitmask : public roaring::Roaring64Map
{
private:
  std::vector<T> buffer;

public:
  BufferedBitmask()
  {
    buffer.reserve(1024L*1024L);
  }

  void set(T id)
  {
    if (buffer.size() == buffer.capacity())
      flush();

    buffer.push_back(std::move(id));
  }

  bool get(T id)
  {
    if (buffer.size() != 0)
        flush();

    return roaring::Roaring64Map::contains(id);
  }

  void flush()
  {
    roaring::Roaring64Map::addMany(buffer.size(), buffer.data());
    buffer.clear();
  }
};
