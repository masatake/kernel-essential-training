usage()
{
    echo "Usage:"
    echo "  $1 [-d|--downcase] WORD..."
    echo "  $1 [-v|--version]"    
    echo "  $1 [-h|--help]"
}

upcase()
{
    echo "$1" |  tr a-z A-Z
}
downcase()
{
    echo "$1" |  tr A-Z a-z
}
