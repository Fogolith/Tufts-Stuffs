#ifndef UMSEGMENT_INCLUDED
#define UMSEGMENT_INCLUDED

#include <stdint.h>

#define T Umsegment_T

typedef uint32_t *T;  // pointer to segment of n words; p[-1] = size in bytes
typedef uint32_t Umsegment_Id;

typedef struct Umsegment_Map *Umsegment_Map;
  /* In the world of ideas, a finite map from 32-bit Umsegment_Id's
     to Umsegment_T's.  ID's not in the map are deemed 'inactive' */

Umsegment_Map Umsegment_newmap (void); 
                          // create a fresh, empty map from Umsegment_Id to T
void          Umsegment_freemap(Umsegment_Map*); // free map and all its segments

Umsegment_Id  Umsegment_new  (Umsegment_Map map, unsigned words); // map segment
T             Umsegment_of_id(Umsegment_Map map, Umsegment_Id id);  // lookup segment
void          Umsegment_inactivate(Umsegment_Map map, Umsegment_Id id); // free segment

#undef T
#endif

