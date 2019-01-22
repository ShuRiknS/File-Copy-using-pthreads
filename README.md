File Copy using pthreads

Known bugs:
1. Bug while copying .rar/.zip or any compressed file. Contents aren't copied completely despite showing the compressed file size as it was originally.
2. Doesn't execute well with small files with size < 1KB
