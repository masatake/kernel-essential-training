準備 (RHEL8)
====================================================
::

        yum install strace


Do nothing: empty.go
====================================================
::

        
	./empty.py; echo $?
        strace -y -f ./empty.py
        strace -y -k -f ./empty.py
	strace -c -f ./empty.py
