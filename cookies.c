#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void) {
	char buf[1000];
	char buf_cookie[1000];
	char *cook = getenv("HTTP_COOKIE");
	char *queryString = getenv("QUERY_STRING");
	if (cook!=NULL) {
		strcpy(buf_cookie,cook+5);
	}
	if (queryString!=NULL) {
		strcpy(buf,queryString+5);
		printf("Set-cookie: cook=%s; expires=Thursday, 2-feb-19 15:52 GMT\n",buf);
	}
	printf("Content-type: text/html\n\n");
	printf("<!DOCTYPE html>\n");
	printf("<html>\n");
	printf("<head>\n");
	printf("<title>Cookies</title>\n");
	printf("<meta charset='utf-8'>\n");
	printf("</head>\n");
	printf("<body>\n");
	if (strlen(buf_cookie)>0) printf("<h1>Здравствуйте %s!</h1>\n",buf_cookie);
	printf("<form action='cookies.cgi' method='GET'> \n");
	printf("<label for='name'>Ваше имя:</label> \n");
	printf("<p><input type='text' name='name' value='%s'/></p>\n",buf_cookie);
	printf("<p><input type='submit' value='Отправить' /></p> \n");
	printf("</form>\n");
	printf("</body>\n");
	printf("</html>\n");
}