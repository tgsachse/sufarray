# Some functions that make this repository easier to work with.
# Written by Tiger Sachse.

PROGRAM_NAME="sufarray"

# Build the program.
build_program() {
    gcc source/*.c -o $PROGRAM_NAME
}

# Run the program and clean up afterwards.
run_program() {
    build_program
    ./$PROGRAM_NAME "$@"
    rm -rf $PROGRAM_NAME
}

# Test the program with Valgrind.
test_program() {
    build_program
    valgrind --leak-check=full ./$PROGRAM_NAME "$@"
    rm -rf $PROGRAM_NAME
}

# Entry point of the script.
case $1 in
    "--build")
        build_program
        ;;

    "--run")
        run_program "${@:2}"
        ;;

    "--test")
        test_program "${@:2}"
        ;;
esac
