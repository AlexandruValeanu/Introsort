for CURRENT_GRAPH in range(7):
    f = open('results.txt')
    lines = []

    for line in f:
        lines.append(line)

    def get_line():
        _line = lines[0]
        del lines[0]
        return _line

    print(CURRENT_GRAPH)

    ys_red = []
    ys_blue = []
    ys_orange = []
    ys_purple = []

    for data in range(7):
        get_line()
        N, V = map(int, get_line().split(" "))

        for test in range(7):
            a, b = map(float, get_line().split(" "))
            # print(a, b)

            if test == CURRENT_GRAPH:
                ys_red.append(a)
                ys_blue.append(b)

    for data in range(7):
        get_line()
        N, V = map(int, get_line().split(" "))

        for test in range(7):
            a, b = map(float, get_line().split(" "))
            # print(a, b)

            if test == CURRENT_GRAPH:
                ys_orange.append(a)
                ys_purple.append(b)

    print("ys1 = ", ys_red)
    print("ys2 = ", ys_blue)
    print("ys3 = ", ys_orange)
    print("ys4 = ", ys_purple)
    print()