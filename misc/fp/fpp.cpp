#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <ncurses.h>
#include <sys/time.h>
using namespace std;

float ray(float, float, float, string, int);
void raycast_in_fov(float[], float, float, float, float, string, int, float, int);
bool is_wall(float, float, string, int);
// int get_predominant_bearing(float);
void set_steps(float &, float &, float);
void render_view(float[], string, int, float, float);
void move(int, float, float &, float &, float, string, int);

int main()
{
    int term_width = 100;
    int term_heigh = 30;
    float *distances = new float[term_width];

    string map = "";
    map += "####################";
    int map_width = map.length();
    map += "#..................#";
    map += "#..................#";
    map += "#..................#";
    map += "#..................#";
    map += "#..................#";
    map += "#..................#";
    map += "#..................#";
    map += "#..................#";
    map += "#..................#";
    map += "#..................#";
    map += "#..................#";
    map += "#..................#";
    map += "####################";
    int map_height = map.length() / map_width;

    // Tweakables
    float fov = 90;
    float view_distance = 10;
    float player_x = map_width / 2;
    float player_y = map_height / 2;
    float player_a = 0.0f;
    float movement_distance = 0.1;
    float sprinting_distance = 0.15;
    // End Tweakables

    // Game Loop
    char input;
    bool keep_going = true;
    while (keep_going)
    {   
        // User Input
        input = getch();
        switch (input)
        {
        case 'w':
            move(0, movement_distance, player_x, player_y, player_a, map, map_width);
            break;
        case 'd':
            move(1, movement_distance, player_x, player_y, player_a, map, map_width);
            break;
        case 's':
            move(2, movement_distance, player_x, player_y, player_a, map, map_width);
            break;
        case 'a':
            move(3, movement_distance, player_x, player_y, player_a, map, map_width);
            break;
        case 'W':
            move(0, movement_distance, player_x, player_y, player_a, map, map_width);
            break;
        case 'D':
            move(1, movement_distance, player_x, player_y, player_a, map, map_width);
            break;
        case 'S':
            move(2, movement_distance, player_x, player_y, player_a, map, map_width);
            break;
        case 'A':
            move(3, movement_distance, player_x, player_y, player_a, map, map_width);
            break;
        case 'q':
            keep_going = false;
        }
        // End User Input

        raycast_in_fov(distances, player_x, player_y, player_a, view_distance, map, map_width, fov, term_width);
        render_view(distances, map, map_width, player_x, player_y);
    }
    // End Game Loop

    delete distances;
    return 0;
}

void render_view(float distances[], string map, int map_width, float player_x, float player_y)
{
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
    fov /= 360.f; // Convert fov to 0-1 float as in angle
    float x_step, y_step;
    float curr_ray_angle = player_angle - (fov / 2);
    float ray_angle_step = fov / float(resolution);

    // Send out rays
    for (int i = 0; i < resolution; i++)
    {
        set_steps(x_step, y_step, curr_ray_angle);
        distances[i] = ray(player_x, player_y, x_step, y_step, map, map_width, view_distance);
        curr_ray_angle += ray_angle_step;
    }
}

// Sends a single ray with a given x and y step value,
// Returns the distance from the player to the destination
//    up to view_distance, or -1 if nothing is found.
float ray(float x, float y,
          float x_step, float y_step,
          string map, int map_width,
          float view_distance)
{
    for (float i = 0; i < view_distance; i += .1)
    {
        x += x_step;
        y += y_step;

        if (is_wall(int(x), int(x), map, map_width))
        {
            return i;
        }
    }

    return 0.0;
}

// Moves the player in a passed direction (0,1,2,3 --> up, right, left down),
//    unless that move would put them too close to a wall;
void move(int direction, float distance,
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
        set_steps(destination_x, destination_y, player_angle); // Step of dist 1 forward
        break;
    case 1:
        set_steps(destination_x, destination_y, (player_angle + .25)); // Step of dist 1 right
        break;
    case 2:
        set_steps(destination_x, destination_y, (player_angle + .5)); // Step of dist 1 forward
        break;
    case 3:
        set_steps(destination_x, destination_y, (player_angle + .75)); // Step of distance 1 left
        break;
    }

    destination_x = (destination_x / distance) + player_x;
    destination_y = (destination_y / distance) + player_y;
    valid_move = !(is_wall(destination_x, destination_y, map, map_width));

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

// // Returns the predominant bearing of the player
// // (0,1,2,3 ==> up,right,down,left)
// int get_predominant_bearing(float angle)
// {
//     if (
//         angle >= 0 && angle < .125 || angle >= .875 && angle < 1.0)
//     {
//         return 0;
//     }
//     else if (angle >= .125 && angle < .375)
//     {
//         return 1;
//     }
//     else if (angle >= .375 && angle < .625)
//     {
//         return 2;
//     }
//     else
//     {
//         return 3;
//     }
// }

// Sets the values of x_step and y_step based on
//    the passed angle of the player
void set_steps(float &x_step, float &y_step, float angle)
{
    if (angle >= .875)
    {
        angle -= 1;
    }

    float angle_in_rads = 2 * M_PI * angle;

    x_step = sin(angle_in_rads);
    y_step = cos(angle_in_rads);
}