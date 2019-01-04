#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <ncurses.h>
#include <signal.h>
#include <vector>
using namespace std;

static void finish(int sig); // ncurses function
float ray(float, float, float, float, string, int, float);
void raycast_in_fov(float[], float, float, float, float, string, int, float, int);
bool is_wall(float, float, string, int);
void set_steps(float &, float &, float, float magnitude = 1);
void render_view(float[], string, int, int, float, float, int, int, float, float, float, bool);
void player_movement(int, float, float &, float &, float, string, int);
int get_predominant_bearing(float);
int get_player_char(float);

vector<float> detected_x;
vector<float> detected_y;

int main()
{
    int term_width = 150;
    int term_height = 50;
    float *distances = new float[term_width];

    string map = "";
    // map += "#####################  ";
    // int map_width = map.length();
    // map += "#...#...............#  ";
    // map += "#...#.........#.....#  ";
    // map += "#...#........###....#  ";
    // map += "#.............#.....#  ";
    // map += "#...................#  ";
    // map += "#...................#  ";
    // map += "#...................#  ";
    // map += "#.........###.......#  ";
    // map += "#.........###.......#  ";
    // map += "#.........###.......#  ";
    // map += "#...................#  ";
    // map += "#####################  ";
    // map += "                       ";

    map += "#########################################################";
    int map_width = map.length();
    map += "#.......................................................#";
    map += "#.......................................................#";
    map += "#.......................................................#";
    map += "#.......................................................#";
    map += "#.....##############..........###..####.................#";
    map += "#.....##.......####...........#.......#.................#";
    map += "#.....#.........##............#.......#.................#";
    map += "#...............###...........#.......#.................#";
    map += "#...............####..........#.......#.................#";
    map += "#...............#####.........#.#######.................#";
    map += "#...............######.......#..#.......................#";
    map += "#............................#..#.......................#";
    map += "#......................#######..################........#";
    map += "#......................#................................#";
    map += "#......................#..######################........#";
    map += "#......................#.........#......................#";
    map += "#......................#.........#......................#";
    map += "#......................#.........#......................#";
    map += "#......................###########......................#";
    map += "#.......................................................#";
    map += "#.......................................................#";
    map += "#.......................................................#";
    map += "#########################################################";
    int map_height = map.length() / map_width;

    // Tweakables
    float fov = 60;
    float view_distance = 20;
    float player_x = 1.5;
    float player_y = 1.5;
    float player_a = 0.0;
    float movement_distance = 0.1;
    float sprinting_distance = .1;
    float retinal_distance = .6;
    bool display_map = true;
    // End Tweakables

    // ncurses intitialization, source: https://invisible-island.net/ncurses/ncurses-intro.html#updating
    signal(SIGINT, finish); /* arrange interrupts to terminate */
    initscr();              /* initialize the curses library */
    keypad(stdscr, TRUE);   /* enable keyboard mapping */
    nonl();                 /* tell curses not to do NL->CR/NL on output */
    cbreak();               /* take input chars one at a time, no wait for \n */
    nodelay(stdscr, TRUE);
    echo(); /* echo input - in color */
    if (has_colors())
    {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);
        init_pair(4, COLOR_BLUE, COLOR_BLACK);
        init_pair(5, COLOR_CYAN, COLOR_BLACK);
        init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(7, COLOR_WHITE, COLOR_BLACK);
    }
    // end ncurses initialization

    // Game Loop
    int input;
    bool keep_going = true;
    while (keep_going)
    {
        detected_x.clear();
        detected_y.clear();

        // User Input
        input = getch();
        switch (input)
        {
        case 'w':
            player_movement(0, movement_distance, player_x, player_y, player_a, map, map_width);
            break;
        case 'd':
            player_movement(1, movement_distance, player_x, player_y, player_a, map, map_width);
            break;
        case 's':
            player_movement(2, movement_distance, player_x, player_y, player_a, map, map_width);
            break;
        case 'a':
            player_movement(3, movement_distance, player_x, player_y, player_a, map, map_width);
            break;
        case 'W':
            player_movement(0, movement_distance, player_x, player_y, player_a, map, map_width);
            break;
        case 'D':
            player_movement(1, movement_distance, player_x, player_y, player_a, map, map_width);
            break;
        case 'S':
            player_movement(2, movement_distance, player_x, player_y, player_a, map, map_width);
            break;
        case 'A':
            player_movement(3, movement_distance, player_x, player_y, player_a, map, map_width);
            break;
        case 'q':
            keep_going = false;
            break;
        case 'm':
            display_map = !display_map;
            break;
        }
        // End User Input

        raycast_in_fov(distances, player_x, player_y, player_a, view_distance, map, map_width, fov, term_width);
        render_view(distances, map, map_width, map_height, player_x, player_y, term_width, term_height, retinal_distance, player_a, view_distance, display_map);
    }
    // End Game Loop
    delete distances;
    finish(SIGINT);
    return 0;
}

