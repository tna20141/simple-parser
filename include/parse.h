#ifndef _PARSE_H
#define _PARSE_H

/*
 * Module for parsing XML documents
 *
 */

#include <customio.h>
#include <basic_tree.h>
#include <basic_stack.h>
#include "validate.h"
#include "xmlerror.h"

/* info about the currently-built DOM tree, used in the middle of parsing */
struct parse_info {
	btnode *current;
	bs_stack elem_stack;
	struct xml_error error;
};

/* keep data about XML declaration */
struct xml_declaration {
	char *str;
};

/* struct to keep return data for users */
struct xml_data {
	btnode *root;
	struct xml_declaration xmldec;
	struct xml_error error;
};

/* lists all the states of XML parsing */
typedef enum {
	PARSE_VOID,
	PARSE_ELEM_OPEN_TAG,
	PARSE_ATTRIBUTE,
	PARSE_TEXT,
	PARSE_ELEM_CLOSE_TAG
} parse_states;

static inline void to_state(parse_states state, FILE *f, struct parse_info *pinfo);

void get_declaration(FILE *f, struct xml_declaration *xmldec, struct xml_error *error);

void parse(const char *filename, struct xml_data *xmldata);

/*
 * state functions
 */
void state_void(FILE *f, struct parse_info *pinfo);
void state_elem_open_tag(FILE *f, struct parse_info *pinfo);
void state_attribute(FILE *f, struct parse_info *pinfo);
void state_text(FILE *f, struct parse_info *pinfo);
void state_elem_close_tag(FILE *f, struct parse_info *pinfo);

/*
 * init & destroy functions
 */
static inline void init_parse_info(struct parse_info *pinfo);
static inline void init_xml_declaration(struct xml_declaration *xmldec);
static inline void init_xml_data(struct xml_data *xmldata);

static inline void destroy_parse_info(struct parse_info *pinfo);
static inline void destroy_xml_declaration(struct xml_declaration *xmldec);
static inline void destroy_xml_data(struct xml_data *xmldata);

/*
 * common functions
 */
int handle_tag_starting(FILE *f);
int handle_tag_ending(FILE *f);

/*
 * inline function definitions
 */
static inline void to_state(parse_states state, FILE *f, struct parse_info *pinfo) {
	switch (state) {
		case PARSE_VOID:
			state_void(f, pinfo);
			break;
		case PARSE_ELEM_OPEN_TAG:
			state_elem_open_tag(f, pinfo);
			break;
		case PARSE_ATTRIBUTE:
			state_attribute(f, pinfo);
			break;
		case PARSE_TEXT:
			state_text(f, pinfo);
			break;
		case PARSE_ELEM_CLOSE_TAG:
			state_elem_close_tag(f, pinfo);
			break;
		default:
			break;
	}
}

static inline void init_parse_info(struct parse_info *pinfo, struct xml_error *error) {
	pinfo->current = NULL;
	bs_init(&pinfo->elem_stack);
	error_copy(&pinfo->error, error);
}

static inline void init_xml_declaration(struct xml_declaration *xmldec) {
	xmldec->str = NULL;
}

static inline void init_xml_data(struct xml_data *xmldata) {
	xmldata->root = NULL;
	init_xml_declaration(&xmldata->xmldec);
	error_init(&xmldata->error);
}

static inline void destroy_parse_info(struct parse_info *pinfo) {
	pinfo->current = NULL;
	bs_destroy(&pinfo->elem_stack);
	error_destroy(&pinfo->error);
}

static inline void destroy_xml_declaration(struct xml_declaration *xmldec) {
	free(xmldata->str);
}

static inline void destroy_xml_data(struct xml_data *xmldata) {
	bt_destroy_tree(xmldata->root);
	destroy_xml_declaration(&xmldata->xmldec);
	error_destroy(&xmldata->error);
}

#endif