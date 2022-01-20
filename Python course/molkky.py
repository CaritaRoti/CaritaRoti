"""
Cmd line based mölkky score calculator for two players named Matti and Teppo.
"""


class Player:
    def __init__(self, name):
        """
        Initializes player with name, points, average points per turn,
        number of throws and a list of hit precentages in a single turn
        :param name: str, player name
        """
        self.__name = name
        self.__points = 0
        self.__avg_points = 0
        self.__number_of_throws = 0
        self.__hits = []

    def get_name(self):
        """
        Returns the name of the player
        :return:
        """
        return self.__name

    def get_points(self):
        """
        Returns the player's points
        :return: int, points
        """
        return self.__points

    def get_hit_percentage(self):
        """
        Calculates and returns the percentage of times
        where the points per throw were over 0
        :return: float, hit precentage
        """
        sum = 0
        for turn in self.__hits:
            sum += turn
        if sum == 0:
            return 0.0
        avg_hit_precentage = round(sum / len(self.__hits), 1)
        return avg_hit_precentage

    def add_points(self, points):
        """
        Adds points to the player's point count according to the rules. Also
        prints some cheering lines if the player is only a few points away
        from winning, or when the player gets a better than usual score on a
        certain turn
        :param points: int, points to be added
        :return:
        """
        self.__number_of_throws += 1
        new_points = self.__points + points
        avg_points_per_throw = new_points / self.__number_of_throws

        if points == 0:
            self.__hits.append(0)
        else:
            self.__hits.append(100)

        if new_points > 50:
            self.__points = 25
            print(f"{self.__name} gets penalty points!")
            return
        self.__points = new_points

        if 40 < self.__points < 49:
            points_to_win = 50 - self.__points
            print(f"{self.__name} needs only {points_to_win} points. "
                  "It's better to avoid knocking down the pins with "
                  "higher points.")

        if self.__number_of_throws > 1 and points > avg_points_per_throw:
            print(f"Cheers {self.__name}!")

    def has_won(self):
        """
        Checks if the player has exactly 50 points
        :return: bool, True if 50pts, False if other than 50pts
        """
        if self.__points == 50:
            return True
        return False


def main():
    player1 = Player("Matti")
    player2 = Player("Teppo")

    throw = 1
    while True:

        # if throw is an even number
        if throw % 2 == 0:
            in_turn = player1

        # else throw is an odd number
        else:
            in_turn = player2

        pts = int(input("Enter the score of player " + in_turn.get_name() +
                        " of throw " + str(throw) + ": "))

        in_turn.add_points(pts)

        if in_turn.has_won():
            print("Game over! The winner is " + in_turn.get_name() + "!")
            return

        print("")
        print("Scoreboard after throw " + str(throw) + ":")
        print(player1.get_name() + ":", player1.get_points(), "p,",
              "hit percentage", player1.get_hit_percentage())
        print(player2.get_name() + ":", player2.get_points(), "p,",
              "hit percentage", player2.get_hit_percentage())
        print("")

        throw += 1


if __name__ == "__main__":
    main()
