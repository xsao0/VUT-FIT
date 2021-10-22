class Point:
        
    def __init__(self, X=0, Y=0): 
        self.x = X
        self.y = Y  
    
    def __sub__(self, other):
        xd = self.x-other.x
        yd = self.y-other.y
        return ("Point("+str(xd)+","+str(yd)+")")

p0 = Point()        
p1 = Point(3, 4)
print(p0-p1)
p2 = Point(1, 2)
result = (p1-p2)
print(result)