import math
import random
coords_robot = []

#radius of the root of the turbine blade
r = 3.5

#coordinates of base transceivers
coords_t1 = [0, 0, 0]
coords_t2 = [0, 3.5, 0]
coords_t3 = [0, 0, 3.5]
i = 0

#randomly generating coordinates for the robot's position
coords_robot.append(round(random.uniform(0.00, 50.00), 4))
coords_robot.append(round(random.uniform(-r, r), 4))
coords_robot.append(round(random.uniform(-r, r), 4))

 #Euclidian distance between base transceivers and the robot trnsceiver
l_1 = math.sqrt((coords_robot[0]-coords_t1[0])**2 + (coords_robot[1]-coords_t1[1])**2 + (coords_robot[2]-coords_t1[2])**2)
l_2 = math.sqrt((coords_robot[0]-coords_t2[0])**2 + (coords_robot[1]-coords_t2[1])**2 + (coords_robot[2]-coords_t2[2])**2)
l_3 = math.sqrt((coords_robot[0]-coords_t3[0])**2 + (coords_robot[1]-coords_t3[1])**2 + (coords_robot[2]-coords_t3[2])**2)

#printing generated coordinates
print("x-coordinate: " + str(coords_robot[0]))
print("y-coordinate: " + str(coords_robot[1]))
print("z-coordinate: " + str(coords_robot[2]))

#printing Euclidian distances
print("Distance 1: " + str(l_1))
print("Distance 2: " + str(l_2))
print("Distance 3:" + str(l_3))
