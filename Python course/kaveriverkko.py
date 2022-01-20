"""
A command line based program for analyzing friendship networks.

The program reads the friendship data from a separate file and asks the user
to input the name of the file to be used for this purpose. If the input is an
empty line, the program will use the default file name "friendships.txt".

The user can then use the commands as instructed by the program.
"""


DEFAULT_FILENAME = "friendships.txt"


def read_friendship_network(filename):
    """
    Read a friendship network description file which must contain
    lines in the following format:

        name;friend_1;friend_2;...;friend_n

    At least one friend (i.e. friend_1) must be present on every line
    of the file, but there is no upper limit to how many friends a line
    can contain.

    :param filename: str, Name of the friendship network file to be read.
    :return: The data structure containing the friendship network
             information or None in the case of an error.
    """

    network = {}

    try:
        file = open(filename, mode="r")

        for line in file:
            line = line.rstrip()

            if len(line) > 0 and line[0] == "#":
                continue

            fields = line.split(";")

            if len(fields) < 2:
                print(f"Fatal Error: line '{line}' has too few fields.")
                return None

            for name in fields:
                if not name.isalpha():
                    print(f"Fatal Error: '{name}' is not a valid name.")
                    return None

            person = fields[0]
            for friend in fields[1:]:
                add_friendship(network, person, friend)

        file.close()

        return network

    except OSError:
        print(f"Fatal Error: opening '{filename}' failed.")
        return None


def user_interface(network):
    """
    Implements a simple user interface for the friendship network analyzer.

    The errors resulting from faulty user inputs are not fatal errors
    and the program will continue working after printing an error message.
    Most of the error messages are printed in the command functions as this
    leaves the user interface function very clear and easy to understand.

    :param network: The data structure containing the information about
                    who is friends with whom.
    :return: None
    """

    while True:
        print()
        print("Enter one of the commands "
              "[Pp]rint/[Aa]dd/[Ff]riends/[Cc]ommon/[Qq]uit")
        print("followed by one or more names if needed.")
        fields = input("Enter command: ").strip().split()

        if len(fields) == 0:
            print("Error: an empty line is not a valid command.")
            continue

        command = fields[0]
        rest = fields[1:]

        if command in [ "P", "p" ]:
            print_command(network, rest)

        elif command in [ "A", "a" ]:
            add_command(network, rest)

        elif command in [ "F", "f" ]:
            friends_command(network, rest)

        elif command in [ "C", "c" ]:
            common_friends_command(network, rest)

        elif command in [ "Q", "q" ]:
            print("Farewell cruel world...")
            return

        else:
            print(f"Error: unknown command '{command}'.")


def add_friendship(network, name1, name2):
    """
    Adds a friendship between name1 and name2.

    There are two situations which are not considered as errors
    but the function just doesn't do anything:

    - name1 is the same as name2
    - name1 and name2 are already friends.

    If name1 or name2 is not a name (i.e. it contains other
    characters than letters) an error message is printed and
    network is not modified.

    The friendship relation is always a two way relation:
    name1 will be registered as a friend of name2, and name2
    will be registered as a friend of name1.

    :param network: Data structure containing the friendship network.
                    This parameter will be modified to include the
                    new two way friendship.
    :param name1: str, Person 1's name
    :param name2: str, Person 2's name
    :return: None
    """

    for name in [ name1, name2 ]:
        if not name.isalpha():
            print("Error: '{name}' is not a valid name: friendship not added.")
            return

    if name1 == name2:
        return

    if name1 not in network:
        network[name1] = []
    if name2 not in network[name1]:
        network[name1].append(name2)

    if name2 not in network:
        network[name2] = []
    if name1 not in network[name2]:
        network[name2].append(name1)

    return


def print_command(network, namelist):
    """
    The function neatly prints out the friendship network.
    All the names and friends' names are printed in alphabetical order.
    Friends' names are printed under the name of the person whose friends
    they are. In front of the every friend's name there is "- "
    (minus and space) character combination.

    The parameter namelist must be an empty list, otherwise an error message
    will be printed and function will return back to user interface which
    will continue normally.

    :param network: Contains the friendship network to be printed.
    :param namelist: list, This parameter should be an empty list since
                           print command doesn't require any names after it.
                           It is passed as a parameter only for error checking
                           purposes.
    :return: None
    """

    if len(namelist) != 0:
        print("Error: there was extra text after [Pp]rint command.")
        return

    for name in sorted(network):
        print_friend_list(name, True, network[name])
    return


