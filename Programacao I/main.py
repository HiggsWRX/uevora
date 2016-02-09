'''Disciplina: Programação I
Trabalho prático ano lectivo 2013/2014
Realizado por Hiago Oliveira (29248) e Rui Oliveira (31511)
'''

class Village:

    # Constructor method
    # Used to create a new instance of Village, taking in arguments like
    # its size and population, then builds the board used throughout the
    # program
    # inputs: size, population
    # outputs: none

    def __init__(self, size, population):
        self.size = size
        self.population = population
        self.board = []
        self.locations = dict()

        for y in range(self.size):
            self.board.append([])
            for x in range(self.size):
                self.board[y].append(0)

    # populate() method
    # Iterates over the number of population to fill the board with each
    # villager's coordinates
    # inputs: none
    # outputs: none

    def populate(self):

        global bad_file

        for i in range(self.population):
            while True:
                try:
                    if io_method == 1:
                        coords = input('{:d} Coords: '.format(i + 1)).split()
                    elif io_method == 2:
                        coords = f_input[i + 2].split()

                    for j in range(len(coords)):
                        coords[j] = int(coords[j])

                    # Storing in the dictionary the given coordinates. for eg:
                    # {1: [0, 0, 3, 2]}
                    self.locations[i + 1] = coords

                    # Checking if the given coordinates are already filled
                    if self.board[coords[1]][coords[0]] == 0:
                        if self.board[coords[3]][coords[2]] == 0:
                            self.board[coords[1]][coords[0]] = i + 1
                            self.board[coords[3]][coords[2]] = i + 1
                            break
                        else:
                            if io_method == 2:
                                print('Bad input file, please review it.')
                                bad_file = True
                                return
                            else:
                                raise ValueError
                    else:
                        if io_method == 2:
                            print('Bad input file, please review it.')
                            bad_file = True
                            return
                        else:
                            raise ValueError
                except ValueError:
                    print('Coord already occupied... Try again.')
                except IndexError:
                    print('Invalid coordinate format...')

# solve(b, p, l)
# The solve function has all the necessary arguments to start solving the
# puzzle, it will first create a pool of all possible paths from point to point
# then finding the correct combination of paths through other functions
# inputs: board, population, locations
# "locations" is a dictionary of villagers, each one with its corresponding
# coordinates for their potion and house
# outputs: none

def solve(board, population, locations):
    solved_board = board.copy()
    paths = {}
    solve_key = []
    vil_keys = []

    # Retrieves from the dicionary the coordinates for the villager's potion
    # then finds all possible paths from the potion to the house using the
    # path_finder() function
    for i in range(1, population + 1):
        x = locations[i][0]
        y = locations[i][1]
        paths[i] = path_finder(solved_board, i, y, x)

    # Creates a list with the villagers, for eg if this village has 3
    # inhabitants, vil_keys will be [1, 2, 3]
    for i in paths.keys():
        vil_keys.append(i)

    # sort_out() explanation further below
    sort_out(paths, solved_board, vil_keys, 0, [], solve_key)

    # io_method dictates whether the user chose to input values manually (1)
    # or by providing a file (2). The only difference is if io_method == 1
    # the solved puzzle will be printed directly in the screen instead of
    # being written to a file
    if io_method == 1:
        if not solve_key:
            print('\nAlesia')
        else:
            print('\nToutatis\n')
            for i in range(len(vil_keys)):
                for j in paths[vil_keys[i]][solve_key[i]]:
                    solved_board[j[0]][j[1]] = vil_keys[i]

            draw_board(solved_board)

    elif io_method == 2:
        fout_name = fin_name[:3] + '.out'
        temp = open(fout_name, 'w+')
        if not solve_key:
            temp.write('Alesia')
        else:
            temp.write('Toutatis\n')
            for i in range(len(vil_keys)):
                for j in paths[vil_keys[i]][solve_key[i]]:
                    solved_board[j[0]][j[1]] = vil_keys[i]

            write_board(solved_board, temp)
            temp.close()
        print('%s has been created at your CWD.' % fout_name)

    return

# path_finder()
# Used as an intermediary function to create the list of all possible paths,
# lather filled by path_crawler()
# inputs: board, i, y, x
# "i" is the current villager which possible paths are being generated.
# x and y are the coords of that villager's potion, or the starting point.
# outputs: pos_path
# "pos_path" is a list fileld with all possible paths from 'a' to 'b'.

def path_finder(board, i, y, x):
    pos_path = []
    path_crawler(board, i, y, x, pos_path, [], y, x)

    return pos_path

# Directions used to travel the board
dirs = [(0, 1), (1, 0), (0, -1), (-1, 0)]

# path_crawler()
# Generates all possible paths from 'a' to 'b', recursively
# inputs: board, i, y, x, path_list, stack, startY, startX
# outputs: none, but modifies path_list (possible paths)

