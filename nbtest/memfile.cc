#include <memfile.hh>

void nbtest::memfile::free() {
	if (this->loaded) {
		::free(this->contents);
		this->contents = nullptr;
		this->size = 0;
		this->loaded = false;
	}
}

bool nbtest::memfile::load(char *filename) {
	if (this->loaded) return 0;

	struct stat st;

	if (stat(filename, &st) != 0) {
		perror("could not get file info");
		return 0;
	}

	if (!S_ISREG(st.st_mode)) {
		fprintf(stderr, "%s is not a regular file\n", filename);
		return 0;
	}

	char *mem = (char *)malloc(st.st_size);
	if (!mem)
	{
		perror("could not allocate memory for file");
		return 0;
	}

	FILE *f = fopen(filename, "r");
	if (!f)
	{
		perror("could not open file for reading");
		::free(mem);
		return 0;
	}

	fread(mem, 1, st.st_size, f);
	fclose(f);

	this->contents = mem;
	this->size = st.st_size;
	this->loaded = true;

	return 1;
}
