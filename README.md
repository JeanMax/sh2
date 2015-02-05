# SH2 #

fsh inside! (FlexShell)


### TODO: ###

* norme
* handle some more signals : ctrl-z (SIGTSTP, suspend)... stty -a for more infos
* memory leaks in cd, setenv, unsetenv, space_error... probably some more
* > and >> : weird behaviour with echo -> WHAT??!
* another weird behaviour wrong handled : "ls > 1 2 > 3" -> wrote "2" in 3 if 2 exist
* handle "space errors" : "ls>1>2" -> "ls > 1 > 2"
* check if "<<" actually begin with "?" in (t)csh
* cd error around /Volumes/Data