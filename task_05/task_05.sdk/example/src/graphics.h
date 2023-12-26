#ifndef GRAPHICS_H
#define GRAPHICS_H

#define G_GC {0xb4, 0xb4, 0xb4}
#define G_GO {0x46, 0x46, 0x46}
#define G_BL {0x00, 0x00, 0x00}

#define SMOKE_TIME      20000   // microseconds
#define SMOKE_FRAMES    4       // microseconds
#define SMOKE_WIDTH     3       // pixels
#define SMOKE_HEIGHT    6       // pixels

color_t smoke[SMOKE_FRAMES][SMOKE_WIDTH][SMOKE_HEIGHT] = {
    {
        {G_BL,G_BL,G_BL},
        {G_BL,G_BL,G_BL},
        {G_BL,G_GC,G_BL},
        {G_BL,G_BL,G_GO},
        {G_BL,G_GC,G_BL},
        {G_GO,G_BL,G_GC}
    },
    {
        {G_BL,G_BL,G_BL},
        {G_BL,G_BL,G_BL},
        {G_GO,G_BL,G_BL},
        {G_BL,G_GO,G_GC},
        {G_GC,G_BL,G_GO},
        {G_BL,G_BL,G_BL}
    },
    {
        {G_BL,G_BL,G_BL},
        {G_BL,G_GO,G_BL},
        {G_BL,G_BL,G_GC},
        {G_GC,G_BL,G_BL},
        {G_BL,G_BL,G_BL},
        {G_BL,G_BL,G_BL}
    },
    {
        {G_BL,G_BL,G_GO},
        {G_BL,G_BL,G_BL},
        {G_BL,G_BL,G_BL},
        {G_BL,G_BL,G_BL},
        {G_BL,G_BL,G_BL},
        {G_BL,G_BL,G_BL}
    }
};

// Functions
void paint_object(position_t pos, color_t **object, int height, int width);
void paint_animation(position_t pos, color_t ***animation, int frames, int period, int rows, int cols);
void print_background(color_t color);
