#include "edge.h"

Edge new_edge(Cell cell1, Cell cell2) {
    uint32_t h1 = cell_hash(cell1);
    uint32_t h2 = cell_hash(cell2);
    // NOTE: We always maintain the invariant that
    // `src_cell_hash < dst_cell_hash`, which allows us to have a unique hash
    // for a bidirectional connection, and it prevents self-linking.
    if (h1 < h2) {
        return (Edge){
            .src_cell_hash = h1,
            .dst_cell_hash = h2,
        };
    } else if (h1 > h2) {
        return (Edge){
            .src_cell_hash = h2,
            .dst_cell_hash = h1,
        };
    }
    // Invalid, so avoid self-linking by returning a bogus link.
    return (Edge){
        .src_cell_hash = INT32_MAX,
        .dst_cell_hash = INT32_MIN,
    };
}

EdgeHash edge_hash(Edge edge) {
    EdgeHash retval = ((EdgeHash)edge.src_cell_hash) << 32;
    return retval | (EdgeHash)edge.dst_cell_hash;
}
