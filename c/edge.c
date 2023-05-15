#include "edge.h"

#include <assert.h>

#include "cell.h"

Edge new_edge(Cell cell1, Cell cell2) {
    uint32_t h1 = cell_hash(cell1);
    uint32_t h2 = cell_hash(cell2);
    // NOTE: We always maintain the invariant that
    // `src_cell_hash < dst_cell_hash`, which allows us to have a unique hash
    // for a bidirectional connection, and it prevents self-linking.
    assert(h1 != h2);
    if (h1 < h2) {
        return (Edge){
            .src_cell_hash = h1,
            .dst_cell_hash = h2,
        };
    }
    return (Edge){
        .src_cell_hash = h2,
        .dst_cell_hash = h1,
    };
}

uint64_t hash(Edge edge) {
    uint64_t retval = ((uint64_t)edge.src_cell_hash) << 32;
    return retval | (uint64_t)edge.dst_cell_hash;
}
