#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void main(){

    char optimized[1024], line[10], opt_line[10], lhs, var1, var2, op;
    strcpy(optimized, "");

    do{
        scanf(" %s[^\n]", line);
        //for algebraic identities: x=0+x, x=1*x
        if(strlen(line) == 5)
        {
            lhs = line[0];
            var1 = line[2];
            op = line[3];
            var2 = line[4];

            if((op == '+' && (var1 == '0' || var2 == '0')) || (op == '*' && (var1 == '1' || var2 == '1')))
            {
                if(lhs == var1 || lhs == var2)
                    continue;
                if(isdigit(var1))
                    sprintf(opt_line, "%c=%c\n", lhs, var2);
                else
                    sprintf(opt_line, "%c=%c\n", lhs, var1);
                
            }
            else
                sprintf(opt_line, "%s\n", line);
        }
        else if (line[3] == '*' && line[4] == '2'){
            sprintf(opt_line, "%c=%c+%c\n", line[0], line[2], line[2]);
        }
        else if (line[3] == '*' && line[2] == '2'){
            sprintf(opt_line, "%c=%c+%c\n", line[0], line[4], line[4]);
        }
        else if (line[2] == 'p' && line[3] == 'o' && line[4] == 'w' && line[5] == '(' && line[8] == '2'){
            sprintf(opt_line, "%c=%c*%c\n", line[0], line[6], line[6]);
        }
        else{
            sprintf(opt_line, "%s\n", line);
        }
        strcat(optimized, opt_line);
    }while (strcmp(line, "END") != 0);

    printf("\n\nOptimized Code -\n");
    printf("%s", optimized);
}