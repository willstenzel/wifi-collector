#ifndef __IO_H
#define __IO_H

wifi_data* read_access_point(FILE *fp, char* buffe);
char* remove_new_line(char* string);
char* extract(char* string, char* delim, int length, int position);

#endif
