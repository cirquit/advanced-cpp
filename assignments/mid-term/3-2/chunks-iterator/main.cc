#include <vector>
#include <iostream>
#include <cstdint>
#include <algorithm>
#include "chunks.h"

#include <vector>
#include <iostream>
 
int main()
{
  using chunked_container = typename cpppc::chunks<2, uint16_t, std::vector<uint16_t>>;

  std::vector<uint16_t> v_us { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

  std::cout << "-- Creation: -- \n";
  chunked_container v_chunks(v_us);

  // Iterate chunks:
  auto first_chunk = v_chunks.begin();

  std::cout << "-- Iterating through with custom for: ";
  for(auto it = first_chunk; it != v_chunks.end(); ++it)
  {
      for (auto iit = (*it).begin(); iit != (*it).end(); ++iit)
      {
        std::cout << *iit << ' '; 
      }
  }
  std::cout << '\n';

  std::cout << "-- Iterating through with generic for_each: ";
  std::for_each(v_chunks.begin(), v_chunks.end(),
    [](chunked_container::chunk_t chunk)
    {
      std::for_each(chunk.begin(), chunk.end(),
        [](uint16_t v)
        {
          std::cout << v << ' ';
        });

      std::cout << "| ";
    });
  std::cout << '\n';

  auto chunk_size  = std::distance(v_chunks.begin(), v_chunks.end());
                     // --> 128/(16/8) = 64
  std::cout << "-- Chunks size: " << chunk_size << '\n';

  // Iterators on elements in a chunk:
  auto first_chunk_elem = first_chunk.begin();
  std::cout << "First element: " << *first_chunk_elem << '\n';

  uint16_t third_chunk_elem = first_chunk[2];
  std::cout << "Third element: " << third_chunk_elem << '\n';
  
  // Pointer to data in second chunk:
  uint16_t *chunk_1_data = v_chunks[1].data();
  std::cout << "Pointer to data in second chunk (should be the third element with chunksize 2): " << *chunk_1_data << '\n';

  // Pointer to data in third chunk (= end pointer of data in second chunk):
  uint16_t *chunk_2_data = v_chunks[2].data();
  std::cout << "Pointer to data in third chunk (should be the fifth element with chunksize 2): " << *chunk_2_data << '\n';

}
