#include<bits/stdc++.h>
#include<windows.h>
#include<graphics.h>
using namespace std;

struct pnt
{
    int x, y;
    pnt(){}
    pnt(int a, int b)
    {
        x = a;
        y = b;
    }
};

const int WINDOW_W = 800, WINDOW_H = 600;

void draw_axis()
{
    for(int i=0; i<WINDOW_H; i++) putpixel(WINDOW_W/2, i, WHITE);
    for(int i=0; i<WINDOW_W; i++) putpixel(i, WINDOW_H/2, WHITE);
}

pnt conv_pixel(pnt p)
{
    p.x += WINDOW_W/2;
    p.y = -p.y;
    p.y += WINDOW_H/2;

    return p;
}

void draw_pixel(pnt p, int color)
{
    delay(0.105);
    p = conv_pixel(p);
    putpixel(p.x, p.y, color);
}

void Draw_Line(pnt a, pnt b)
{
    if(a.x > b.x) swap(a, b);

    if(a.y == b.y)
    {
        for(int x = a.x; x <= b.x; x++)
        {
            draw_pixel(pnt(x, a.y), YELLOW);
        }
    }

    ///vertical

    else if(a.x == b.x)
    {
        if(a.y > b.y) swap(a, b);
        for(int y = a.y; y <= b.y; y++)
        {
            draw_pixel(pnt(a.x, y), YELLOW);
        }
    }

    else
    {
        double m = (double)(b.y-a.y)/(double)(b.x-a.x);
        double c = (double)a.y - m*(double)a.x;
        for(int x = a.x; x <= b.x; x++)
        {
            int y = round(m*(double)x + c);

            draw_pixel(pnt(x, y), YELLOW);
        }
    }
}

void draw_polygon(vector<pnt> points)
{
    int n = points.size();
    for(int i=0; i<n; i++)
    {

        Draw_Line(points[i], points[(i+1)%n]);
    }
}

void boundary_fill(pnt curr_pixel, int boundaryColor, int fill_color)
{
    pnt pixel = conv_pixel(curr_pixel);
    int Curr_color = getpixel(pixel.x, pixel.y);
    if(Curr_color == boundaryColor || Curr_color == fill_color)
    {
        return;
    }

    draw_pixel(curr_pixel, fill_color);

    boundary_fill(pnt(curr_pixel.x, curr_pixel.y+1), boundaryColor, fill_color);
    boundary_fill(pnt(curr_pixel.x, curr_pixel.y-1), boundaryColor, fill_color);
    boundary_fill(pnt(curr_pixel.x+1, curr_pixel.y), boundaryColor, fill_color);
    boundary_fill(pnt(curr_pixel.x-1, curr_pixel.y), boundaryColor, fill_color);
}


void flood_fill(pnt curr_pixel, int old_color, int fill_color)
{
    pnt pixel = conv_pixel(curr_pixel);
    int Curr_color = getpixel(pixel.x, pixel.y);
    if(Curr_color != old_color )
    {
        return;
    }

    draw_pixel(curr_pixel, fill_color);

    flood_fill(pnt(curr_pixel.x, curr_pixel.y+1), old_color, fill_color);
    flood_fill(pnt(curr_pixel.x, curr_pixel.y-1), old_color, fill_color);
    flood_fill(pnt(curr_pixel.x+1, curr_pixel.y), old_color, fill_color);
    flood_fill(pnt(curr_pixel.x-1, curr_pixel.y), old_color, fill_color);

}





int main()
{

    initwindow(WINDOW_W, WINDOW_H);
    draw_axis();

    vector<pnt> poly;

    poly.push_back(pnt(0, 0));
    poly.push_back(pnt(-115, 0));
    poly.push_back(pnt(-150, -115));
    poly.push_back(pnt(-205, -205));
    poly.push_back(pnt(0, -115));


    draw_polygon(poly);


    flood_fill(pnt(-1, -1), BLACK, RED);


    getchar();

    return 0;
}
