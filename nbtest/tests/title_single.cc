#include <tests.hh>

#include <cstdio>

#include <memfile.hh>
#include <nblib/nblib.hh>
#include <util.hh>

int nbtest::tests::title_single(int argc, char **argv,
					FILE *stdout_redir, FILE *stderr_redir) {

	if (argc < 1) {
		fprintf(stderr_redir, "invalid arguments\n");
		return 1;
	}

	nbtest::memfile titlef;
	nb::Title title;

	if (!titlef.load(argv[0]))
		return 1;

	nb::StatusCode code = nb::single_object::parse<nb::Title>(
		title,
		(u8 *)titlef.contents,
		titlef.size
	);

	fprintf(stdout_redir, "nb result code: %d\n", (int)code);

	if (code == nb::StatusCode::SUCCESS) {
		fprintf(stdout_redir, "seed: ");
		nbtest::util::hexprint(
			stdout_redir,
			title.seed,
			sizeof(title.seed),
			true,
			true
		);
		fprintf(stdout_redir, "id: %d\n", title.id);
		fprintf(stdout_redir, "size: %lld\n", title.size);
		fprintf(stdout_redir, "title id: %016llX\n", title.tid);
		fprintf(stdout_redir, "added: %lld, updated: %lld\n", title.added, title.updated);
		fprintf(stdout_redir, "dl count: %lld\n", title.dlCount);
		fprintf(stdout_redir, "flags: %llX\n", title.flags);
		fprintf(stdout_redir, "name: %s\n", title.name.c_str());
		fprintf(stdout_redir, "preferred alt: %s\n", title.has_alt() ? title.preferred_alt_name().c_str() : "N/A");
		fprintf(stdout_redir, "region: %s\n", title.region.c_str());
		fprintf(stdout_redir, "file name: %s\n", title.filename.c_str());
		fprintf(stdout_redir, "description: %s\n", title.desc.c_str());
		fprintf(stdout_redir, "product code: %s\n", title.prod.c_str());
		fprintf(stdout_redir, "version: %d\n", title.version);
		fprintf(stdout_redir, "content type: %d\n", title.contentType);
		fprintf(stdout_redir, "category: %d\n", title.cat);
		fprintf(stdout_redir, "subcategory: %d\n", title.subcat);
		fprintf(stdout_redir, "listed: %s\n", title.listed ? "yes" : "no");

		if (title.alt_names.size()) {
			fprintf(stdout_redir, "alternative names:\n");
			for (size_t i = 0; i < title.alt_names.size(); i++) {
				fprintf(stdout_redir, "\t- %s\n", title.alt_names[i].c_str());
			}
		}

		fprintf(stdout_redir, "checksum: ");
		nbtest::util::hexprint(
			stdout_redir,
			title.file_checksum,
			sizeof(title.file_checksum),
			true,
			true
		);
	}

	titlef.free();
	return 0;
}
