準備 (RHEL8)
====================================================
::

	yum install python36
        yum install strace


Do nothing: empty.go
====================================================
::

        
	python3 ./empty.py; echo $?
        strace -y -f python3 ./empty.py
        strace -y -k -f python3 ./empty.py
	strace -c -f python3 ./empty.py
