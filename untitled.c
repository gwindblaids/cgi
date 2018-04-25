#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void url_decode(char *st) {
	char *p = st;
	char hex[3];
	int code;
	do {
		if (*st=='%') {
			hex[0] = *(++st);
			hex[1] = *(++st);
			hex[2] = 0;
			sscanf(hex,"%X",&code);
			*p++ = (char) code;
		}
		else if (*st=='+') {
			*p++=' ';
		} else *p++=*st;

	} while(*st++!=0);
}
int main(void) {
	char *remoteAddr = getenv("REMOTE_ADDR");
	char *contentLength = getenv("CONTENT_LENGTH");
	char *queryString = malloc(strlen(getenv("QUERY_STRING"))+1);
	strcpy(queryString,getenv("QUERY_STRING"));
	url_decode(queryString);
	int num_bytes = atoi(contentLength);
	char *data = (char *)malloc(num_bytes+1);
	fread(data,1,num_bytes,stdin);
	data[num_bytes] = 0;
	url_decode(data);
	printf("Content-type: text/html\n\n");
	printf("<!DOCTYPE html>\n");
	printf("<html>\n");
	printf("<head>\n");
	printf("<title>POST</title>\n");
	printf("<meta charset='utf-8'>\n");
	printf("</head>\n");
	printf("<body>\n");
	printf("<h1>Здравствуйте!</h1>\n");
	printf("<p>Ваш ip адрес: %s</p>\n",remoteAddr);
	printf("<p>Ваш запрос :%s</p>\n", data);
	printf("<p>Колличество байтов данных: %d</p>\n",num_bytes);
	printf("<p>А вот то, что мы получили через url: %s </p>\n", queryString);
	printf("</body>\n");
	printf("</html>\n");
}