#include "enums.h"

namespace Utils
{
	COLORS& operator++(COLORS& original)
	{
		original = static_cast<COLORS>(original + 1);
		return original;
	}
}