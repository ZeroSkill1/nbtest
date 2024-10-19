#include <testcfg.hh>

int nbtest::testcfg::run(int argc, char **argv) {
	return this->handler(argc, argv, stdout, stderr);
}

int nbtest::testcfg::run_redir(int argc, char **argv,
	const char *redir_stdout_filename, const char *redir_stderr_filename) {
	FILE *stdout_redir = nullptr, *stderr_redir = nullptr;
	int rc = 1;

	if (!redir_stdout_filename)
		stdout_redir = stdout;
	else {
		if (!(stdout_redir = fopen(redir_stdout_filename, "w")))
			goto close_fds;
	}

	if (!redir_stderr_filename)
		stderr_redir = stdout;
	else {
		if (!(stderr_redir = fopen(redir_stderr_filename, "w")))
			goto close_fds;
	}

	rc = this->handler(argc, argv, stdout_redir, stderr_redir);
	
close_fds:
	if (stderr_redir && redir_stderr_filename) fclose(stderr_redir);
	if (stdout_redir && redir_stdout_filename) fclose(stdout_redir);
	
	return rc;
}