def path_crawler(board, i, y, x, path_list, stack, startY, startX):

    # Previously visited/tested paths are marked with a *
    if board[y][x] == '*':
        return

    stack.append((y, x))

    if board[y][x] == 0 or (y == startY and x == startX):
        lastVal = board[y][x]
        board[y][x] = '*'

        for d in dirs:
            if not valid(x + d[0], y + d[1], len(board)):
                continue
            path_crawler(board, i, y + d[1], x + d[0], path_list, stack,
                         startY, startX)

        board[y][x] = lastVal
    elif board[y][x] == i:
        path_list.append(list(stack))

    stack.pop()

# valid()
# Checks if the given coordinate is valid, i.e., if it's within the board
# inputs: x, y, size
# outputs: boolean
# True being a valide coordinate, False otherwise

def valid(x, y, size):
    return x < size and y < size and x >= 0 and y >= 0

# sort_out()
# Receives a dictionary (paths) with all villagers and their possible solutions
# which then sorts out and finds the correct solution key, by excluding the
# paths that intersect with eachother and combining a set of paths that can be
# used to solve the puzzle
# inputs: paths, board, vil, index, stack, final_sol
# "vil" is a list of villagers, for eg if 3 villagers exist vil = [1, 2, 3]
# "final_sol" is a list of the correct key to solve the puzzle, for further
# explanation check the report.
# "stack" list used to store possible paths, pops the wrong ones.

def sort_out(paths, board, vil, index, stack, final_sol):

    if len(vil) == 1 and index == 1:
        return True

    if index == len(vil):
        return len(stack) == len(board) * len(board[index - 1])

    for current in range(0, len(paths[vil[index]])):
        path = paths[vil[index]][current]

        if intersects(path, stack):
                continue

        final_sol.append(current)

        if sort_out(paths, board, vil, index + 1, stack + path, final_sol):
            return True

        final_sol.pop()
    return False

# intersects()
# Returns whether an item is present in both lists
# inputs: listA, listB
# outputs: boolean

def intersects(listA, listB):
    for i in listA:
        if i in listB:
            return True
    return False

# draw_board()
# Used to properly print "board", or a list of lists
# inputs: board
# outputs: none

def draw_board(board):
    for item in board:
        for j in item:
            print(j, end=' ')
        print()

# write_board()
# Same as draw_board(), but instead of printing directly to the screen,
# writes it in a file
# inputs: board, file
# outputs: none

def write_board(board, file):
    for item in board:
        for j in item:
            file.write(str(j) + ' ')
        file.write('\n')


if __name__ == '__main__':

    # While True, the game runs. If the user later chooses not to play again,
    # a 'break' statement will break out of it.
    while True:

        bad_file = False

        print('Input values manually(1) or import them from a file(2)? ',
              end='')

        while True:
            try:
                io_method = int(input())

                if io_method != 1 and io_method != 2:
                    raise ValueError
                else:
                    break
            except ValueError:
                print('Not a valid choice...')

        if io_method == 2:
            f_input = []

            while True:
                try:
                    fin_name = input('Please enter the file name: ')
                    temp = open(fin_name, 'r')

                    # Fills a list f_input with the contents of a file
                    for line in temp:
                        f_input.append(line.rstrip())

                    temp.close()
                    break
                except FileNotFoundError:
                    print('Error: No such file or directory.')

        while True:
            try:
                if io_method == 1:
                    board_size = int(input('Village size: '))
                elif io_method == 2:
                    board_size = int(f_input[0])

                if board_size < 2 or board_size > 7:
                    if io_method == 2:
                        print('Bad input file, please review it.')
                        bad_file = True
                        break
                    else:
                        raise ValueError
                else:
                    break
            except ValueError:
                print('Village size must be AN INTEGER between 2 and 7.')

        # These "bad_file checks" are used to know if the file provided
        # contains a bad variable or coordinate, eg a larger village than
        # permitted, or a coordinate already occupied..
        # These checks occur twice more down below.
        if bad_file:
            input('Press Enter to exit...')
            break

        while True:
            try:
                if io_method == 1:
                    vil_population = int(input('Village population: '))
                elif io_method == 2:
                    vil_population = int(f_input[1])

                if vil_population < 1 or vil_population > board_size:
                    if io_method == 2:
                        print('Bad input file, please review it.')
                        bad_file = True
                        break
                    else:
                        raise ValueError
                else:
                    break
            except ValueError:
                print('Population must be between 1 and village size.')

        if bad_file:
            input('Press Enter to exit...')
            break

        # Creates a new instance of Village and then populates it
        new_game = Village(board_size, vil_population)
        new_game.populate()

        if bad_file:
            input('Press Enter to exit...')
            break

        #start solving
        solve(new_game.board, vil_population, new_game.locations)

        replay = input('\nReplay? Y/N ... ')
        if replay == 'n' or replay == 'N':
            break
        elif replay == 'y' or replay == 'Y':
            continue
        else:
            print('Interpreting vague answer as... no.')
            input('Press Enter to exit...')
            break