// Renders the view to the screen, going column by column
// distances represents the distances to each object by each ray
// retinal_distance is the distance to a theoretical retina allowing for
//    accurate scaling of objects at distance
void render_view(
    float distances[], string map,
    int map_width, int map_height,
    float player_x, float player_y,
    int terminal_width, int terminal_height,
    float retinal_distance, float player_angle,
    float view_distance, bool display_map)
{
    float sky_size, projection_height;

    for (int x = 0; x < terminal_width; x++)
    {
        projection_height = terminal_height * (retinal_distance / distances[x]);

        for (int y = 0; y < terminal_height; y++)
        {
            if (display_map && x < map_width && y < map_height) // In bounds of minimap area
            {
                if (x == int(player_x) && y == int(player_y)) // Player location on the map
                {
                    mvaddch(y, x, char(get_player_char(player_angle)));
                }
                else
                {
                    char curr_char = map[((int(y) * map_width) + int(x))];
                    if (x < map_width && y < map_height) // In bounds of minimap area
                    {
                        if (x == int(player_x) && y == int(player_y)) // Player location on the map
                        {
                            mvaddch(y, x, char(get_player_char(player_angle)));
                        }
                        else
                        {
                            mvaddch(y, x, curr_char);
                        }
                    }
                }
            }
            else
            {
                if (distances[x] > 0)
                {
                    sky_size = (terminal_height - projection_height) * 2.f / 3.f;
                    if (y <= sky_size)
                    {
                        mvaddch(y, x, ' ');
                    }
                    else if (y <= sky_size + projection_height)
                    {
                        mvaddch(y, x, '#');
                    }
                    else
                    {
                        mvaddch(y, x, '.');
                    }
                }
                else // No wall in range, pretend like wall at distance 10 but not displaying anything there.
                {
                    projection_height = terminal_height * (retinal_distance / view_distance);
                    sky_size = (terminal_height - projection_height) * 2.f / 3.f;
                    if (y <= sky_size + projection_height)
                    {
                        mvaddch(y, x, ' ');
                    }
                    else
                    {
                        mvaddch(y, x, '.');
                    }
                }
            }
        }
    }
    refresh();
}

/*
** distances[] is the array that the distances will be recorded into,
** view_distance is the maximum distance the player can see before encountering fog,
** fov is the desired field of view in degrees
** resolution is the number of rays to send out (determined by terminal size)
*/
void raycast_in_fov(float distances[],
                    float player_x, float player_y,
                    float player_angle, float view_distance,
                    string map, int map_width,
                    float fov, int resolution)
{
    fov = fov / 360.f; // Convert fov to 0-1 float as in angle
    float x_step, y_step;
    float curr_ray_angle = player_angle - (fov / 2);
    float ray_angle_step = fov / float(resolution);

    // Send out rays
    for (int i = 0; i < resolution; i++)
    {
        set_steps(x_step, y_step, curr_ray_angle, .1);
        distances[i] = ray(player_x, player_y, x_step, y_step, map, map_width, view_distance);
        curr_ray_angle += ray_angle_step;
    }
}

