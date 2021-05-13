#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include <locale.h>

int codigo(char c){
    c = tolower(c);
    switch (c)
    {
        case 'a': case 'b': case 'c': case 'â': case 'ã': case 'á': case 'à': return 2;
        case 'd': case 'e': case 'f': case 'é': return 3;
        case 'g': case 'h': case 'i': case 'í': return 4;
        case 'j': case 'k': case 'l': return 5;
        case 'm': case 'n': case 'o': case 'õ': case 'ô': return 6;
        case 'p': case 'q': case 'r': case 's': return 7;
        case 't': case 'u': case 'v':  return 8;
        case 'w': case 'x': case 'y': case 'z': return 9;
        default: return -1;
    }
}

int codigo_string(char * a){
    int j = 1;
    int result = 0;
    for (int i = strlen(a)-1; i >= 0; i--)
    {
        result += codigo(a[i]) * j;
        j *= 10;
    }
    return result;
}

int main(int argc, char const *argv[])
{
    setlocale(LC_CTYPE, "en_US.utf8");
    printf("%d\n", codigo_string("cáo"));
    return 0;
}
