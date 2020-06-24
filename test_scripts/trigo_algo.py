import math
rad = input("Enter the radius at the root of the wind turbine blade (in metres): ")
d_1 = input("Enter distance between transceiver 1 and robot transceiver (in metres): ")
d_2 = input("Enter distance between transceiver 2 and robot transceiver (in metres): ")
d_3 = input("Enter distance between transceiver 3 and robot transceiver (in metres): ")
rad = float(rad)
d_1 = float(d_1)
d_2 = float(d_2)
d_3 = float(d_3)

# Coordinates of transceiver 1: [0, 0, 0]
# Coordinates of transceiver 2: [0, rad, 0]
# Coordinates of transceiver 3: [0, 0, rad]

# calculating x and y coordinates of the robot by taking transceivers 1 and 2
cos_C = (d_1**2 + d_2**2 - rad**2)/(2 * d_1 * d_2)
sin_C = math.sin(math.acos(cos_C))
sin_A = (d_1 * sin_C)/rad
sin_B = (d_2 * sin_C)/rad
cos_B = math.cos(math.asin(sin_B))
if math.degrees(math.asin(sin_A) + math.asin(sin_B) + math.asin(sin_C))<179.9 or math.degrees(math.asin(sin_A) + math.asin(sin_B) + math.asin(sin_C))>181.1:
    x = d_1 * math.sin(math.pi - math.asin(sin_B))
    y = d_1 * math.cos(math.pi - math.acos(cos_B))
else:
    x = d_1 * sin_B
    y = d_1 * cos_B

# calculating z coordinate of the robot by taking transceivers 1 and 3
cos_F = (d_1**2 + d_3**2 - rad**2)/(2 * d_1 * d_3)
sin_F = math.sin(math.acos(cos_F))
sin_D = (d_1 * sin_F)/rad
sin_E = (d_3 * sin_F)/rad
cos_E = math.cos(math.asin(sin_E))
if math.degrees(math.asin(sin_D) + math.asin(sin_E) + math.asin(sin_F))<179.9 or math.degrees(math.asin(sin_D) + math.asin(sin_E) + math.asin(sin_F))>181.1:
    z = d_1 * math.cos(math.pi - math.asin(sin_E))
else:
    z = d_1 * cos_E

#printing the calculated coordinates of the robot
print("x-coordinate of the robot: " + str(x))
print("y-coordinate of the robot: " + str(y))
print("z-coordinate of the robot: " + str(z))
