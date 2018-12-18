# sufarray
An implementation of suffix arrays in C. This project was made for fun and is not intended to be used as a library. Better, faster implementations of suffix arrays exist, like Yuta Mori's [divsufsort](https://github.com/y-256/libdivsufsort) library.

# download
To download and use this project, clone the repository with the following command. This command requires `git` to be installed on your system.
```
git clone https://github.com/tgsachse/sufarray.git
```

# usage
This project is easy to use and only requires one command:
```
bash sufarray.sh --run <file> [<pattern> <pattern> <pattern> ...]
```
- `<file>` : The path to the text file you'd like to create a suffix array for.
- `<pattern>` : A string pattern you want to search for in the resulting suffix array. This is an optional argument.

# example
The following example creates a suffix array from the input file `examples/dna.txt`. Afterwards, it searches for the patterns `aa`, `gg`, `gat`, and `atttcccg`. You can search for any number of patterns on a single run--just make sure to separate the patterns with spaces!
```
bash sufarray.sh --run examples/dna.txt aa gg gat atttcccg
```
