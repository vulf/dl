#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <libgen.h>
#define MAX 1000

int main(int argc, char *argv[]){
    char TRASH_DIR[MAX], HOME_DIR[MAX], FULLPATH[MAX], TRASH_FILE[MAX], TRASH_INFO[MAX], CUR_TIME[50];
    char *tdir = TRASH_DIR, *hdir = HOME_DIR, *abspath = FULLPATH, *tfile = TRASH_FILE, *tinfo = TRASH_INFO;
    int i, ret;
    FILE *fp;
    time_t rawtime;
    struct tm *info;

    hdir = getenv("HOME");
    tdir = (getenv("XDG_DATA_HOME")) ? getenv("XDG_DATA_HOME"): strcat(hdir, "/.local/share");
    strcat(tdir, "/Trash");
    
    if(argc<2){
        fprintf(stderr, "error: missing operand\n"
                        "Usage: dl <path> [..]\n");
        return 1;
    }
    for(i=1;i<argc;i++){
        abspath = realpath(argv[i],NULL);
        // Check if file exists
        if( access(abspath, F_OK) != 0 ){
            fprintf(stderr, "error: cannot delete '%s': No such file or directory\n", basename(argv[i]));
            continue;
        }
        // Move to trash
        snprintf(tfile, MAX, "%s/files/%s", tdir, basename(argv[i]) );
        ret = rename(abspath, tfile); 
        if(ret == 0){
            printf("moved '%s' to trash\n", basename(argv[i]));
        }
        else{
            fprintf(stderr, "error: cannot delete '%s': ", basename(argv[i]));
            perror("");
            continue;
        }
 
        // Trash info
        snprintf(tinfo, MAX, "%s/info/%s.trashinfo", tdir, basename(argv[i]));
        time( &rawtime );
        info = localtime( &rawtime );
        strftime(CUR_TIME, 50, "%Y-%m-%dT%H:%M:%S", info);
        fp = fopen(tinfo, "w");
        fprintf(fp, "[Trash Info]\n"
                     "Path=%s\n"
                     "DeletionDate=%s\n", abspath, CUR_TIME);
        fclose(fp);

    }
    return 0;
}
