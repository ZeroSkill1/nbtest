#ifndef nblib_test_tests_hh
#define nblib_test_tests_hh

#include <testcfg.hh>
#include <cstddef>

#define TEST_DEF(x) \
	int x (int argc, char **argv, FILE *stdout_redir, FILE *stderr_redir)

namespace nbtest
{
	namespace tests
	{
		TEST_DEF(tindex);
		TEST_DEF(title_single);
	};

	static testcfg test_configs[2] =
	{
		{
			"tindex",
			"tests deserialization of a TIDX.",
			"<path to binary data file>",
			tests::tindex
		},
		{
			"title-single",
			"tests deserialization of a single TITL.",
			"<path to binary data file>",
			tests::title_single
		},
	};

	static constexpr const size_t tests_count = 2;
};

#undef TEST_DEF

#endif
