準備 (RHEL8)
====================================================
::

        yum install java-1.8.0-openjdk-devel
        yum install strace


Do nothing: empty.c
====================================================
::

	javac empty.java
        strace -y -f java empty
        strace -y -k -f java empty
	strace -c -f java empty
