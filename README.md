# PQBench_Windows

Simple benchmark which benches your single-core CPU performance using the pq-formula.

## Compilation and installation
I am not responsible for any hardware damage, you run this programm on your own risk!

(I don't recommand to compile pqbench with Microsoft Visual Studio, because of optimization problems. Follow instructions below instead.)



<details>
  -------------------------------------------------------------------------------------------------------------------------------------------------------------
<summary>MSYS2's and Mingw's install instruction</summary>

1. Follow these [install instructions](https://www.msys2.org/) to install MSYS2 including Mingw-w64

2. Add Mingw's bin folder to the PATH environment variable:
<br/>(I once messed up my Windows by accidentally overwriting the entire `PATH` variable, so be careful!)
     1. Type environment variable in the Windows search bar, hit enter <br/>
     2. Chose *"Environment variables"* on the bottom right hand corner <br/>
     3. Click on *"Path"*, then on edit <br/>
     4. Select *"New"*, then add this `C:\msys64\mingw64\bin` to the `PATH` <br/>
     5. Click "*OK*", you can now close all windows

(**NOTE:** Replace `C:\msys64\mingw64\bin` with your own destination folder if you changed it during the installation!)

That's it! Don't forget to reopen all open console windows.

**(Source: https://code.visualstudio.com/docs/cpp/config-mingw)** <br/>

\-------------------------------------------------------------------------------------------------------------------------------------------------------------
</details>


<br/>

In the root folder of pqbench, hold shift and press the right mouse button at the same time, then chose *"Open PowerShell-window here"*.

PQBench can be compiled with level 3 optimization using the mingw's g++ compiler on Windows:

```
$ g++ -s -DNDEBUG -O3 mainpqthread.cpp -o pqbench -static
```

<br/>


Type this command to run the benchmark:
```
$ ./pqbench
```
I **!!! highly !!!** recommand to use the [Windows Terminal App](https://www.microsoft.com/store/productId/9N8G5RFZ9XK3) from the Microsoft Store instead of just PowerShell.

## Features

PQBench provides following parameters:
```
-t, 	--time

-cs, 	--check-status

-oc,	--overclocking

-h	--help
```

### Explaination

```
-t, 	--time (Default active parameter)
```
Measures the time that has been taken to to make 5\*10^10 calculations.
The results are displayed in milliseconds, seconds and calculations per millisecond. 
```
-cs, 	--check-status
```
The --check-status parameter can be used to verify the benchmark is running and not freezing.
**NOTE:** Due to an extra thread running in the background, I recommand to use -t for proper benching.
```
-oc,	--overclocking
```
This parameter can be used for realtime overclocking. It displays calculations per second in realtime and these will change during changing any CPU properties (e.g. CPU frequency). **NOTE:** Due to extra threads running in the background, I recommand to use -t for resonable results (after messing around with your CPU).
```
-h	--help
```
It's the --help parameter, what do you expect.

```
PQBench (testphase) by ZombiDebugWall
Usage: pqbench [parameter]
-t, 	--time				Measures time and calculations per ms [DEFAULT]

-cs, 	--check-status			Shows if test is running properly or freezing
					NOTE: This parameter might reduce performance (Use -t for proper performance testing)

-oc,	--overclocking			This parameter measures calculations per second in realtime, made for realtime overclocking
					NOTE: This parameter will reduce performance due to realtime measurements (Again, use -t for proper performance testing)

-h	--help				print this message
```

