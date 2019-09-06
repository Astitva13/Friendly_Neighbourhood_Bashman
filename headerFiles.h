#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <errno.h>   
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#define buff_size 1000000

extern int idx;
extern int counter;
extern int pidarr[10000];
extern int pidctr[10000];
extern char pidcmd[10000][100];
extern char s[10000];
extern char s_save[10000];
extern char inputstring[10000];
extern char homedir[10000];
extern char currdir[10000];
extern char prevdir[10000];
extern char* name;
extern int stx;
extern int fl_a,fl_l,fl_dir,ctdir;
extern struct stat fileStat;


extern void truncatedir(char * name);