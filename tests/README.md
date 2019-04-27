## Directories and Files ##
* **ctests/** This directory contains the unit tests for each project.  
* **Makefile** I believe this is obsolete.  
* **proj1-part2.py** A list of tests classes for project 1, part 2.  Each test class corresponds to one of the unit tests within the ctests/ directory  
* **proj2-extra-credit.py** Same as above, but for project 2, extra credit.  
* **proj2.py** Same, but for project 2.  
* **proj3.py** For project 3, I started getting a little fancy.  I realized that it would be easier to add/remove tests by creating  
             the array `test_values` and building the needed test classes by looping through this array.  I also realized that I could write the  
			 description of each test in the `.c` test file itself, then extract that description by writing the `get_description` method.  
			 It appears that I was inspired by `project4b.py` which is leftover from UW-Madison.  
* **proj4.py** Same as above, but for project 4.  
**NOTE:** It might be worth refactoring the first few .py files to be more like proj3.py and proj4.py  
* **project4b.py** Leftover from UW-Madison.  Might be worth deleting at some point.  
* **runtests** I believe this is obsolete.  
* **runtests-proj2** This short bash script is programmatically generated when you run `autograde.py` for project 2.  
                   However, it can also be modified manually as needed and run as a standalone script.  
* **runtests-proj3** This short bash script is programmatically generated when you run `autograde.py` for project 3.  
                   However, it can also be modified manually as needed and run as a standalone script.  
* **runtests2** I believe this is obsolete.  
* **runtests4b** I believe this is obsolete.  
* **toolspath.py** I believe this file acts as a pointer to important classes that are defined in the `tools/` directory.  
                 The classes there are imported by some of the python scripts here.  
