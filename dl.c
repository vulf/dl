#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
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
    tdir = (getenv("XDG_DATA_HOME")) ? getenv("XDG_DATA_HOME"): strcat(hdir, "/.local/share/Trash");
    for(i=1;i<argc;i++){
        abspath = realpath(argv[i],NULL);
        snprintf(tfile, MAX, "%s/files/%s", tdir, basename(argv[i]) );
        ret = rename(abspath, tfile); 
        if(ret == 0){
            printf("moved '%s' to trash\n", basename(argv[i]));
        }
 
        // TRASH INFO
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
