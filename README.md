# VITASDK Headers [![Build Status](https://travis-ci.org/DolceSDK/headers.svg?branch=master)](https://travis-ci.org/VITASDK/headers)

This repository contains all Vita headers needed for development.

## Structure :
- `db.yml` contains all the unique identifiers (NID) of the available functions.

-      vita-libs-gen db_365.yml db_365
-      cd db_365
-      make install
  
- `include/` contains the header files themselves
  - `psp2` is for header files of user-exported libraries
  - `psp2kern` is for header files of kernel-exported libraries
- `docs` contains everything related to the generation of the documentation using doxygen.
