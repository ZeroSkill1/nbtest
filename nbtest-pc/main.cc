#include <cstdio>
#include <cstring>

#include <testcfg.hh>
#include <tests.hh>

void print_usage() {
	puts("available tests:");
	for (size_t i = 0; i < nbtest::tests_count; i++) {
		const nbtest::testcfg *cfg = &nbtest::test_configs[i];
		printf("%s %s | %s\n", cfg->name, cfg->arginfo, cfg->description);
	}
}

int main(int argc, char **argv) {
	if (argc < 2) {
		print_usage();
		return 1;
	}

	for (size_t i = 0; i < nbtest::tests_count; i++) {
		if (strcmp(argv[1], nbtest::test_configs[i].name) == 0)
			return nbtest::test_configs[i].run(argc - 2, argv + 2);
	}

	print_usage();

	return 1;
}
