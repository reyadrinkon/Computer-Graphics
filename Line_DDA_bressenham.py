from graphics import *
import time

def dda(x1,y1,x2,y2):
    win= GraphWin('line_Drawing_DDA ',600,600)
    dx=abs(x1-x2)
    dy=abs(y1-y2)
    if(x1>x2):
        x,y=x2,y2
        x_end=x1
    else:
        x,y=x1,y1
        x_end=x2
    if(dx>dy):
        steps=dx
    else:
        steps=dy
    x_inc=dx/steps
    y_inc=dy/steps

    PutPixle(win, x, y)
    while True:
        x=x+x_inc
        y=y+y_inc
        print(x,y)
        time.sleep(0.01)
        PutPixle(win,round(x),round(y))
        if(x>x_end):
            break
    #win.getMouse()
    #win.close()
def BresenhamLine(x1,y1,x2,y2):
   dx = abs(x2 - x1)
   dy = abs(y2 - y1)
   slope = dy/float(dx)
  
   x, y = x1, y1  
   win = GraphWin('Line_drawing_Brasenham',600, 600)
  
   if slope > 1:
       dx, dy = dy, dx
       x, y = y, x
       x1, y1 = y1, x1
       x2, y2 = y2, x2
   p = 2 * dy - dx
  
   PutPixle(win, x, y)
   for k in range(2, dx):
       if p > 0:
           y = y + 1 if y < y2 else y - 1
           p = p + 2*(dy - dx)
       else:
           p = p + 2*dy
       x = x + 1 if x < x2 else x - 1
       time.sleep(0.01)
       print(x,y)
       PutPixle(win, x, y)
   #win.getMouse()
   #win.close()
def PutPixle(win,x,y):
    po=Point(x,y)
    po.draw(win)
 
def main():
   x1 = int(input("Enter Start X: "))
   y1 = int(input("Enter Start Y: "))
   x2 = int(input("Enter End X: "))
   y2 = int(input("Enter End Y: "))
 
   dda(x1, y1, x2, y2)
   BresenhamLine(x1 ,y1 ,x2 ,y2 )

if __name__ == "__main__":
    main()