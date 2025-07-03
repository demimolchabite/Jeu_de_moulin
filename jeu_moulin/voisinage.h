#ifndef VOISINAGE_H_INCLUDED
#define VOISINAGE_H_INCLUDED
#include  "alignement.h"


bool operator<(const Coord& lhs, const Coord& rhs);
bool operator==(const Coord& lhs, const Coord& rhs);
bool CasesVoisines(const Coord& c1, const Coord& c2);

#endif // VOISINAGE_H_INCLUDED
