#ifndef __IO_H
#define __IO_H

wifi_data* read_access_point(FILE *fp, char* buffe, size_t bytes_number);
char* remove_new_line(char* string);
char* extract(char* string, char* delim, int length, int position);
void string_copy(char* destination, char* source, char char_nbr);
int string_compare(char* string1, char* string2, char char_nbr);

#endif
