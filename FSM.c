


enum state { ST_NEW, ST_OPEN, ST_SHIFT, ST_END };

enum state current_state = ST_NEW;

while (current_state != ST_END)
{
    input = get_input();

    switch (current_state)
    {
        case ST_NEW:
        /* Do something with input and set current_state */
        break;

        case ST_OPEN:
        /* Do something different and set current_state */
        break;

        /* ... etc ... */
    }
}


#include<stdio.h>
#include<stdbool.h>

void m_cmnt( FILE *fp )
{
    int prev=0 , ch ;

    while ((ch=getc(fp))!=EOF)
    {
        if ( prev== '*' && ch == '/')
            return ;
        else
        prev=ch ;
    }
}

void s_cmnt( FILE *fp )
{
    int ch ;
    while ( (ch=getc(fp))!='\n' && ch!=EOF )
        ;
}

int main ( int c , char **arr )
{
        FILE *fp , *np ;
        int ch , prev=0 ;
        bool String=0 ;

        fp = fopen(arr[1] , "r") ;
        np = fopen("temp.txt" , "w") ;

        if (fp==NULL )
        {
            printf ("Invalid/No Filename given as Argument ! \n") ;
            return 1 ;
        }
        while ((ch=getc(fp))!=EOF )
        {
            /* file pointer currently not inside a string */
            if ( !String )
            {
                if ( ch=='/' )
                {
                    prev=ch ;
                    ch= getc(fp) ;
                    switch(ch)
                    {
                        case '*'  : m_cmnt( fp) ;
                                     break ;
                        case '/'  : s_cmnt( fp) ;
                                     break ;
                        default   :  putc(prev , np) ;
                                     putc(ch , np) ;
                                     break ;
                    }
                }
                else putc( ch ,np ) ;
            }
            else  putc(ch , np) ;

            if ( ch=='\"')
                String = !String ;
            prev = ch ;
        }

    fclose(fp) ;
    fclose(np) ;
    remove(arr[1]) ;
    rename( "temp.txt" , arr[1] ) ;
    return 0 ;
}






https://www.tutorialspoint.com/data_structures_algorithms/hash_data_structure.htm
