File Copy using pthreads

Known bugs:
1. Doesn't take constant time for each thread.
2. Bug while copying .rar/.zip or any compressed file. Contents aren't copied completely despite showing the compressed file size as it was originally.
