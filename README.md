# Auction_App_Backend
Backend of Auction App for SQA Winter 2020

## Contributors: 
- Pulkit Madan    (100674520) 
- Aleem Alibhai   (100636156)

## Coverage
As the main() function in driver only handles arg parsing it is left un-checked other than the creation of the
user, item, and transaction lists. every other class, method, and line is covered. We technically have loop and decision
coverage for all of our methods, but look to the readFile and writeToFile methods for our example of loop/decision coverage.

## Reports
Our reports for individual runs of our test suite can be found under the test/reports folder in our project directory.
There is also a report on our coverage located under the test/reports/coverage folder. 

## Platform
This was developed in both windows and linux but only tested on linux. Folders and path directories are troublesome across
platforms ("\\" vs. "/"). The JUnit library also performs differently in the two platforms. For full functionality and reproducability
please run this in a linux environment.

## Extra Notes
one of our tests relies on a locked file ("filelocked.txt") to have no read/write permissions. for the sake of uploading
the project these permissions must be given to it. please remove read/write permissions on "filelocked.txt" before running. 
 
