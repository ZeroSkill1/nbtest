#ifndef nblib_tests_testcfg_hh
#define nblib_tests_testcfg_hh

#include <functional>
#include <cstdio>

namespace nbtest
{
	using test_handler = std::function<int(int, char **, FILE *, FILE *)>;

	struct testcfg
	{
		const char *name;
		const char *description;
		const char *arginfo;
		test_handler handler;

		int run(int argc, char **argv);
		int run_redir(int argc, char **argv, const char *redir_stdout_filename, const char *redir_stderr_filename);
	};
};

#endif
