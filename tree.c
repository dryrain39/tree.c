#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void print_tree(int height, int padding) {
    int colors[] = {31, 32, 33, 34, 35, 36, 37};

    for (int current_height = height; current_height; current_height--) {
        for (int pad = current_height - 1 + padding; pad; pad--)
            printf(" ");

        for (int star = (height - current_height) * 2 + 1; star; star--) {
            if (star % 2)
                printf("\x1B[%dm*\x1B[0m", colors[rand() % 7]);
            else
                printf(" ");
        }

        printf("\n");
    }
}

int get_tree_bottom_length(int height) {
    return height + height - 1;
}

void print_center(char *str, int width) {
    for (int p = (width - strlen(str)) / 2; p; p--)
        printf(" ");
    printf("%s", str);
}

int main() {
    srand(time(NULL));

    while(1)
    {
        struct winsize w;

        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

        print_tree(3, (w.ws_col - get_tree_bottom_length(3)) / 2);
        print_tree(5, (w.ws_col - get_tree_bottom_length(5)) / 2);
        print_tree(7, (w.ws_col - get_tree_bottom_length(7)) / 2);

        print_center("Merry Christmas! \n", w.ws_col + 3);

        sleep(1);
        printf("\e[1;1H\e[2J");
    }

    return 0;
}
