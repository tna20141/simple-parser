#include <customio.h>
#include <validate.h>
#include <parse.h>

void get_declaration(FILE *f, struct xml_declaration *xmldec, struct xml_error *error) {
	char c;

	if (cio_eat_ws(f, NULL)) {
		error->type = ERROR_READ_FILE;
		return;
	}

	if (cio_get_till_delim(f, ">", &xmldec->str, 0, NULL)) {
		error->type = ERROR_READ_FILE;
		return;
	}

	if (validate(xmldec->str)) {
		error->type = ERROR_SYNTAX;
		return;
	}
}