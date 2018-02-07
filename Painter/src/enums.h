#ifndef ENNUMS_H
#define ENNUMS_H

namespace Utils
{
	enum COLORS { RED, BLUE, GREEN, TOTAL };

	COLORS& operator++(COLORS& original);
}

#endif // ENNUMS_H

