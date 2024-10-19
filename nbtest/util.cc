#include <util.hh>

void nbtest::util::hexprint(FILE *outf, void *mem, size_t size, bool upper, bool newline)
{
	u8 *as_u8 = reinterpret_cast<u8 *>(mem);
	const char *fmt = upper ? "%02X" : "%02x";
	char tmp[3] = { 0 };

	for (size_t i = 0; i < size; i++)
	{
		snprintf(tmp, 3, fmt, as_u8[i]);
		fwrite(tmp, 1, 2, outf);
	}

	if (newline)
		fputc('\n', outf);
}
