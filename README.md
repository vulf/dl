# dl
> A safer way to 'rm' your files by moving them to the trash

Written in C.
Works only on __Linux__.

## What it does
Safely delete files and directories by moving them to the Trash directory (`$XDG_DATA_HOME/Trash` or `$HOME/.local/share/Trash`).  

## Install
```
$ cd dl/
$ sudo make install
```
## Usage
```
$ dl <path> [..]

Examples:
    $ dl foo.jpg bar.txt
    $ dl *.txt
    $ dl games_dir
```

## Tip
Alias `rm` to `dl` in your SHELL configuration file (`.bashrc` , `.zshrc`). 
```
alias rm='dl'
```

## TODO
- [ ] add support for symbolic files and /tmp
- [ ] create $XDG_DATA_HOME/Trash and subdirs if it does not exist
- [ ] remove duplicates in Trash by renaming identical files
    * related issue: deleting a directory with the same name as that of a dir in Trash throws errors

## Prior art
* https://github.com/sindresorhus/trash-cli
