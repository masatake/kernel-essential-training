準備 (RHEL8)
====================================================
::

	yum install golang
        yum install strace


Do nothing: empty.go
====================================================
::

        go build empty.go
	./empty; echo $?
        strace -y -f ./empty
        strace -y -k -f ./empty
	strace -c -f ./empty
