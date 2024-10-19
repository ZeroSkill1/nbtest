#include <tests.hh>

#include <cstdio>

#include <nblib/nblib.hh>
#include <memfile.hh>

int nbtest::tests::tindex(int argc, char **argv, FILE *stdout_redir, FILE *stderr_redir) {
	if (argc < 1) {
		fprintf(stderr_redir, "invalid arguments\n");
		return 1;
	}

	nbtest::memfile indexf;

	if (!indexf.load(argv[0]))
		return 1;

	nb::Index index;

	nb::StatusCode code = nb::single_object::parse<nb::Index>(index, (u8 *)indexf.contents, indexf.size);

	fprintf(stdout_redir, "nb parse result: %d\n", (int)code);

	if (code == nb::StatusCode::SUCCESS)
	{
		fprintf(stdout_redir, "num titles: %d\n", index.meta.titles);
		fprintf(stdout_redir, "num official titles: %d\n", index.meta.officialTitles);
		fprintf(stdout_redir, "num legit titles: %d\n", index.meta.legitTitles);
		fprintf(stdout_redir, "size: %ld\n", index.meta.size);
		fprintf(stdout_redir, "num downloads: %ld\n", index.meta.downloads);
		fprintf(stdout_redir, "date: %ld\n", index.date);

		for (auto ct : index.categories) {
			fprintf(stdout_redir, "%d:\n", ct.first);
			fprintf(stdout_redir, "\tname: %s (%s)\n", ct.second.disp.c_str(), ct.second.name.c_str());
			fprintf(stdout_redir, "\tdesc: %s\n", ct.second.desc.c_str());
			fprintf(stdout_redir, "\tpriority: %d\n", ct.second.prio);
			fprintf(stdout_redir, "\tnum titles: %d\n", ct.second.meta.titles);
			fprintf(stdout_redir, "\tnum official titles: %d\n", ct.second.meta.officialTitles);
			fprintf(stdout_redir, "\tnum legit titles: %d\n", ct.second.meta.legitTitles);
			fprintf(stdout_redir, "\tsize: %ld\n", ct.second.meta.size);
			fprintf(stdout_redir, "\tnum downloads: %ld\n", ct.second.meta.downloads);
			fputs("\tsubcategories:\n", stdout_redir);
			for (auto sc : ct.second.subcategories) {
				fprintf(stdout_redir, "\t%d:\n", sc.first);
				fprintf(stdout_redir, "\t\tname: %s (%s)\n", sc.second.disp.c_str(), sc.second.name.c_str());
				fprintf(stdout_redir, "\t\tdesc: %s\n", sc.second.desc.c_str());
				fprintf(stdout_redir, "\t\tnum titles: %d\n", sc.second.meta.titles);
				fprintf(stdout_redir, "\t\tnum official titles: %d\n", sc.second.meta.officialTitles);
				fprintf(stdout_redir, "\t\tnum legit titles: %d\n", sc.second.meta.legitTitles);
				fprintf(stdout_redir, "\t\tsize: %ld\n", sc.second.meta.size);
				fprintf(stdout_redir, "\t\tnum downloads: %ld\n", sc.second.meta.downloads);
			}
		}
	}

	indexf.free();
	return 0;
}
