# Simple File Compression Using Run-Length Encoding

Usage: ./compress_file [OPTION] [FILE]
Option: [-d] to decompress file

Compresses a file by replacing sequences of identical bytes
by a pair of bytes, a repetition count byte followed by
the byte to be repeated. Include -d flag to decompress file.

test output file with: https://github.com/kornel-kidoodle/byte_viewer