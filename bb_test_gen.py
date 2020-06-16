import random

receiver_coords = [
    [0,0,0]
]

NUM_RECEIVERS = 4
DIMENSIONS = 3

VS = 343

for i in range(NUM_RECEIVERS - 1):
    temp_coord = []
    for i in range(DIMENSIONS):
        temp_coord.append(random.randint(0,10))
    
    receiver_coords.append(temp_coord)

bug_coord = []
for i in range(DIMENSIONS):
    bug_coord.append(random.randint(0,10))


bug_to_rx_distances = []

for i in range(NUM_RECEIVERS):
    distance = ((bug_coord[0] - receiver_coords[i][0]) ** 2) + ((bug_coord[1] - receiver_coords[i][1]) ** 2) + ((bug_coord[2] - receiver_coords[i][2]) ** 2)
    distance = distance ** (1/2)
    bug_to_rx_distances.append(distance)

toas = []

for i in range(NUM_RECEIVERS):
    toas.append(bug_to_rx_distances[i]/VS)


print('Receiver Coords:', receiver_coords)
print('Bug Coord:', bug_coord)
print('Bug to Rx Distances', bug_to_rx_distances)
print('TOAs:', toas)