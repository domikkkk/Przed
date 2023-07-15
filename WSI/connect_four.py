from typing import Tuple
import random
from two_player_games.player import Player
from two_player_games.games.connect_four import ConnectFour, ConnectFourMove


ROW_COUNT = 6
COLUMN_COUNT = 7


class MinMaxSolver:

    def __init__(self, game: ConnectFour):
        self.game = game

    def how_many_in(self, ee):
        return len([i for i in ee if i is not None])

    def evaluate_position(self, is_maximizing_player) -> float:
        if self.game.is_finished():
            if is_maximizing_player:
                return -10000
            elif not is_maximizing_player:
                return 10000
            else:
                return 0
        elif not self.game.is_finished():
            fields = self.game.state.fields
            value = 0
            p1 = self.game.state._other_player.char
            p2 = self.game.state._current_player.char
            for column_id in range(len(fields)):  # verticals
                for start_row_id in range(len(fields[column_id]) - 3):
                    vertical = [fields[column_id][start_row_id + i] for i in range(4)]
                    vertical = [i.char if i is not None else None for i in vertical]
                    if p1 in vertical and p2 not in vertical:
                        value += self.how_many_in(vertical)
                    elif p2 in vertical and p1 not in vertical:
                        value -= self.how_many_in(vertical)

            for start_column_id in range(len(fields) - 3):  # horizontals
                for row_id in range(len(fields[start_column_id])):
                    horizontal = [fields[start_column_id + i][row_id] for i in range(4)]
                    horizontal = [i.char if i is not None else None for i in horizontal]
                    if p1 in horizontal and p2 not in horizontal:
                        value += self.how_many_in(horizontal)
                    elif p2 in horizontal and p1 not in horizontal:
                        value -= self.how_many_in(horizontal)

            for start_column_id in range(len(fields) - 3):  # diagonals
                for start_row_id in range(len(fields[start_column_id]) - 3):
                    diag1 = [fields[start_column_id + i][start_row_id + i] for i in range(4)]
                    diag1 = [i.char if i is not None else None for i in diag1]
                    diag2 = [fields[start_column_id + i][ROW_COUNT - 1 - start_row_id - i] for i in range(4)]
                    diag2 = [i.char if i is not None else None for i in diag2]
                    if p1 in diag1 and p2 not in diag1:
                        value += self.how_many_in(diag1)
                    elif p2 in diag1 and p1 not in diag1:
                        value -= self.how_many_in(diag1)
                    if p1 in diag2 and p2 not in diag2:
                        value += self.how_many_in(diag2)
                    elif p2 in diag2 and p1 not in diag2:
                        value -= self.how_many_in(diag2)
            return value

    def minimax(self, depth, alpha:float, beta:float, is_maximizing_player:bool)->Tuple[float, int]:
        """Returns column index and score"""
        if self.game.is_finished() or depth == 0:
            q = {True: -1, False: 1}[is_maximizing_player]
            y = self.evaluate_position(is_maximizing_player)+depth
            return y, None
        if is_maximizing_player:
            value = -10000
            col = random.choice(self.game.get_moves()).column
            for column in self.get_valid_move():
                self.game.make_move(ConnectFourMove(column))
                new_value = self.minimax(depth-1, alpha, beta, False)[0]
                self.undo_move(column)
                if new_value > value:
                    value = new_value
                    col = column
                if value >= beta:
                    break
                alpha = max(alpha, value)
            return value, col
        else:
            value = 10000
            col = random.choice(self.game.get_moves()).column
            for column in self.get_valid_move():
                self.game.make_move(ConnectFourMove(column))
                new_value = self.minimax(depth-1, alpha, beta, True)[0]
                self.undo_move(column)
                if new_value < value:
                    value = new_value
                    col = column
                if value <= alpha:
                    break
                beta = min(beta, value)
            return value, col


    def get_best_move(self, depth)->int:
        return self.minimax(depth=depth, alpha=-10000, beta=10000, is_maximizing_player=True)

    def get_valid_move(self):
        return [i.column for i in self.game.get_moves()]

    def undo_move(self, move):
        fields = self.game.state.fields[move]
        height = len(fields)
        for i in range(height):
            if fields[height-1-i] is not None:
                self.game.state.fields[move][height-1-i] = None
                self.game.state._current_player, self.game.state._other_player = self.game.state._other_player, self.game.state._current_player
                break


p1 = Player("o")
p2 = Player("x")
game = ConnectFour(size=(COLUMN_COUNT, ROW_COUNT), first_player=p1, second_player=p2)
x = MinMaxSolver(game)
while not x.game.is_finished():
    z = int(input())
    x.game.make_move(ConnectFourMove(z))
    print(x.game)
    y = x.get_best_move(5)
    x.game.make_move(ConnectFourMove(y[1]))
    print(x.game)
