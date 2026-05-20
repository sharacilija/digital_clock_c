#include <stdio.h>
#include <raylib.h>
#include <time.h>
#include <stdbool.h>

#define WIDTH 1030
#define HEIGHT 600

#define ON_COLOR RED
#define OFF_COLOR DARKGRAY

#define OFFSET 50
#define START_X 100
#define DIGIT_DISTANCE 130
#define COLON_DISTANCE 110

#define COLON_RADIUS 18

#define SEGMENT_WIDTH 40
#define SEGMENT_THICKNESS 27
int digits[10][7] = { {1, 1, 1, 0, 1, 1, 1}, // digit 0
                   {0, 0, 1, 0, 0, 1, 0}, // digit 1
                   {1, 0, 1, 1, 1, 0, 1}, // digit 2
                   {1, 0, 1, 1, 0, 1, 1}, // digit 3
                   {0, 1, 1, 1, 0, 1, 0}, // digit 4
                   {1, 1, 0, 1, 0, 1, 1}, // digit 5
                   {1, 1, 0, 1, 1, 1, 1}, // digit 6
                   {1, 0, 1, 0, 0, 1, 0}, // digit 7
                   {1, 1, 1, 1, 1, 1, 1}, // digit 8
                   {1, 1, 1, 1, 0, 1, 1} }; // digit 9

void DrawSegment(Vector2 center, bool horizontal, Color color)
{
    // Create real 7-segment display segment
    int count = 6;
    Vector2 a, b, c, d, e, f;
    if (horizontal)
    {
        a = (Vector2) {center.x - SEGMENT_WIDTH/2 - SEGMENT_THICKNESS/2, center.y};
        b = (Vector2) {center.x - SEGMENT_WIDTH/2, center.y + SEGMENT_THICKNESS/2};        
        c = (Vector2) {center.x - SEGMENT_WIDTH/2, center.y - SEGMENT_THICKNESS/2};
        d = (Vector2) {center.x + SEGMENT_WIDTH/2, center.y + SEGMENT_THICKNESS/2};        
        e = (Vector2) {center.x + SEGMENT_WIDTH/2, center.y - SEGMENT_THICKNESS/2};
        f = (Vector2) {center.x + SEGMENT_WIDTH/2 + SEGMENT_THICKNESS/2, center.y};
    }  
    else
    {
        a = (Vector2) {center.x, center.y - SEGMENT_WIDTH/2 - SEGMENT_THICKNESS/2};
        b = (Vector2) {center.x - SEGMENT_THICKNESS/2, center.y - SEGMENT_WIDTH/2};
        c = (Vector2) {center.x + SEGMENT_THICKNESS/2, center.y - SEGMENT_WIDTH/2};
        d = (Vector2) {center.x - SEGMENT_THICKNESS/2, center.y + SEGMENT_WIDTH/2};
        e = (Vector2) {center.x + SEGMENT_THICKNESS/2, center.y + SEGMENT_WIDTH/2};
        f = (Vector2) {center.x, center.y + SEGMENT_WIDTH/2 + SEGMENT_THICKNESS/2};    
    }      
    Vector2 points[] = {a, b, c, d, e, f};
    DrawTriangleStrip(points, count, color);
}

void DrawDigit(Vector2 center, int digit)
{
    // find out which segments to draw in which color
    int *digit_segments = &digits[digit][0];

    // draw first strip
    Vector2 first = {center.x, center.y - SEGMENT_WIDTH - OFFSET};
    DrawSegment(first, true, digit_segments[0] ? ON_COLOR : OFF_COLOR);

    Vector2 second = {center.x - SEGMENT_WIDTH/2 - OFFSET/2, center.y - SEGMENT_WIDTH/2 - OFFSET/2};
    DrawSegment(second, false, digit_segments[1] ? ON_COLOR : OFF_COLOR);

    Vector2 third = {center.x + SEGMENT_WIDTH/2 + OFFSET/2, center.y - SEGMENT_WIDTH/2 - OFFSET/2};
    DrawSegment(third, false, digit_segments[2] ? ON_COLOR : OFF_COLOR);

    Vector2 fourth = {center.x, center.y};
    DrawSegment(fourth, true, digit_segments[3] ? ON_COLOR : OFF_COLOR);

    Vector2 fifth = {center.x - SEGMENT_WIDTH/2 - OFFSET/2, center.y + SEGMENT_WIDTH/2 + OFFSET/2};
    DrawSegment(fifth, false, digit_segments[4] ? ON_COLOR : OFF_COLOR);

    Vector2 sixth = {center.x + SEGMENT_WIDTH/2 + OFFSET/2, center.y + SEGMENT_WIDTH/2 + OFFSET/2};
    DrawSegment(sixth, false, digit_segments[5] ? ON_COLOR : OFF_COLOR);

    Vector2 seventh = {center.x, center.y + SEGMENT_WIDTH + OFFSET};
    DrawSegment(seventh, true, digit_segments[6] ? ON_COLOR : OFF_COLOR);
}

void DrawColon(Vector2 center, int seconds)
{
    DrawCircleV((Vector2) {center.x, center.y - 50}, COLON_RADIUS, seconds % 2 ? OFF_COLOR : ON_COLOR);
    DrawCircleV((Vector2) {center.x, center.y + 50}, COLON_RADIUS, seconds % 2 ? OFF_COLOR : ON_COLOR);
}

void DrawTime(int hours, int minutes, int seconds)
{
    float x = START_X;
    DrawDigit((Vector2) {x, HEIGHT/2}, hours/10);
    x += DIGIT_DISTANCE;
    DrawDigit((Vector2) {x, HEIGHT/2}, hours%10);
    x += COLON_DISTANCE;

    DrawColon((Vector2) {x, HEIGHT/2}, seconds);
    x += COLON_DISTANCE;

    DrawDigit((Vector2) {x, HEIGHT/2}, minutes/10);
    x += DIGIT_DISTANCE;
    DrawDigit((Vector2) {x, HEIGHT/2}, minutes%10);
    x += COLON_DISTANCE;
    
    DrawColon((Vector2) {x, HEIGHT/2}, seconds);
    x += COLON_DISTANCE;

    DrawDigit((Vector2) {x, HEIGHT/2}, seconds/10);
    x += DIGIT_DISTANCE;
    DrawDigit((Vector2) {x, HEIGHT/2}, seconds%10);
}

int main(int argc, char const *argv[])
{
    InitWindow(WIDTH, HEIGHT, "Digital Clock");

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);

        time_t current_time = time(NULL);
        struct tm *current_localtime = localtime(&current_time);
        DrawTime(current_localtime->tm_hour, current_localtime->tm_min, current_localtime->tm_sec);        
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
