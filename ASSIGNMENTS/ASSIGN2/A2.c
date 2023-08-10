/*
Name          : Sushant Patil
Date          : 19/07/2023
Description   : Implement a wc(word count) command with –l –w -c options
Sample execution:
                  When no arguments or file is  passed 
                  ./word_count
                  Hai hello world
                  1 3 16 lines words characters
                       Reads from stdin till EOF (ctrl + d) and count lines words and bytes.
                  2. When one file passed
                  ./word_count file.txt
                  10 20 45
                       Reads from file till EOF (ctrl + d) and count lines words and bytes.
                  3.When Mutilple files are passed
                  ./word_count f1.txt f2.txt
                  5 7 40 f1.txt
                  3 4 10 f2.txt
                  8 11 50 total
                  3. When options passed (-l, -w, -c).
                 ./word_count file.txt –l –w
                  10 20
                     Prints according to given option. Option combination also should work.(Use getopt function )
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// Function to count lines, words, and bytes from a file descriptor
void word_count(int fd, int *lines, int *words, int *bytes) {
    char ch;
    int in_word = 0;
    *lines = *words = *bytes = 0;

    while (read(fd, &ch, 1) > 0) {
        (*bytes)++;

        if (ch == '\n')
            (*lines)++;

        if (ch == ' ' || ch == '\t' || ch == '\n') {
            in_word = 0;
        } else if (in_word == 0) {
            in_word = 1;
            (*words)++;
        }
    }
}

int main(int argc, char *argv[]) {
    int total_lines = 0;
    int total_words = 0;
    int total_bytes = 0;
    int print_lines = 1; // Set default values to print all counts
    int print_words = 1;
    int print_bytes = 1;
    int opt;

    while ((opt = getopt(argc, argv, "lwc")) != -1) {
        switch (opt) {
            case 'l':
                print_lines = 1;
                break;
            case 'w':
                print_words = 1;
                break;
            case 'c':
                print_bytes = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-l] [-w] [-c] [file1] [file2] ...\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (optind >= argc) {
        // If no files passed, read from stdin
        word_count(0, &total_lines, &total_words, &total_bytes);
        if (print_lines)
            printf("%d ", total_lines);
        if (print_words)
            printf("%d ", total_words);
        if (print_bytes)
            printf("%d ", total_bytes);
        printf("\n");
    } else {
        // Loop iterates through the files and processes each one
        for (int i = optind; argv[i] != NULL; i++) {
            int fd = open(argv[i], O_RDONLY);
            if (fd == -1) {
                perror("Error opening file");
                exit(EXIT_FAILURE);
            }

            int lines = 0, words = 0, bytes = 0;
            word_count(fd, &lines, &words, &bytes);
            close(fd);

            if (print_lines)
                printf("%d ", lines);
            if (print_words)
                printf("%d ", words);
            if (print_bytes)
                printf("%d ", bytes);
            printf("%s\n", argv[i]);

            total_lines += lines;
            total_words += words;
            total_bytes += bytes;
        }

        // Print total count if more than one file is processed
        if (argc - optind > 1) {
            if (print_lines)
                printf("%d ", total_lines);
            if (print_words)
                printf("%d ", total_words);
            if (print_bytes)
                printf("%d ", total_bytes);
            printf("total\n");
        }
    }

    return 0;
}