def print_friend_list(name, print_name, friend_list, list_mark="- "):
    """
    Prints the person's name and the names their friends in an alphabetical
    order in the following format unless requested otherwise:

    name
    - friend_1
    - friend_2
    - friend_n

    :param name: str, the name of the person
    :param print_name: bool, True if the person's name needs to be printed
    :param friend_list: list, list of said person's friends
    :param list_mark: str, a print mark to be used in the list of friends,
                            "- " by default
    :return: None
    """
    if print_name:
        print(name)
    friend_list.sort()
    for friend in friend_list:
        print(f"{list_mark}{friend}")
    return


def add_command(network, namelist):
    """
    Adds a friendship between the first element of the namelist
    and the rest of its elements.

    The friendships are automatically considered to be a two way relationship,
    therefore, if A has B added as his friend, B will also have A added
    as her friend.

    Any errors happening during a call to this functions are not fatal
    errors.  The function will print an error message and return back
    to the user interface which will continue normally.

    In case of any error, network will be left unmodified.

    :param network: The friendship network data structure which will
                    be modified as a result of the call to this function.
    :param namelist: list, This list must have at least two elements.
                     The first one is the name of the person to
                     whom we want to add friends.  The rest of the
                     elements are the names of the friends to be added.
    :return: None
    """

    if len(namelist) < 2:
        print("Error: [Aa]dd command requires minimum two names.")
        return

    for name in namelist:
        if not name.isalpha():
            print(f"Error: '{name}' is not a valid name.")
            return

    for friend in namelist[1:]:
        # Remember, add_friendship function is supposed to automatically
        # add a two way relationship.  Therefore one call to it is enough.
        add_friendship(network, namelist[0], friend)


def friends_command(network, namelist):
    """
    Print out, in aplhabetical order, all the friends of the person whose
    name is the only element in the namelist parameter.

    An error message is printed if the namelist doesn't contain exactly
    one element which is a string of letters.

    An error message is also printed if the name in the namelist does not
    exist in the friendship network.

    These error conditions are not fatal errors. The program will continue
    normally after printing an error message and returning to the
    user interface.

    :param network: Data structure containing the friendship information.
    :param namelist: list, List containing one element: the name of the
                           person whose friends are we interested in printing.
    :return: None
    """

    if len(namelist) != 1:
        print("Error: [Ff]riends command requires exactly one name.")
        return

    name = namelist[0]

    if not name.isalpha():
        print(f"Error: {name} is not a valid name.")
        return

    if not does_network_contain_name(network, name):
        return

    print_friend_list(name, False, network[name], "")


def does_network_contain_name(network, name):
    """
    Checks if the given name exists in the given network, and prints and error
    message if the person is not found.

    :param network: dict, Data structure containing the friendship network.
    :param name: str, Name of the person.
    :return: bool, True if found, False if not found.
    """
    if name not in network:
        print(f"Error: '{name}' is an unknown name.")
        return False
    return True


def common_friends_command(network, namelist):
    """
    Prints, in alphabetical order, the common friends of the two persons whose
    names are in the namelist.

    The following error conditions are possible:

    - There are more or less than two names in the namelist.
    - Either of the names in the namelist contains some other
      characters than letters.
    - Either of the names in namelist does not exist in the network.

    All these errors cause an error message to printed but they are not
    fatal errors: the program will return to user interface and continue
    normally after printing the error message.

    :param network: Data structure containing the friendship information.
    :param namelist: list, A list containing exactly two names.
    :return: None
    """

    if len(namelist) != 2:
        print("[Cc]ommon command requires exactly two names.")
        return

    for name in namelist:
        if not name.isalpha():
            print(f"Error: {name} is not a valid name.")
            return

    for name in namelist:
        if not does_network_contain_name(network, name):
            return

    name1 = namelist[0]
    name2 = namelist[1]

    if name1 == name2:
        print(f"{name1} has no common friends with him/herself.")
        return

    print_common_friends(name1, name2, network)


def print_common_friends(name1, name2, network):
    """
    Makes a list of two people's common friends. Prints the list in
    alphabetical order if common friends are found, or prints an error
    message if no common friends are found.

    :param name1: str, The name of the first person.
    :param name2: str, The name of the second person.
    :param network: dict, Data structure containing the friendship network
    :return: None
    """
    common_friends = [friend for friend in network[name1]
                      if friend in network[name2]]

    if len(common_friends) > 0:
        common_friends.sort()
        for name in common_friends:
            print(name)
        return

    print(f"{name1} and {name2} have no common friends.")
    return


def main():

    filename = input("Enter the name of the input file: ")

    if filename == "":
        filename = DEFAULT_FILENAME

    net = read_friendship_network(filename)

    if net is None:
        return
    else:
        print(f"File {filename} successfully read.")

    user_interface(net)


if __name__ == "__main__":
    main()
