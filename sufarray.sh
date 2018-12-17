
PROGRAM_NAME="sufarray"

build() {
    gcc source/*.c -o $PROGRAM_NAME
}

run() {
    build
    ./$PROGRAM_NAME "$@"
    rm -rf $PROGRAM_NAME
}

test_with_valgrind() {
    build
    echo "uh"
    valgrind --leak-check=full ./$PROGRAM_NAME
    rm -rf $PROGRAM_NAME
}

case $1 in
    "--build")
        build
        ;;

    "--run")
        run "$@"
        ;;

    "--valgrind")
        test_with_valgrind "$@"
        ;;
esac
