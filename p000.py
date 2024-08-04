
#-----Statement of Authorship----------------------------------------#
#
#  This is an individual assessment task for QUT's teaching unit
#  IFB104, "Building IT Systems", Semester 2, 2023.  By submitting
#  this code I agree that it represents my own work.  I am aware of
#  the University rule that a student must not act in a manner
#  which constitutes academic dishonesty as stated and explained
#  in QUT's Manual of Policies and Procedures, Section C/5.3
#  "Academic Integrity" and Section E/2.1 "Student Code of Conduct".
#
#  Put your student number here as an integer and your name as a
#  character string:
#
student_number = 11644672
student_name = "Suraj Patel"

#
#  NB: All files submitted for this assessable task will be subjected
#  to automated plagiarism analysis using a tool such as the Measure
#  of Software Similarity (http://theory.stanford.edu/~aiken/moss/)
#  or Copydetect (https://pypi.org/project/copydetect/).
#
#--------------------------------------------------------------------#



#-----Assessment Task 1 Description----------------------------------#
#
#  This assessment task tests your skills at processing large data
#  sets, creating reusable code and following instructions to display
#  a complex visual image.  The incomplete Python program below is
#  missing a crucial function.  You are required to complete this
#  function so that when the program runs it fills a grid with various
#  symbols, using data stored in a list to determine which symbols to
#  draw and where.  See the online video instructions for
#  full details.
#
#  Note that this assessable assignment is in multiple parts,
#  simulating incremental release of instructions by a paying
#  "client".  This single template file will be used for all parts
#  and you will submit your final solution as this single Python 3
#  file only, whether or not you complete all requirements for the
#  assignment.
#
#  This file relies on other Python modules but all of your code
#  must appear in this file only.  You may not change any of the code
#  in the other modules and you should not submit the other modules
#  with your solution.  The markers will use their own copies of the
#  other modules to test your code, so your solution will not work
#  if it relies on changes made to any other files.
#
#--------------------------------------------------------------------#  



#-----Preamble-------------------------------------------------------#
#
# This section imports necessary functions used to execute your code.
# You must NOT change any of the code in this section, and you may
# NOT import any non-standard Python modules that need to be
# downloaded and installed separately.
#

# Import standard Python modules needed to complete this assignment.
# You should not need to use any other modules for your solution.
# In particular, your solution must NOT rely on any non-standard
# Python modules that need to be downloaded and installed separately,
# because the markers will not have access to such modules.
from turtle import *
from math import *
from random import *
from sys import exit as abort
from os.path import isfile

# Confirm that the student has declared their authorship
if not isinstance(student_number, int):
    print('\nUnable to run: No student number supplied',
          '(must be an integer), aborting!\n')
    abort()
if not isinstance(student_name, str):
    print('\nUnable to run: No student name supplied',
          '(must be a character string), aborting!\n')
    abort()

# Import the functions for setting up the drawing canvas
config_file = 'assignment_1_config.py'
if isfile(config_file):
    print('\nConfiguration module found ...\n')
    from assignment_1_config import *
else:
    print(f"\nCannot find file '{config_file}', aborting!\n")
    abort()

# Define the function for generating data sets in Task 1B,
# using the imported raw data generation function if available,
# but otherwise creating a dummy function that just returns an
# empty list
data_file = 'assignment_1_data_source.py'
if isfile(data_file):
    print('Data generation module found ...\n')
    from assignment_1_data_source import raw_data
    def data_set(new_seed = randint(0, 99999)):
        return raw_data(new_seed) # return the random data set
else:
    print('No data generation module available ...\n')
    def data_set(dummy_parameter = None):
        return []

#
#--------------------------------------------------------------------#



#-----Student's Solution---------------------------------------------#
#
#  Complete the assignment by replacing the dummy function below with
#  your own function and any other functions needed to support it.
#  All of your solution code must appear in this section.  Do NOT put
#  any of your code in any other sections and do NOT change any of
#  the provided code except as allowed by the comments in the next
#  section.
#

