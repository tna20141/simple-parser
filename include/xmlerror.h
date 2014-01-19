#ifndef _XMLERROR_H
#define _XMLERROR_H

/*
 * Error handling for simple XML parser
 *
 */

/* error codes */
typedef enum {
	ERROR_READ_FILE = -1,
	ERROR_SYNTAX = -2
} error_type;

/* struct containing all info about xml errors */
struct xml_error {
	error_type type;
};

static inline void error_init(struct xml_error *error);

static inline void error_destroy(struct xml_error *error);

static inline void error_copy(struct xml_error *src, struct xml_error *dest);

/*
 * static function definitions
 */
static inline void error_init(struct xml_error *error) {
	error->type = 0;
}

static inline void error_destroy(struct xml_error *error) {
	return;
}

static inline void error_copy(struct xml_error *src, struct xml_error *dest) {
	*src = *dest;
}

#endif