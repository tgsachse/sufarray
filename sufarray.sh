# Operations script to make working with this repository easier.
# Written by Tiger Sachse.

PROGRAM_NAME="sufarray"

# Build the program.
build() {
    gcc source/*.c -o $PROGRAM_NAME
}

# Run the program and clean up afterwards.
run() {
    build
    ./$PROGRAM_NAME "$@"
    rm -rf $PROGRAM_NAME
}

# Test the program with Valgrind.
test_with_valgrind() {
    build
    valgrind --leak-check=full ./$PROGRAM_NAME "$@"
    rm -rf $PROGRAM_NAME
}

# Entry point of the script.
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
