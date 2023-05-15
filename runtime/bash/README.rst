準備 (RHEL8)
====================================================
::

        yum install strace


Do nothing: empty.c
====================================================
::

	./empty.sh; echo $?	
        strace -y -f ./empty.sh
        strace -y -k -f ./empty.sh
	strace -c -f ./empty.sh
