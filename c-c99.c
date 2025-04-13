#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *g(const char *s) {
    char *r = calloc(3000, 1);
    for(int i = 0, j = 0;; i++)
        switch (s[i]) {
            case '\0':
                return r;
            case '\\':
                r[j++] = '\\';
                r[j++] = '\\';
                break;
            case '\n':
                r[j++] = '\\';
                r[j++] = 'n';
                r[j++] = '"';
                r[j++] = '\n';
                r[j++] = '"';
                break;
            case '"':
                r[j++] = '\\';
                r[j++] = '"';
                break;
            default:
                r[j++] = s[i];
                break;
        }
}

char *f(const char *s, int pos) {
    char *r = calloc(3000, 1);
    memcpy(r, s, strlen(s) - pos);
    char *t = g(s);
    strcat(r, t);
    free(t);
    strcat(r, s + strlen(s) - pos);
    return r;
}

int main(void) {
    char *t;
    puts(t = f(
"#include <stdio.h>\n"
"#include <stdlib.h>\n"
"#include <string.h>\n"
"\n"
"char *g(const char *s) {\n"
"    char *r = calloc(3000, 1);\n"
"    for(int i = 0, j = 0;; i++)\n"
"        switch (s[i]) {\n"
"            case '\\0':\n"
"                return r;\n"
"            case '\\\\':\n"
"                r[j++] = '\\\\';\n"
"                r[j++] = '\\\\';\n"
"                break;\n"
"            case '\\n':\n"
"                r[j++] = '\\\\';\n"
"                r[j++] = 'n';\n"
"                r[j++] = '\"';\n"
"                r[j++] = '\\n';\n"
"                r[j++] = '\"';\n"
"                break;\n"
"            case '\"':\n"
"                r[j++] = '\\\\';\n"
"                r[j++] = '\"';\n"
"                break;\n"
"            default:\n"
"                r[j++] = s[i];\n"
"                break;\n"
"        }\n"
"}\n"
"\n"
"char *f(const char *s, int pos) {\n"
"    char *r = calloc(3000, 1);\n"
"    memcpy(r, s, strlen(s) - pos);\n"
"    char *t = g(s);\n"
"    strcat(r, t);\n"
"    free(t);\n"
"    strcat(r, s + strlen(s) - pos);\n"
"    return r;\n"
"}\n"
"\n"
"int main(void) {\n"
"    char *t;\n"
"    puts(t = f(\n"
"\"\", 23));\n"
"    free(t);\n"
"}", 23));
    free(t);
}
