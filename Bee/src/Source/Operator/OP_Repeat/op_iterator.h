#pragma once

namespace op
{
	class Iterator
	{
	public:
		Iterator() { this->itr = 0; }
		Iterator(size_t itr) { this->itr = itr; }

		inline void operator=(size_t itr) { this->itr = itr; }
		inline void operator+=(size_t itr) { this->itr += itr; }
		inline size_t operator+(size_t itr) { return this->itr + itr; }
		inline void operator++() { this->itr++; }

		inline bool operator>=(Iterator itr) { return this->itr >= itr.itr; }
		inline bool operator>(Iterator itr)  { return this->itr > itr.itr; }
		inline bool operator<=(Iterator itr) { return this->itr <= itr.itr; }
		inline bool operator<(Iterator itr)  { return this->itr < itr.itr; }
		inline bool operator==(Iterator itr) { return this->itr == itr.itr; }

		size_t itr;
	};
}