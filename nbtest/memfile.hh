#ifndef nblib_test_memfile_hh
#define nblib_test_memfile_hh

#include <cstdio>
#include <cstdlib>

#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

namespace nbtest
{
	class memfile {
	public:
		char *contents;
		size_t size;
		bool loaded = false;

		void free();
		bool load(char *filename);
	};
};

#endif
