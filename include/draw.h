#ifndef DRAW_H
#define DRAW_H

#include "..\include\common.h"
#include "..\include\mathlib.h"
#include <assert.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

enum glyph_idx {
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    a,
    b,
    c,
    d,
    e,
    f,
    g,
    h,
    i,
    j,
    k,
    l,
    m,
    n,
    o,
    p,
    q,
    r,
    s,
    t,
    u,
    v,
    w,
    x,
    y,
    z,
    nill,
    one,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
};

// The framebuffer drawable area is from (0, 0) to (width-1, height-1).
struct Framebuffer {
    void *buffer;
    u32 bpp;
    u32 width;
    u32 height;
    u32 size;
    HBITMAP bitmap_handle;
    BITMAPINFO info;
    HDC bitmap_hdc;
};

struct Bitmap {
    u8 *pixel;
    u32 bpp;
    u32 width;
    u32 height;
};

struct Sprite {
    float x;
    float y;

    struct Bitmap *frames;

    int animation_frame_count;
    int current_frame;

    double timer_next_frame;
    double current_timer;
};

struct Triangles {
    float verts[6;]
    u32 color;
};

// Create only one framebuffer at a time with the win32 window handle
__declspec(dllexport) struct Framebuffer CreateFramebuffer(HWND window);

/*
 * This function is mainly used when recreating the Framebuffer.
 * It doens't need to be called otherwise really,
 * since a framebuffer needs to be up at all times to be able to render stuff.
 */
__declspec(dllexport) void DestroyFramebuffer(struct Framebuffer *fb);


// After you rendered all stuff to the framebuffer output everything to the screen.

__declspec(dllexport)void OutputFramebuffer(HWND window, struct Framebuffer fb);

/*
 * u32 RGB_Color(u8 red, u8 green, u8 blue);
 * Packs three 8bit values in a unsigned 32bit value in the order the framebuffer uses it and returns the value.
 * The Format: 0RGB.
 */
__declspec(dllexport) u32 RGB_Color(u8 red, u8 green, u8 blue);

// Fill the screen with a solid color. The Color format is 0RGB.
__declspec(dllexport) void FillScreen(struct Framebuffer *framebuffer, u32 color);
__declspec(dllexport) void DrawPixel(struct Framebuffer *framebuffer, u32 x, u32 y, u32 color);
__declspec(dllexport) void DrawRectangle(struct Framebuffer *framebuffer, u32 x0, u32 y0, u32 width, u32 height, u32 color);

// I copied this function from: https://en.wikipedia.org/wiki/Bresenham's_line_algorithm.
// I should make an effort to fully understand this algorithm :P.
// Lines get clipped through the DrawPixel function
__declspec(dllexport) void DrawLine(struct Framebuffer *framebuffer, int x0, int y0, int x1, int y1, u32 color);
// Triangles get clipped thorugh the DrawPixel function inside the DrawLine function.
__declspec(dllexport) void DrawTriangle(struct Framebuffer *framebuffer, u32 points[6], u32 color);


// This function gets only used in LoadBitmapFile().
__declspec(dllexport) void *ReadFileContent(char *filename);
__declspec(dllexport) struct Bitmap LoadBitmapFile(char *filename);

/*
 *  The win32 ReadFile() function loads .bmp (or all formats?) file formats horizontally flipped.
 *  Flip the bmp again to draw bitmaps with right orientation.
 */
__declspec(dllexport) void HFlipBMP24bpp(struct Bitmap *bitmap);
__declspec(dllexport) void HFlipBMP32bpp(struct Bitmap *bitmap);


// Bitmap drawing functions for 24 bytes per pixel and 32 bytes per pixel.
__declspec(dllexport) void DrawBMP24bpp(struct Framebuffer *framebuffer, struct Bitmap bitmap, u32 x_pos, u32 y_pos, u32 color_mask);
__declspec(dllexport) void DrawBMP32bpp(struct Framebuffer *framebuffer, struct Bitmap bitmap, u32 x_pos, u32 y_pos, u32 color_mask);

/*
 * Initalizes a sprite with a collection of bitmaps (animation frames).
 * Sprites are just bitmaps with animation variables at the moment.
 * To update sprite animations call UpdateSpriteAnimation().
 * Bitmap *frames: an array with all the possible frames for an animation cycle.
 */
__declspec(dllexport) void InitSprite(struct Sprite *s, float x, float y, int frame_count, struct Bitmap *frames, int start_frame, double frame_time);
__declspec(dllexport) void UpdateSpriteAnimation(struct Sprite *s);
__declspec(dllexport) void GetPixelFromBMP(struct Bitmap *from, u8 *to);

__declspec(dllexport) void DrawGlyph(struct Framebuffer *buffer, struct Bitmap font, char ch, u32 x, u32 y, u32 color_mask);

__declspec(dllexport) void DrawString(struct Framebuffer *buffer, struct Bitmap font, char *string, u32 x, u32 y, u32 color_mask);

// NDC range: [-1, 1] DC range: [0, window width] / [0, window height]
__declspec(dllexport) float NDC_TO_DC(float v, int width_height);
__declspec(dllexport) float DC_TO_NDC(float v, int width_height);

// Bounding Box Axis Aligned Collision Detection
__declspec(dllexport) bool BBAA(v2 b1, int width1, int height1, v2 b2, int width2, int height2);

#endif // DRAW_H
