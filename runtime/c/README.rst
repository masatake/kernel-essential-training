準備 (RHEL8)
====================================================
::

	yum install gcc
        yum install strace


Do nothing: empty.c
====================================================
::

        gcc -o empty empty.c
	./empty; echo $?	
        strace -y -f ./empty
        strace -y -k -f ./empty
	strace -c -f ./empty
