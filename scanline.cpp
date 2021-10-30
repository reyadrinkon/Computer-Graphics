#include<graphics.h>
#include<bits/stdc++.h>

using namespace std;

const int WINDOW_W = 600, WINDOW_H = 600;

struct pnt{
    double x,y;
    pnt(){}
    pnt(double a, double b)
    {
        x=a;
        y=b;
    }
    bool operator < (const pnt & p) const
    {
        return x < p.x;
    }
};

struct Edge{

    double ymin,ymx, xwith_ymn, m_inv;
    Edge(){};
    Edge(double a , double b, double c , double d)
    {
        ymin=a;
        ymx=b;
        xwith_ymn=c;
        m_inv=d;
    }
    bool operator < (const Edge &p) const
    {
        return ymin<p.ymin;
    }

};

void drawAxis()
{
    for(int i=0; i<WINDOW_H; i++) putpixel(WINDOW_W/2, i, WHITE);
    for(int i=0; i<WINDOW_W; i++) putpixel(i, WINDOW_H/2, WHITE);
}

pnt cnv_pxl(pnt p)
{
    p.x += WINDOW_W/2;
    p.y = -p.y;
    p.y += WINDOW_H/2;

    return p;
}

void draw_pixel(pnt p, int color)
{
    delay(2);
    p = cnv_pxl(p);
    putpixel((int)(p.x+0.5),(int) (p.y+0.5), color);
}


void draw_line(pnt a, pnt b,int color)
{
    if(a.x > b.x) swap(a, b);


    if(a.y == b.y)
    {
        if(a.x>b.x) swap(a,b);
        for(int x = a.x; x <= b.x; x++)
        {
            draw_pixel(pnt(x, a.y), color);
        }
    }

    else if(a.x == b.x)
    {
        if(a.y > b.y) swap(a, b);
        for(int y = a.y; y <= b.y; y++)
        {
            draw_pixel(pnt(a.x, y), color);
        }
    }

    else
    {
        double m = (double)(b.y-a.y)/(double)(b.x-a.x);
        double m_inv= 1.0/m;

        if(fabs(m)<=1.0)
        {
            if(a.x>b.x) swap(a,b);
            while(a.x<=b.x)
            {
                draw_pixel(a,color);
                a.x+=1;
                a.y+=m;
            }

        }
        else{
            if(a.y>b.y) swap(a,b);
            while(a.y<=b.y)
            {
                draw_pixel(a,color);
                a.x+=m_inv;
                a.y+=1;
            }
        }
    }
}

void Scan_line(vector<pnt> points,int color)
{
    vector<Edge> edgs;

    int n=points.size();
    double st=1e15 , en =-1e15 ;

    unordered_map<double,int>mp;


    for(int i=0;i<n;i++)
    {
        pnt a =points[i];
        pnt b =points[(i+1)%n];
        if(a.y==b.y) continue;

        Edge temp;
        temp.ymin=min(a.y,b.y);
        temp.ymx=max(a.y,b.y);
        temp.xwith_ymn=a.y < b.y ? a.x : b.x;
        temp.m_inv=(b.x-a.x) / (b.y -a.y);

        st = min(st,temp.ymin);
        en = max(en,temp.ymx);

        mp[temp.ymin] =1;

        edgs.push_back(temp);
    }

    n=edgs.size();
    sort(edgs.begin(),edgs.end());

    for(int i=0;i<n;i++)
    {
        if(mp[edgs[i].ymx]) edgs[i].ymx--;
    }

    /// loop on y
    for(double y=st;y<=en;y++)
    {
        vector<pnt> integer_pnt;
        for(int i=0;i<n;i++)
        {
            if(y>=edgs[i].ymin && y<=edgs[i].ymx)
            {
                pnt temp;
                temp.x=edgs[i].xwith_ymn;
                temp.y=y;
                edgs[i].xwith_ymn+=edgs[i].m_inv;
                integer_pnt.push_back(temp);
            }
        }

        sort(integer_pnt.begin(),integer_pnt.end());
        for(int i=0;i<integer_pnt.size()-1;i+=2)
        {
            draw_line(integer_pnt[i],integer_pnt[i+1],RED);
        }
    }
}

void draw_Polygon(vector<pnt> points,int color)
{
    int n = points.size();
    for(int i=0; i<n; i++)
    {

        draw_line(points[i], points[(i+1)%n],color);
    }
}

int main()
{
    initwindow(WINDOW_W,WINDOW_H);
    drawAxis();

    vector<pnt> Poly;


    Poly.push_back(pnt(-140,-40));
    Poly.push_back(pnt(-60,60));
    Poly.push_back(pnt(0,20));
    Poly.push_back(pnt(-40,-60));
    Poly.push_back(pnt(100,-80));
    Poly.push_back(pnt(150,100));
    Poly.push_back(pnt(-150,150));

    draw_Polygon(Poly,YELLOW);

    Scan_line(Poly,RED);
    getchar();
    return 0;
}
