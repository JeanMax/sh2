# SH2 #

fsh inside! (FlexShell)


### TODO: ###

* handle some more signals : ctrl-z (SIGTSTP, suspend)... stty -a for more infos
* memory leaks in cd, setenv, unsetenv, space_error... probably some more
* > and >> : weird behaviour with echo
* another weird behaviour wrong handled : "ls > 1 2 > 3" -> wrote "2" in 3 if 2 exist
* handle "space errors" : "ls>1>2" -> "ls > 1 > 2"
* handle mixed redirection ):
