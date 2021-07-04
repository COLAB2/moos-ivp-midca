from __future__ import division
import math

def sim_to_grid(x, y):
    # side length of a grid cell
    side = 80
    # grid n*m !
    grid_m = 5

    # starting positions
    start_x = -141
    start_y = 76

    cell_x = (start_x - x)/side
    cell_y = (grid_m -1) - ((start_y - y)/side)

    return abs(int(math.ceil(cell_x))), abs(int(math.ceil(cell_y)))

def grid_to_sim(x,y):
    # starting positions
    start_x = -141
    start_y = 76
    # side length of a grid cell
    side = 80
    # grid n*m !
    grid_m = 5

    y = grid_m-1 - y

    grid_start_x = start_x + x*80
    grid_end_x = start_x + (x+1)*80

    grid_start_y = start_y - (y)*80
    grid_end_y = start_y - (y+1)*80

    x = (grid_start_x + grid_end_x)/2
    y = (grid_start_y + grid_end_y)/2

    return x,y

def get_abstract_position(s):
    start_x = -141
    start_y = 76 - 80*5
    side = 80
    tags = []
    grid_n = 5
    grid_m = 5
    for i in range(grid_n):
        for j in range(grid_m):
            tags.append([start_x + j*80, start_y + i*80])

    print tags

    return tags[s][0], tags[s][1], 20



print(sim_to_grid(100, -245))
