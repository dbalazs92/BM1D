# BM1D

Brownian movement in one dimension. Starter pack for data processing course from 2017/10/30 to 2017/11/03.

## Authors

* **Balázs Demeter** - *University of Debrecen* - [E-mail](mailto:balazsdemeter92@gmail.com)
* **Balázs Ujvári** - *University of Debrecen* - [E-mail](mailto:balazs.ujvari@science.unideb.hu)
* **Dávid Baranyai** - *University of Debrecen* - [E-mail](mailto:divaldo95@gmail.com)

## Requirements

* Linux (Tested on Ubuntu 16.04 LTS)
* CERN ROOT (Tested on v6.10/08)

### Download Link

Via Git:

```
git clone https://github.com/dbalazs92/BM1D.git
```

Direct link:

```
https://github.com/dbalazs92/BM1D/archive/master.zip
```
### Build

In the directory of program (BM1D), open a terminal window and enter:

```
chmod 744 setup.sh
```
After giving the necessary permissions for setup script, run:

```
./setup.sh
``` 

### Running the simulation

After build, in the directory of build (bm1d_build), open a terminal window and enter:

```
./BM1D <openrootfile_or_simulation> 
```

If there's command line argument, then program opens the created root file. Name of file can be found in main file (BM1D.cc) .

## Updates

* 2017/10/29 - 'v1.3' - Minor fixes in Progress

* 2017/10/29 - 'v1.2' - Creation of reloaded version and it's repository

* 2015/10/27 - 'v1.0' - Creation of program

