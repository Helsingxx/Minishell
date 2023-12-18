Compile the program with Make. If you need to change the compiler rules, add your flags to the CFLAGS variables.
If you need to change the linker rules, add them to LDFLAGS.
You will need to install the GNU readline library in order to use this program.

Usage:
./minishell
minishell$: echo "test" >> file1 | cat test | cat | cat | ls
...
minishell$: echo $?
...
minishell$: export myvar
minishell$: export myvar=value
minishell$: env
...
minishell$: unset env
minishell$: cd $(SOMEDIRECTORY)
minishell$: /bin/ls
...
minishell$: pwd
...
minishell$: cat << x
>hello$HOME
>x
hello/USER/helsing
minishell$: cat << "x"
>$USER
>x
$USER
minishell$: echo hey > a > b > c > d > e
minishell$: rm a b c d
minishell$: cat < e
...
minishell$: exit 255
sh$: echo $?
255
[EOF]
