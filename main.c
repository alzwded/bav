#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NELEMENS(a) ( sizeof(a) / sizeof((a)[0]) )

typedef struct {
    char const* name;
    int (*f)(int argc, char* argv[]);
} command_t;

static int command_comparator(void const* left, void const* right) {
    command_t const* a = static_cast<command_t const*>(left);
    command_t const* b = static_cast<command_t const*>(right);

    return strcmp(a->name, b->name);
}

extern int command_branch(int argc, char* argv[]);
extern int command_checkout(int argc, char* argv[]);
extern int command_commit(int argc, char* argv[]);
extern int command_init(int argc, char* argv[]);
extern int command_join(int argc, char* argv[]);
extern int command_log(int argc, char* argv[]);
extern int command_release(int argc, char* argv[]);
extern int command_revert(int argc, char* argv[]);

static command_t g_commands[] = {
    { "branch", &command_branch },
    { "checkout", &command_checkout },
    { "commit", &command_commit },
    { "init", &command_init },
    { "join", &command_join },
    { "log", &command_log },
    { "release", &command_release },
    { "revert", &command_revert },
};

static void usage()
{
    fprintf(stderr, "TODO\n");
    exit(255);
}

int main(int argc, char* argv[])
{
    if(argc < 2) usage();

    command_t* option = bsearch(argv[1], g_commands, NELEMENTS(g_commands), sizeof(command_t), &command_comparator);
    if(option == &g_commands[NELEMENTS(g_commands)]) usage();
    else return option->f(argc - 2, argv + 2);

    return 255;
}
