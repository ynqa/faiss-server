#include <cstdio>
#include <cstdlib>

#include <faiss/IndexBinaryFlat.h>
#include <faiss/hamming.h>

#include <string>
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    // dimension of the vectors to index
  int d = 64;

  // size of the database we plan to index
  size_t nb = 1000;

  // make the index object and train it
  faiss::IndexBinaryFlat index(d);

  srand(35);

  std::vector<uint8_t> database(nb * (d / 8));
  for (size_t i = 0; i < nb * (d / 8); i++) {
    database[i] = rand() % 0x100;
  }

  { // populating the database
    index.add(nb, database.data());
  }

  int nq = 200;

  { // searching the database

    std::vector<uint8_t> queries(nq * (d / 8));
    for (size_t i = 0; i < nq * (d / 8); i++) {
      queries[i] = rand() % 0x100;
    }

    int k = 5;
    std::vector<faiss::IndexBinary::idx_t> nns(k * nq);
    std::vector<int>                     dis(k * nq);

    index.search(nq, queries.data(), k, dis.data(), nns.data());

    for (size_t i = 0; i < nq; ++i) {
      faiss::HammingComputer8 hc(queries.data() + i * (d / 8), d / 8);
      hamdis_t dist_min = hc.hamming(database.data());
      for (size_t j = 1; j < nb; ++j) {
        hamdis_t dist = hc.hamming(database.data() + j * (d / 8));
        if (dist < dist_min) {
          dist_min = dist;
          cout << dist_min << endl;
        }
      }
    }
  }
    return 0;
}