# All of your code goes in, or is called from, this function.
# In Task 1B ensure that your code does NOT call functions data_set
# or raw_data because they're already called by the main program
# below.
# Define the constants for the grid dimensions and the home positions
GRID_SIZE = 20  # Assuming a 20x20 grid as per the given setup
HALF_GRID = GRID_SIZE // 2  # Half of the grid

# Home positions for the competitors
HOME_A = (HALF_GRID - 1, HALF_GRID - 1)  # Top-left for Competitor A
HOME_B = (HALF_GRID, HALF_GRID)  # Bottom-right for Competitor B

# Directions for movement
DIRECTIONS = {
    'north': (0, 1),
    'south': (0, -1),
    'east': (1, 0),
    'west': (-1, 0)
}

# Define a function to check if a given position is within the grid boundaries
def is_within_grid(pos):
    return 0 <= pos[0] < GRID_SIZE and 0 <= pos[1] < GRID_SIZE

# Define the main function to visualize the data
def visualise_data(moves):
    # Initial positions
    pos_a, pos_b = HOME_A, HOME_B
    visited_cells = set([HOME_A, HOME_B])  # Cells visited by either competitor
    
    # Counters for the cells captured by each competitor
    captured_a, captured_b = 0, 0
    
    # Iterate over the moves in the data set
    for move in moves:
        _, competitor, direction = move
        
        # Determine the new position based on the direction
        dx, dy = DIRECTIONS[direction]
        if competitor == "Competitor A":
            new_pos = (pos_a[0] + dx, pos_a[1] + dy)
            # Check if the move is valid
            if is_within_grid(new_pos) and new_pos not in visited_cells:
                pos_a = new_pos  # Update position
                # Check if the cell is in the opponent's half and increment the counter
                if new_pos[0] >= HALF_GRID:
                    captured_a += 1
            visited_cells.add(pos_a)  # Mark the cell as visited
        else:  # Competitor B
            new_pos = (pos_b[0] + dx, pos_b[1] + dy)
            # Check if the move is valid
            if is_within_grid(new_pos) and new_pos not in visited_cells:
                pos_b = new_pos  # Update position
                # Check if the cell is in the opponent's half and increment the counter
                if new_pos[0] < HALF_GRID:
                    captured_b += 1
            visited_cells.add(pos_b)  # Mark the cell as visited
    
    # At the end, display the number of cells captured by each competitor
    # For now, we'll print it (will need to update this for the final visualization)
    print(f"Competitor A captured {captured_a} cells from Competitor B's half.")
    print(f"Competitor B captured {captured_b} cells from Competitor A's half.")

# Test the function with a sample data set
sample_data = [
    (0, "Competitor A", "east"),
    (1, "Competitor B", "west"),
    (2, "Competitor A", "south"),
    (3, "Competitor B", "north"),
    (4, "Competitor A", "east"),
    (5, "Competitor B", "west"),
    (6, "Competitor A", "south")
]
#visualise_data(sample_data)


#
#--------------------------------------------------------------------#



#-----Main Program to Run Student's Solution-------------------------#
#
# This main program configures the drawing canvas, calls the student's
# function and closes the canvas.  Do NOT change any of this code
# except as allowed by the comments below.  Do NOT put any of
# your solution code in this section.
#

# Configure the drawing canvas
#
# ***** You can add arguments to this function call to modify
# ***** features of the drawing canvas such as the background
# ***** and line colours, etc
create_drawing_canvas()

# Create the data set and pass it to the student's function
#
# ***** While developing your Task 1B code you can call the
# ***** "data_set" function with a fixed seed below for the
# ***** random number generator, but your final solution must
# ***** work with "data_set()" as the function call,
# ***** i.e., for any random data set that can be returned by
# ***** the function when called with no seed
visualise_data(data_set()) # <-- no argument for "data_set" when assessed

# Exit gracefully
#
# ***** Do not change this function call
release_drawing_canvas(student_name)

#
#--------------------------------------------------------------------#
