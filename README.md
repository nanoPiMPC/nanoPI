# nanoPI

[nanoPI](http://homes.sice.indiana.edu/yh33/mypub/scalableMPC.pdf) is an actively-secure MPC framework. This is our prototype, contains the static rewriter and the C++ source code.


# Pre-required packages: 
g++, make, libgcrypt-dev.


# Static rewriter
Specify which file to rewrite in [this line](https://github.com/nanoPiMPC/nanoPI/blob/351a35c6387114cf3b280095051c33293e1362c1/Rewriter/Makefile#L3). Then simply run

```sh
$ make
```

# Compile:
1. Replace the IP address and number of parties [here](https://github.com/nanoPiMPC/nanoPI/blob/351a35c6387114cf3b280095051c33293e1362c1/MPC/src/Common/Network_IO.hpp#L25).
2. Run

```sh
$ make Install NoP=n
```
where "n" is the number of the parties.

For example, run

```sh
$ make Install NoP=4
```

3. Run

```sh
$ make App NoP=n
```

where "App" is the name of your application.

For example, run
```sh
$ make AES NoP=4
```


# Execution

After compiling the program, simply execuite
```sh
$ ./bin/app.out id port parameter
```
on each end, where "app" is the application name, "id" is the ID number of the party and "port" is the port number.

For example, run:
```sh
$ ./bin/AES.out id 12345 100
```
on each end will execute 100 x AES