// Sends a single ray with a given x and y step value,
// Returns the distance from the player to the destination
//    up to view_distance, or 0 if nothing is found.
float ray(float x, float y,
          float x_step, float y_step,
          string map, int map_width,
          float view_distance)
{
    for (float i = 0; i < view_distance; i += .1)
    {
        x += x_step;
        y += y_step;

        if (is_wall(int(x), int(y), map, map_width))
        {
            detected_x.push_back(x);
            detected_y.push_back(y);
            return i;
        }
    }

    return 0.0;
}

// Moves the player in a passed direction (0,1,2,3 --> up, right, left down),
//    unless that player_movement would put them too close to a wall;
void player_movement(int direction, float distance,
                     float &player_x, float &player_y,
                     float player_angle, string map,
                     int map_width)
{
    bool valid_move = true;
    float destination_x;
    float destination_y;

    switch (direction)
    {
    default:
        set_steps(destination_x, destination_y, player_angle, distance); // Step of dist 1 forward
        break;
    case 1:
        set_steps(destination_x, destination_y, (player_angle + .25), distance); // Step of dist 1 right
        break;
    case 2:
        set_steps(destination_x, destination_y, (player_angle + .5), distance); // Step of dist 1 forward
        break;
    case 3:
        set_steps(destination_x, destination_y, (player_angle + .75), distance); // Step of distance 1 left
        break;
    }

    destination_x = (destination_x) + player_x;
    destination_y = (destination_y) + player_y;
    valid_move = !(is_wall(destination_x, destination_y - .01, map, map_width));

    if (valid_move)
    {
        player_x = destination_x;
        player_y = destination_y;
    }
}

// Returns whether the given x and y are in a wall tile
bool is_wall(float x, float y, string map, int map_width)
{
    if (map[int(y) * map_width + int(x)] == '#')
    {
        return true;
    }
    else
    {
        return false;
    }
}

int get_player_char(float player_angle)
{
    int bearing = get_predominant_bearing(player_angle);
    switch (bearing)
    {
    default: // Upward facing
        return '↑';
        break;
    case 1:
        return '↗';
        break;
    case 2:
        return '→';
        break;
    case 3:
        return '↘';
        break;
    case 4:
        return '↓';
        break;
    case 5:
        return '↙';
        break;
    case 6:
        return '←';
        break;
    case 7:
        return '↖';
        break;
    }
}

// Returns the predominant bearing of the player
// (0,1,2,3,4,5,6,7 ==> up,up-right,right,down-right,down,down-left,left,up-left)
int get_predominant_bearing(float angle)
{
    if (angle >= 0 && angle < 1.0 / 8.0)
    {
        return 0;
    }
    else if (angle >= 1.0 / 8.0 && angle < 2.0 / 8.0)
    {
        return 1;
    }
    else if (angle >= 2.0 / 8.0 && angle < 3.0 / 8.0)
    {
        return 2;
    }
    else if (angle >= 3.0 / 8.0 && angle < 4.0 / 8.0)
    {
        return 3;
    }
    else if (angle >= 4.0 / 8.0 && angle < 5.0 / 8.0)
    {
        return 4;
    }
    else if (angle >= 5.0 / 8.0 && angle < 6.0 / 8.0)
    {
        return 5;
    }
    else if (angle >= 6.0 / 8.0 && angle < 7.0 / 8.0)
    {
        return 6;
    }
    else
    {
        return 7;
    }
}

// Sets the values of x_step and y_step based on
//    the passed angle of the player and the passed
//    magnitude, which is the length of the hypotenuse
void set_steps(float &x_step, float &y_step, float angle, float magnitude)
{
    if (angle >= .875)
    {
        angle -= 1;
    }

    float angle_in_rads = 2 * M_PI * angle; // Convert to radians
    angle_in_rads -= M_PI_2;                // Shift angle

    x_step = cos(angle_in_rads) * magnitude;
    y_step = sin(angle_in_rads) * magnitude;
}

// Function that runs at end of execution or at error.
static void finish(int sig)
{
    endwin();
    exit(0);
}