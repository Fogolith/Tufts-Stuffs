#include "umsegment.h"
#include "seq.h"
#include "mem.h"
#include "assert.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define T Umsegment_T

/* The key constraint here is that I want Umsegment_of_id to be fast.
   For this reason I manage my own memory and use an unsafe C array.
   By contrast, I don't care about the cost of inactivate and deactivate,
   since whatever I do will be dwarfed by the cost of malloc() and free().
   For that reason I'm content with the greater convenience and poorer
   performance of Hanson's Seq_T to keep track of inactivated id's that
   can be used to satisfy future activation requests. 
*/

struct Umsegment_Map { // finite map from IDs to UM segments
  unsigned num_segments;
  T *segments;       // array of num_segments pointers (element -1 is length)
  unsigned num_used; // number larger than any id ever used but <= num_segments
  Seq_T free_ids;    // ids available for reuse; element is an id, not a pointer
};
    // Invariant: an ID 'i' is inactive if and only if 'i >= num_used' or 
    // 'i' appears as an element of 'free_ids'.
    //
    // Invariant: the finite mapping consist of the set of ordered pairs
    // '(i, segments[i])', where 'i' is an active ID.  Inactive IDs never appear
    // in the domain of the finite map.
    //
    // Invariant: if 'i' is active than segments[i] is a valid, non-NULL
    // pointer to a UM segment whose length in bytes is segments[i][-1]
    //
    // Invariant (to help detect errors only): if 'i < num_segments' and 'i'
    // is inactive, then 'segments[i] == NULL'.


Umsegment_Map Umsegment_newmap(void) {
  Umsegment_Map map;
  NEW0(map);
  map->num_segments = 20;
  map->segments = CALLOC(map->num_segments, sizeof(*map->segments));
  map->segments[0] = (T)~(uintptr_t)NULL; // marks segment 0 as in use
  map->num_used = 1; // segments[0] is used
  map->free_ids = Seq_new(10);
  return map;
}

void Umsegment_freemap(Umsegment_Map *mapp) {
  Umsegment_Map map = *mapp;
  assert(map->num_segments > 0);
  for (unsigned id = 1; id < map->num_segments; id++)
    if (map->segments[id])
      free(map->segments[id] - 1);
  FREE(map->segments);
  Seq_free(&map->free_ids);
  FREE(*mapp);
}

static Umsegment_Id getid(Umsegment_Map map) { 
  /* get an unused id, growing the segment list if necessary */
  if (Seq_length(map->free_ids) > 0) {
    return (Umsegment_Id)(uintptr_t)Seq_remlo(map->free_ids);
  } else if (map->num_used < map->num_segments) {
    return map->num_used++;
  } else {
    int old_num = map->num_segments;
    int new_num = old_num * 13 / 10;  // grow by 30% at overflow
    map->num_segments = new_num;
    RESIZE(map->segments, new_num * sizeof(*map->segments));
    T *segments = map->segments;
    for (int i = old_num; i < new_num; i++)
      segments[i] = NULL;
    return map->num_used++;
  }
}

static void putid(Umsegment_Map map, Umsegment_Id id) {
  Seq_addlo(map->free_ids, (void *)(uintptr_t)id);
}

Umsegment_Id Umsegment_new(Umsegment_Map map, unsigned words) {
  Umsegment_Id id = getid(map);
  T *segments = map->segments;
  segments[id] = CALLOC(words+1, sizeof(*segments[id]));
  segments[id][0] = 4 * (words+1);
  segments[id]++;
  return id;
}
  
inline T Umsegment_of_id(Umsegment_Map map, Umsegment_Id id) {
  return map->segments[id];
}

void Umsegment_inactivate(Umsegment_Map map, Umsegment_Id id) {
  map->segments[id]--;
  FREE(map->segments[id]);
  putid(map, id);
}
