#ifndef _VALIDATE_H
#define _VALIDATE_H

/*
 * Validations for the XML elements
 *
 */

int verify_tag(const char *tag);

int verify_att_key(const char *att_key);

int verify_att_value(const char *att_value);

int verify_text(const char *text);

int validate_declaration(const char *text);

#endif