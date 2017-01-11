#include <vector>
#include <iostream>
#include <cstdint>
#include <algorithm>
#include "chunks.h"


#include <vector>
#include <iostream>
 
int main()
{

  std::vector<uint16_t> v_us { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

  //                                    ,-- wrapped container
  //                                    |
  cpppc::chunks<2, uint16_t, std::vector<uint16_t>> v_chunks(v_us);
  //             |      |
  //             |      '-- element type
  //             |
  //             '-- maximum size of a
  //                 single chunk in bytes

  // Iterate chunks:
  auto first_chunk = v_chunks.begin();

  for(auto it = first_chunk; it != v_chunks.end(); ++it)
  {
      std::cout << *it << '\n';
  }

//  for_each(v_chunks.begin(), v_chunks.end(), [](uint16_t & i){
//      std::cout << i << '\n';
//  });


  auto chunk_size  = std::distance(v_chunks.begin(), v_chunks.end());
                     // --> 128/(16/8) = 64
  std::cout << "Current chunks: " << chunk_size << '\n';

  // Iterators on elements in a chunk:
//  uint16_t first_chunk_elem = *first_chunk.begin();
//  uint16_t third_chunk_elem = first_chunk[2];
//  
//  // Pointer to data in second chunk:
//  uint16_t chunk_1_data = v_chunks[1].data();
//  // Pointer to data in third chunk (= end pointer of data in second chunk):
//  uint16_t chunk_2_data = v_chunks[2].data();

}
