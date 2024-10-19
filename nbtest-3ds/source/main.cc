#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>

#include <nblib/nblib.hh>
#include <tests.hh>

enum {
	NBTEST_CTR_TINDEX = 0,
	NBTEST_CTR_TITLE_SINGLE,
};

static size_t sel = 0;
static size_t max = nbtest::tests_count;

void handle() {
	switch (sel) {
	case NBTEST_CTR_TINDEX:
		break;
	case NBTEST_CTR_TITLE_SINGLE:
		break;
	default:
		fprintf(stderr, "unknown test %d\n", sel);
	}
}

static void cycle_up() {
	consoleClear();
	if (sel + 1 > (max - 1)) {
		sel = 0;
		return;
	}
	
	++sel;
}

static void cycle_down() {
	consoleClear();
	if (sel == 0) {
		sel = max - 1;
		return;
	}

	--sel;
}

static void print_test() {
	printf("Selected test: " CONSOLE_GREEN "%s" CONSOLE_RESET "\n", nbtest::test_configs[sel].name);
	printf("Description:\n" CONSOLE_YELLOW "%s" CONSOLE_RESET "\n\n", nbtest::test_configs[sel].description);
	printf(
		"Controls:\n"
		CONSOLE_MAGENTA "Up/Down" CONSOLE_RESET ": cycle tests\n"
		CONSOLE_MAGENTA "A" CONSOLE_RESET ": Perform test\n"
		CONSOLE_MAGENTA "START" CONSOLE_RESET ": exit\n"
	);
}

static void perform_test() {
	int rc = -1;
	nbtest::testcfg *cfg = &nbtest::test_configs[sel];

	switch (sel) {
	case NBTEST_CTR_TINDEX:
		{
			char *arg = (char *)"/tindex.bin";
			rc = cfg->run_redir(1, &arg, "/tindex-stdout.txt", nullptr);
		}
		break;
	case NBTEST_CTR_TITLE_SINGLE:
		{
			char *arg = (char *)"/title.bin";
			rc = cfg->run(1, &arg);
		}
		break;
	}
	
	printf("Test " CONSOLE_GREEN "%s" CONSOLE_RESET " finished with retcode " CONSOLE_YELLOW "%d\n" CONSOLE_RESET, cfg->name, rc);
}

int main(int argc, char* argv[])
{
	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);

	print_test();

	while (aptMainLoop())
	{
		gspWaitForVBlank();
		gfxSwapBuffers();
		hidScanInput();

		u32 kDown = hidKeysDown();

		if (kDown & KEY_UP) {
			cycle_up();
			print_test();
			continue;
		}

		if (kDown & KEY_DOWN) {
			cycle_down();
			print_test();
			continue;
		}

		if (kDown & KEY_A) {
			perform_test();
			continue;
		}

		if (kDown & KEY_START)
			break;
	}

	gfxExit();
	return 0;
}
