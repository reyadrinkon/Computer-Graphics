from graphics import *
import time


def midPointCircleDraw(x_centre, y_centre, r):
   win = GraphWin('midpoint_circle', 600, 600)
   x = r
   y = 0  
   P = 1 - r 
   while x > y:   
       y += 1     
       if P <= 0: 
           P = P + 2 * y + 1      
       else:         
           x -= 1
           P = P + 2 * y - 2 * x + 1      
       if (x < y):
           break   
       x1 = x + x_centre
       y1 = y + y_centre
      
       x2 = -x + x_centre
       y2 = y + y_centre
      
       x3 = x + x_centre
       y3 = -y + y_centre
      
       x4 = -x + x_centre
       y4 = -y + y_centre
       PutPixle(win, x1,y1)
       PutPixle(win, x2,y2)
       PutPixle(win, x3,y3)
       PutPixle(win, x4,y4)
       
       if x != y:
           x1 = y + x_centre
           y1 = x + y_centre
 
           x2 = -y + x_centre
           y2 = x + y_centre
 
           x3 = y + x_centre
           y3 = -x + y_centre
 
           x4 = -y + x_centre
           y4 =  -x + y_centre
 
           PutPixle(win, x1,y1)
           PutPixle(win, x2,y2)
           PutPixle(win, x3,y3)
           PutPixle(win, x4,y4)
   #win.getMouse()
   #win.close()
def PutPixle(win, x, y):
   pt = Point(x,y)
   pt.draw(win)   


def bressenhamcricle(x_centre,y_centre,r):
    win = GraphWin('midpoint_circle', 600, 600)
    def draw(x_centre,y_centre,x,y):
        PutPixle(win, x_centre+x,y_centre+y)
        PutPixle(win, x_centre-x,y_centre+y)
        PutPixle(win, x_centre+x,y_centre-y)
        PutPixle(win, x_centre-x,y_centre-y)
        PutPixle(win, x_centre+x,y_centre+y)
        PutPixle(win, x_centre-x,y_centre+y)
        PutPixle(win, x_centre+x,y_centre-y)
        PutPixle(win, x_centre-x,y_centre-y)

    x=0
    y=r
    d=3-2*r
    draw(x_centre,y_centre,x,y)
    while(y>=x):
        x=x+1
        if(d>0):
            y=y-1
            d=d+4*(x-y)+10
        else:
            d=d+4*x+6
        draw(x_centre,y_centre,x,y)






                     
if __name__ == '__main__':
   x,y = map(int, input("Enter center coordinates:").split())
   r = int(input("Enter radius:"))
   midPointCircleDraw(x, y, r)
   bressenhamcricle(x,y,r)