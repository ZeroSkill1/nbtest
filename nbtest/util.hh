#ifndef nblib_test_util_hh
#define nblib_test_util_hh

#include <cstdio>
#include <nblib/nb.hh>

namespace nbtest
{
	namespace util
	{
		void hexprint(FILE *outf, void *mem, size_t size, bool upper = false, bool newline = false);
	};
};

#endif
