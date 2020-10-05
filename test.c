#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


#define FileLocation "/dev/PA2" 
#define BuffSize 1024


void main()
{
    int openF;
    openF = open(FileLocation, O_RDWR);
    printf("%d\n",openF);
    int size = 0;
    int whence =0;
    int offset = 0;
    char* buff = NULL;
    buff = malloc(BuffSize);
    char x;
    char buffcont;
    int ioSize = 0;

    while(1)
    {
        ioSize = 0;
        printf("Enter commond <read -- r>, <write -- w>, <seek -- s> or <exit -- e>\n");
        scanf("%s", &x);
        memset(buff, 0, BuffSize);

        switch (x)
        {
        case 'r':
            printf("Plase enter read size\n");
            scanf("%d", &size);
            ioSize = read(openF, buff, size);
            printf("total read: %d\n", ioSize);
            printf("%s\n", buff);
            break;

        case 'w':
            printf("Plase enter buff size\n");
            scanf("%d", &size);
            printf("Plase enter buff content\n");
            scanf("%s", buff);
            ioSize = write(openF, buff, size);
            printf("total write: %d\n", ioSize); 
            break;

        case 's':
            printf("Plase enter offset\n");
            scanf("%d", &offset);

            printf("Plase enter < SEEK_SET--0 > < SEEK_CUR--1 >< SEEK_END--2 >\n");
            scanf("%d", &whence);           
            while(whence <0 || whence > 2)
            {
                printf("wrong type\n");
                printf("Plase enter < SEEK_SET--0 > < SEEK_CUR--1 >< SEEK_END--2 >\n");
                scanf("%d", &whence);           
                if(whence > 0 && whence < 2)
                    break;
            }
            lseek(openF, offset, whence);
            break;
        case 'e':
            printf("good bye\n");
            return;

        default:
            printf("Please enter correct commond");
            break;
        }        
    }
    return;
}
