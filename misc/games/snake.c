#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <sys/select.h>
#include <stdio.h>
#include <time.h>

#define DESIRED_WIDTH  70
#define DESIRED_HEIGHT 25

WINDOW * g_mainwin;
int g_oldcur, g_score = 0, g_width, g_height;
typedef struct {
    int x;
    int y;
} pos;
pos fruit;


bool *spaces;


struct s_node
{
    pos *position; 
    struct s_node *prev;
    struct s_node *next;
} *front=NULL, *back=NULL;
typedef struct s_node node;

pos* peek( )
{
    return front == NULL ? NULL : front->position;
}

pos* dequeue( )
{
    node *oldfront = front;
    front = front->next;
    return oldfront->position;
}

void enqueue( pos position )
{
   pos *newpos   = (pos*)  malloc( sizeof( position ) ); 
   node *newnode = (node*) malloc( sizeof( node ) );

   newpos->x = position.x;
   newpos->y = position.y;
   newnode->position = newpos;

   if( front == NULL && back == NULL )
       front = back = newnode;
   else
   {
       back->next = newnode;
       newnode->prev = back;
       back = newnode;
   }
}

void snake_write_text( int y, int x, char* str )
{
    mvwaddstr( g_mainwin, y , x, str );
}

void snake_draw_board( )
{
    int i;
    for( i=0; i<g_height; i++ )
    {
        snake_write_text( i, 0,         "*" );
        snake_write_text( i, g_width-1, "*" );
    }
    for( i=1; i<g_width-1; i++ )
    {
        snake_write_text( 0, i,          "*" );
        snake_write_text( g_height-1, i, "*" );
    }
    snake_write_text( g_height+1, 2, "Score:" );
}

void snake_game_over( )
{
    free( spaces );
    while( front )
    {
        node *n = front;
        front = front->next;
        free( n );
    }
    endwin();
    exit(0);
}

bool snake_in_bounds( pos position )
{
    return position.y < g_height - 1 && position.y > 0 && position.x < g_width - 1 && position.x > 0;
}

int snake_cooridinate_to_index( pos position )
{
    return g_width * position.y + position.x;
}

pos snake_index_to_coordinate( int index )
{
    int x = index % g_width;
    int y = index / g_width;
    return (pos) { x, y };
}


void snake_draw_fruit( )
{
    attrset( COLOR_PAIR( 3 ) );
    int idx;
    do
    {
        idx = rand( ) % ( g_width * g_height );
        fruit = snake_index_to_coordinate( idx );
    }
    while( spaces[idx] || !snake_in_bounds( fruit ) );    
    snake_write_text( fruit.y, fruit.x, "1" );
}

bool snake_move_player( pos head )
{
    attrset( COLOR_PAIR( 1 ) ) ;
    
    int idx = snake_cooridinate_to_index( head );
    if( spaces[idx] )
        snake_game_over( );
    spaces[idx] = true; 
    enqueue( head );
    g_score += 10;
    
    
    if( head.x == fruit.x && head.y == fruit.y )
    {
        snake_draw_fruit( );
        g_score += 1000;
    }
    else
    {

        pos *tail = dequeue( );
        spaces[snake_cooridinate_to_index( *tail )] = false;
        snake_write_text( tail->y, tail->x, " " );
    }
    
    snake_write_text( head.y, head.x, "O" );
    
    char buffer[25];
    sprintf( buffer, "%d", g_score );
    attrset( COLOR_PAIR( 2 ) );
    snake_write_text( g_height+1, 9, buffer );

}

int main( int argc, char *argv[] )
{
    int key = KEY_RIGHT;
    if( ( g_mainwin = initscr() ) == NULL ) {
        perror( "error initialising ncurses" );
        exit( EXIT_FAILURE );
    }
    
    srand( time( NULL ) );
    noecho( );
    curs_set( 2 );
    halfdelay( 1 );
    keypad( g_mainwin, TRUE );
    g_oldcur = curs_set( 0 );
    start_color( );
    init_pair( 1, COLOR_RED,     COLOR_BLACK );
    init_pair( 2, COLOR_GREEN,   COLOR_BLACK );
    init_pair( 3, COLOR_YELLOW,  COLOR_BLACK );
    init_pair( 4, COLOR_BLUE,    COLOR_BLACK );
    init_pair( 5, COLOR_CYAN,    COLOR_BLACK );
    init_pair( 6, COLOR_MAGENTA, COLOR_BLACK );
    init_pair( 7, COLOR_WHITE,   COLOR_BLACK );
    getmaxyx( g_mainwin, g_height, g_width );
    
    g_width  = g_width  < DESIRED_WIDTH  ? g_width  : DESIRED_WIDTH;
    g_height = g_height < DESIRED_HEIGHT ? g_height : DESIRED_HEIGHT; 
    
    spaces = (bool*) malloc( sizeof( bool ) * g_height * g_width );

    snake_draw_board( );
    snake_draw_fruit( );
    pos head = { 5,5 };
    enqueue( head );
    
    while( 1 )
    {
        int in = getch( );
        if( in != ERR )
            key = in;
        switch( key )
        {
            case KEY_DOWN:
            case 'j':
            case 'J':
            case 's':
            case 'S':
                head.y++;
                break;
            case KEY_RIGHT:
            case 'l':
            case 'L':
            case 'd':
            case 'D':
                head.x++;
                break;
            case KEY_UP:
            case 'k':
            case 'K':
            case 'w':
            case 'W':
                head.y--;
                break;
            case KEY_LEFT:
            case 'h':
            case 'H':
            case 'a':
            case 'A':
                head.x--;
                break;

        }
        if( !snake_in_bounds( head ) )    
            snake_game_over( );
        else
            snake_move_player( head );
    }
    snake_game_over( );
}